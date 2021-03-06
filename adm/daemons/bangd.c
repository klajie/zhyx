// 帮会系统
// 在原基础上增加帮会声望部分，并修改了存储结构
// Updated By Yuchang@zhyx

#include <ansi.h>

// #pragma optimize
// #pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

// 帮会声望最大是10亿
#define MAX_PARTY_FAME         1000000000

// 每个帮会最多有100个仇人
#define MAX_HATRED_PERSON       100

// 当仇人超过的时候每次移除多少个
#define HATREDP_REMOVED         10

mapping party_fame;
mapping last_party_fame;

private int sort_hatred(string, string, mapping);

public string query_save_file() { return DATA_DIR "bangd"; }

void create()
{
        seteuid(getuid());
        restore();
        set_heart_beat(7200 + random(3600));
        if (! mapp(party_fame)) party_fame = ([ ]);
}

void remove() { save(); }

public void mud_shutdown()  { save(); }

public void reset_party()
{
        string *all_fam;
        string fam;

        all_fam = keys(party_fame) - ({ 0 });

        foreach (fam in all_fam)
        {
		last_party_fame[fam] += party_fame[fam];
		party_fame[fam] = 0;
	}
        save();
        return;
}

public string max_party(int max_sw)
{
        string *all_fam;
        string fam, max_fam;

        all_fam = keys(party_fame) - ({ 0 });
	if (sizeof(all_fam) < 2)   return 0;

        foreach (fam in all_fam)
        {
		if (party_fame[fam] > max_sw)
                {
                   	max_sw = party_fame[fam];
                      	max_fam = fam;
	        }
	}
        return max_fam;
}

private void heart_beat()
{
	string party_name;

	party_name = max_party(1000);
	if (!stringp(party_name))   return;
        CHANNEL_D->do_channel(this_object(), "rumor", "听说『" +
        	party_name + "』名声日盛，已成为江湖中最大的帮会。");
	save();
}

// 返回帮会声望：如果参数为空，返回mapping类型，包含了所有帮
// 会的声望；如果参数是人物， 则返回该人物所在的那个帮会的声
// 望；如果参数是帮会，则返回该帮会的声望。
public mixed query_party_fame(mixed ob)
{
        string fname;

        if (stringp(ob))
                return party_fame[ob];

        if (objectp(ob))
        {
                if (stringp(fname = ob->query("party/party_name")))
                        return party_fame[fname];
                else
                        return 0;
        }

        return party_fame;
}

// 查询昨天的帮会名望信息
public mapping query_all_last_party_fame()
{
        if (! mapp(last_party_fame))
                // 没有昨天的信息，返回今天的
                return party_fame;

        // 返回昨天的帮会声望信息
        return last_party_fame;
}

// 查询帮会的仇恨信息：输入的ob可以是帮会的名字，也可是帮会
// 中的人物。
public mapping query_party_hatred(mixed ob)
{
        mapping hatred;
        string fname;

        if (objectp(ob))
                fname = ob->query("party/party_name");
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || ! mapp(hatred = query(fname + "/hatred")))
                return 0;

        return hatred;
}

// 变化帮会声望：输入的ob可以是帮会的名字，也可是帮会中的人
// 物。
public void add_party_fame(mixed ob, int n)
{
        int new_fame;
        string fname;

        if (objectp(ob))
                fname = ob->query("party/party_name");
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || undefinedp(query(fname + "/member")))
                return;

        // 计算新的帮会声望
        new_fame = party_fame[fname] + n;
        if (new_fame > MAX_PARTY_FAME)
                new_fame = MAX_PARTY_FAME;
        party_fame[fname] = new_fame;
        save();
        return;
}

// 帮会间仇杀
public void party_kill(object killer, object victim)
{
        int kexp;
        int vexp;
        string vfam;
        string kfam;
        string kid;
        int fame_delta;
        mapping hatred;
        mixed *d;

        // 只有玩家之间的仇杀才计算在内
        if (! objectp(killer) || ! playerp(killer) ||
            ! objectp(victim) || ! playerp(victim))
                return;

        // 巫师之间的比划可不能算数
        if (wizardp(killer) || wizardp(victim))
                return;

        // 查看这两个玩家所处的帮会
        kfam = killer->query("party/party_name");
        vfam = victim->query("party/party_name");

        if (killer->is_brother(victim) && killer->is_killing(victim->query("id")))
                // 杀死结拜兄弟，威望降低10%
                killer->add("weiwang", -killer->query("weiwang") / 10);

        if (! stringp(kfam) && ! stringp(vfam))
                // 都不在帮会内，不必继续了
                return;

        kexp = killer->query("combat_exp");
        vexp = victim->query("combat_exp");

        if (kfam == vfam)
        {
                if (! killer->is_killing(victim->query("id")))
                        // 失手所杀，不予理会
                        return;

                // 兄弟间残杀？不与理会，直接扣除帮会和个人1/10威望。
                add_party_fame(kfam, -party_fame[kfam] / 10);
                killer->add("weiwang", -killer->query("weiwang") / 10);
                return;
        }

        if (kexp > vexp * 2 && vexp >= 100000)
        {
                // 杀手的经验远大于对方（以强欺弱？），并且被杀的
                // 人有一定的经验，这将导致帮会声望的降低。
                fame_delta = 100 - (vexp / 10000);
                if (fame_delta < 10)   fame_delta = 10;
                fame_delta = -fame_delta;
        } else
                // 双方差距不是很大，增加杀手所在帮会声望
                fame_delta = 5 + random(5);

        // 查看杀手所在的帮会是否仇恨死者：如果仇恨，则能够
        // 带动声望的变化。
        if (stringp(kfam))
        {
                string path;
                int wang;

                path = kfam + "/hatred/"+ victim->query("id");
                d = query(path);
                if (arrayp(d) && sizeof(d) >= 2 && intp(d[1]))
                {
                        // 仇恨死者，帮会获得额外的声望
                        if (d[1] > 2000)
                                CHANNEL_D->do_channel(this_object(), "rumor",
                                        "听说" + killer->name(1) + "击毙了" +
                                        victim->name(1) + "，为" +
                                        kfam + "出了一口恶气。");
                        wang = d[1] / 20;
                        if (wang < 5)     wang = 5;
                        if (wang > 50)    wang = 50;
                        fame_delta += wang;
                        wang = d[1] / 3;

                        // 对此人的仇恨降低(降低的要比增加的要多)，
                        // 具体可以看fame_delta 与仇恨度公式的差异
                        d[1] -= wang;
                        if (d[1] <= 0)
                                delete(path);
                        else
                                set(path, d);
                }
        }

        // 调整两个帮会的声望
        add_party_fame(killer,  fame_delta);
        add_party_fame(victim, -fame_delta);

        // 统计该杀手对本门的残害程度
        if (! stringp(vfam))
                return;

        // 仇恨程度和声望的变化都是在一个数量级上(K经验)，但
        // 是仇恨程度低于声望的变化。
        vexp = vexp / 1000 + 1;
        if (vexp > 5000)
                vexp = (vexp - 5000) / 16 + 2000;
        else
        if (vexp > 1000)
                vexp = (vexp - 1000) / 4 + 1000;

        kid = killer->query("id");
        if (! mapp(hatred = query(vfam + "/hatred")))
        {
                set(vfam + "/hatred/" + kid,
                    ({ killer->name(), vexp }));
                return;
        }

        // 每个帮会最多记录若干个仇人
        if (! undefinedp(d = hatred[kid]))
        {
                if (! arrayp(d) || sizeof(d) < 2 ||
                    ! intp(d[1]) || ! stringp(d[0]))
                {
                        // 这个ID的数据出了故障
                        d = 0;
                }
        } else
        if (sizeof(hatred) >= MAX_HATRED_PERSON)
        {
                string *ids;
                int i;

                // 过滤去掉一些人，为什么不去掉一个？这是为
                // 了防止过滤频繁的进行过滤操作。
                ids = sort_array(keys(hatred),
                                 (: sort_hatred :), hatred);
                for (i = 0; i < sizeof(ids) && i < HATREDP_REMOVED; i++)
                        map_delete(hatred, ids[i]);
        }

        if (! arrayp(d))
                d = ({ killer->name(1), vexp });
        else
        {
                d[0] = killer->name(1);
                d[1] += vexp;
        }

        // 记录这个人的信息
        hatred[kid] = d;
        return;
}

// 去掉所有帮会对某个人的仇恨信息
public void remove_hatred(string id)
{
        mapping dbase, party, hatred;
        string fam;

        if (! mapp(dbase = query_entire_dbase()))
                // 现在还没有仇恨信息
                return;

        // 查阅所有的帮会
        foreach (fam in keys(dbase))
        {
                reset_eval_cost();

                if (! mapp(party = dbase[fam]))
                        continue;

                if (mapp(hatred = party["hatred"]))
                        // 去掉该帮会对某人的仇恨信息
                        map_delete(hatred, id);

                if (! mapp(hatred) || sizeof(hatred) < 1)
                        // 这个帮会已经没有仇恨信息
                        map_delete(party, "hatred");
        }
        save();
        return;
}

// 创建帮会
public void create_party(string fname, int base, object *obs)
{
        string *info;
	mapping players;
        int i;

        party_fame[fname] = base;
        if (! mapp(last_party_fame))
                last_party_fame = ([ fname : base ]);
        else
                last_party_fame[fname] = base;

	players = ([]);
	for (i=0; i<sizeof(obs); i++)
	{
		info = ({ obs[i]->query("party/right"), obs[i]->query("name"), 0 });
		players += ([ obs[i]->query("id") : info ]);

	}
        set(fname, ([ "member" : players,
        	      "money"  : 0,
                      "time"   : time() ]));

        save();
        CHANNEL_D->do_channel(this_object(), "rumor",
                   "听说玩家帮会『" + fname + "』在江湖中成立了。");
        return;

}

// 解散帮会
public void dismiss_party(string fname)
{
        string *ids;
        string id;

        // 清除帮会中的所有玩家的相关信息
        if (mapp(query(fname + "/member")))
	        ids = keys(query(fname + "/member"));

        if (arrayp(ids))
        {
                // 帮会中还有玩家，清除他们的信息
                foreach (id in ids)
                {
                	reset_eval_cost();
                	UPDATE_D->clear_user_data(id, "party");
                	UPDATE_D->clear_user_data(id, "room");
                }
        }

        // 清除名望信息
        map_delete(party_fame, fname);
        if (mapp(last_party_fame)) map_delete(last_party_fame, fname);

        // 清除帮会的所有信息
        rm(BANG_DIR + fname);
        delete(fname);
        save();
        CHANNEL_D->do_channel(this_object(), "rumor",
                   "听说" + fname + "人才凋零，昔日好友尽皆散去，从此江湖再无此字号了。");
	return;
}

// 查询帮会中的弟兄
public mapping query_members(mixed ob)
{
        mapping member;
        string fname;

        if (objectp(ob))
                fname = ob->query("party/party_name");
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || ! mapp(member = query(fname + "/member")))
                return 0;

        return member;
}

// 从帮会中去掉一个人
public varargs void remove_member_from_party(mixed fname, string id)
{
        mapping party, member;

        if (objectp(fname))
        {
                // fname is user object
                id = fname->query("id");
                if (! stringp(fname = fname->query("party/party_name")))
                        return;
        } else
        if (! stringp(fname))
                // or fname must be a league name
                return;

        if (! mapp(party = query(fname)) ||
            ! mapp(member = party["member"]))
                // no such party or no member in the party
                return;

	map_delete(member, id);
	set(fname + "/member", member);
        add_party_fame(fname, -1);
	save();
        if (sizeof(keys(member)) < 2)
		dismiss_party(fname);

        return;
}

// 在帮会中增加一个人
public void add_member_into_party(string fname, string id, string cname)
{
        mapping member;
	string *info;
	object player;

        if (! mapp(member = query(fname + "/member")))
                return 0;

        if (member_array(id, keys(member)) != -1)
                return 0;

	info = ({ 5, cname, 0 });
        member += ([ id : info ]);
        set(fname + "/member", member);

        // 如果该ID在线，且EXP>200K则增加1点声望
        if (userp(player = find_player(id)) && player->query("combat_exp") > 200000)
	        add_party_fame(fname, 1);
	return;
}

// 修改帮会成员权限
public void modify_member_auth(string fname, string id, int auth)
{
        mapping member;

        if (! mapp(member = query(fname + "/member")))
                return 0;

        if (member_array(id, keys(member)) == -1)
                return 0;

        member[id][0] = auth;
        set(fname + "/member", member);
	save();
	return;
}

// 排序：升序
private int sort_hatred(string id1, string id2, mapping hatred)
{
        mixed *d1, *d2;

        if (! arrayp(d1 = hatred[id1]) || sizeof(d1) < 2 || ! intp(d1[1]))
                return -1;

        if (! arrayp(d2 = hatred[id2]) || sizeof(d2) < 2 || ! intp(d2[1]))
                return 1;

        return d1[1] - d2[1];
}

// 记录帮会日志文件
public int party_save_record(string fname, string str)
{
	fname = BANG_DIR + fname;
	if(!write_file(fname,str))
		return 0;
	else	return 1;
}

// 向帮会存款
public void cun_money_to_party(object ob, int amount)
{
	string id, fname;
	mapping party;

	if (! objectp(ob))
		return;

	if (! stringp(fname = ob->query("party/party_name")))
		return;

	id = ob->query("id");
	if (! mapp(party = query(fname)))
                return;

	party["member"][id][2] += amount;
	party["money"] += amount;
	set(fname, party);
	save();
	return;
}

// 查询帮会存款总数
public int check_party_money(string fname)
{
	return query(fname + "/money");
}

// 从帮会取款
public void qu_money_from_party(object ob, int amount)
{
	string id, fname;
	mapping party;

	if (! objectp(ob))
		return;

	if (! stringp(fname = ob->query("party/party_name")))
		return;

	id = ob->query("id");
	if (! mapp(party = query(fname)))
                return;

	party["money"] -= amount;
	set(fname, party);
	save();
	return;
}
