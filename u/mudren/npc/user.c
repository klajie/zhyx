// user.c



#include <origin.h>

#include <user.h>

#include <ansi.h>

#include <command.h>



inherit CHARACTER;

inherit F_AUTOLOAD;

inherit F_SAVE;



nosave int net_dead;                    // 标志：是否断开了连接

nosave int last_age_set = 0;            // 上一次更新AGE的时间

nosave int user_say = 0;                // 一定时间以内玩家做的say-action

nosave int user_command = 0;            // 一定时间以内玩家发送的命令

nosave int attach_flag = 0;             // 是否正在和系统联络

int        at_time = 0;                 // 在什么时间计算的

int        ban_to = 0;                  // 在什么时间解禁玩家

string     ban_say_msg = "";            // 禁止说话的消息



nosave string my_defeater_id;           // 上一次打晕你的人ID

nosave string my_killer_id;             // 上一次杀你的人的ID

nosave int    craze = 0;                // 愤怒



#define DEFAULT_PRISON          "/d/register/prison"



// globals variables

string  prison = 0;

int     time_to_leave = 0;



int	is_stay_in_room()	{ return 1; }

int     is_player()		{ return clonep(); }

string  query_prison()          { return prison; }

int     query_time_to_leave()   { return time_to_leave; }

int     is_in_prison()          { return stringp(prison); }

int     is_net_dead()           { return net_dead || ! interactive(this_object()); }



#define MAX_COMMAND_ONE_SECTION         40

#define MAX_SAY_ONE_SECTION             4

#define BAN_SAY_PERIOD                  60



int query_current_neili_limit();

int query_neili_limit();

int query_current_jingli_limit();

int query_jingli_limit();

int query_potential_limit();

int query_experience_limit();



int is_user() { return 1; }



void create()

{

	::create();

	set_name("使用者物件", ({ "user object", "user", "object" }) );

}



void terminal_type(string term_type)

{

	set_temp("terminal_type", term_type);

	message("system", "终端机型态设定为 " + term_type + "。\n", this_object());

}



void reset()

{

	if ((int)query("potential") - (int)query("learned_points") < 100)

		add("potential", 1);

	if ((int)query("thief") > 0)

		add("thief", -1);

        if (query("pk_point") < 5000)
                add("pk_point",15);
}



// This is used by F_SAVE to determine the filename to save our data.

string query_save_file()

{

	string id;



	id = geteuid();

	if (! id) id = getuid();

	if (! stringp(id)) return 0;

	return sprintf(DATA_DIR "user/%c/%s", id[0], id);

}



// override set function

mixed set(string idx, mixed para)

{

        if (idx == "name" && clonep(this_object()) &&

            geteuid(this_object()))

        {

                NAME_D->change_name(this_object(), para, 1);

                return para;

        } else

                return ::set(idx, para);

}



int save()

{

	int res;



        if (query_temp("user_setup"))

        {

	        save_autoload();

	        res = ::save();

	        clean_up_autoload();		// To save memory

        } else

                res = ::save();



#if INSTALL_EXAMINE

        EXAMINE_D->examine_player(me);

#endif

	return res;

}



// This function updates player's age, called by heart_beat()

void update_age()

{

	if (! last_age_set)

        {

                last_age_set = time();

                add("mud_age", 0);

        }



        if (! environment() ||

            ! environment()->is_chat_room() ||

            ! query("env/halt_age"))

        {

                // Update age

	        add("mud_age", time() - last_age_set);

                if (time_to_leave)

                        time_to_leave -= time() - last_age_set;

        }



	last_age_set = time();

	set("age", 14 + (int)query("age_modify") +

		   ((int)query("mud_age") / 86400));

}



void setup()

{

	// We want set age first before new player got initialized with

	// random age.

        last_age_set = 0;

	update_age();



	::setup();



        // set the enable flag to enable save

        set_temp("user_setup", 1);



	restore_autoload();



	if (query("doing"))

                CLOSE_D->continue_doing(this_object());

}



void user_dump(int type)

{

	switch(type)

        {

	case DUMP_NET_DEAD:

                if (environment())

                {

			tell_room(environment(), query("name") + "断线超过 " +

			          NET_DEAD_TIMEOUT/60 + " 分钟，自动退出这个世界。\n");

                }

		catch(command("quit"));

                if (this_object() && ! query("doing"))

                {

                        // command quit failed.

			QUIT_CMD->force_quit(this_object());

                }

		break;



	case DUMP_IDLE:

                if (query_temp("learned_idle_force"))

                {

                        message_vision("$N狂笑三声，道：我终于明白了！\n",

                                       this_object());

                        tell_object(this_object(), "你经过长时间的发"

                                    "呆，终于对发呆神功的理解又深了一层！\n");

                        improve_skill("idle-force", 360000);

                        delete_temp("learned_idle_force");

                } else

	                tell_object(this_object(), "对不起，您已经发呆超过 " +

		                    IDLE_TIMEOUT / 60 + " 分钟了，请下次再来。\n");

                if (environment())

                {

		        tell_room(environment(), "一阵风吹来，将发呆中的" + query("name") +

			           "化为一堆飞灰，消失了。\n", ({this_object()}));

                }

		command("quit");

                if (this_object() && ! query("doing"))

                {

                        // command quit failed.

			QUIT_CMD->force_quit(this_object());

                }

	        break;

	default:

                return;

	}

}



// net_dead: called by the gamedriver when an interactive player loses

// hir network connection to the mud.

private void net_dead()

{

	object link_ob;



	if (! query("doing"))

		set_heart_beat(0);



	if (objectp(link_ob = query_temp("link_ob")))

	{

		if (link_ob->query_temp("ip_number"))

		{

			link_ob->set("last_on", time());

			link_ob->set("last_from",

				     link_ob->query_temp("ip_number"));

			link_ob->save();

		}

		destruct(link_ob);

	}



	net_dead = 1;

	if (userp(this_object()) && ! query("doing"))

        {

		call_out("user_dump", NET_DEAD_TIMEOUT, DUMP_NET_DEAD);

	        tell_room(environment(), query("name") + "断线了。\n", this_object());

	        CHANNEL_D->do_channel(this_object(), "sys", "断线了。");

                remove_all_enemy(1);

	} else

        {

                if (environment())

                        message("vision", name() + "离线了。\n",

				environment(), ({ this_object() }));

	}

}



// reconnect: called by the LOGIN_D when a netdead player reconnects.

void reconnect()

{

        set_heart_beat(1);

        net_dead = 0;

        remove_call_out("user_dump");

        tell_object(this_object(), "重新连线完毕。\n");

}



// skill variable & function

#define MAX_NEILI_IMPROVE       query("con")

#define MAX_JINGLI_IMPROVE      query("con")



int query_neili_limit()

{

        string *skill_names;

        mapping skills;

        int neili_limit;

        int base_lvl, lvl;

        int tmp;

        int i;



        skills = this_object()->query_skills();

        if (! mapp(skills))

                return 0;



        skill_names = keys(skills);



        base_lvl = ((int) skills["force"]) / 2;

        neili_limit = base_lvl * 10;

        for (i = 0; i < sizeof(skill_names); i++)

        {

                if (file_size(SKILL_D(skill_names[i]) + ".c") == -1)

                {

                        // No such skill

                        continue;

                }



                if (! SKILL_D(skill_names[i])->valid_enable("force"))

                        continue;



                lvl = (int) skills[skill_names[i]];

                tmp = (base_lvl + lvl) * 10;

                tmp += (int) SKILL_D(skill_names[i])->query_neili_improve(this_object());

                if (tmp > neili_limit) neili_limit = tmp;

        }



        if (query("special_skill/mystery"))

                neili_limit += query("con") * 15;

        neili_limit += neili_limit * query("improve/neili") / 100;

        if (query("breakup"))

                neili_limit += neili_limit * 3 / 10;

        return neili_limit;

}



int query_current_neili_limit()

{

        int neili;

        string force;



        force = query_skill_mapped("force");

        neili = (int)query_skill("force", 1) / 2 * 10;

        if (stringp(force) && force != "")

        {

                neili += (int)query_skill(force, 1) * 10;

                neili += SKILL_D(force)->query_neili_improve(this_object());

        }



        if (query("special_skill/mystery"))

                neili += query("con") * 15;

        neili += neili * query("improve/neili") / 100;

        if (query("breakup"))

                neili += neili * 3 / 10;

        return neili;

}



int query_jingli_limit()

{

        int limit;



        limit = ((int)query("magic_exp") / 3000) + query("int") * 30;

        limit += limit * query("improve/jingli") / 100;

        if (query("animaout"))

                limit += limit * 4 / 10;

        return limit;

}



int query_current_jingli_limit()

{

        return query_jingli_limit();

}



int query_potential_limit()

{

	int p;



	if (ultrap(this_object()))

		p = 10000;

	else

		p = query_int() * 10 / 2 + 100;

        return (int)query("learned_points") + p;

}



int query_experience_limit()

{

	int p;



	if (ultrap(this_object()))

		p = 10000;

	else

		p = query("int") * 10 / 2 + 100;

        return (int)query("learned_experience") + p;

}



int can_improve_neili()

{

        return query("improve/neili") < MAX_NEILI_IMPROVE;

}



int can_improve_jingli()

{

        return query("improve/jingli") < MAX_NEILI_IMPROVE;

}



void improve_neili(int n)

{

        if (! can_improve_neili())

                return;



        if (add("improve/neili", n) > MAX_NEILI_IMPROVE)

                set("improve/neili", MAX_NEILI_IMPROVE);



        add("max_neili", (10 + random(80)) * n);

        if (query("max_neili") > query_neili_limit())

                set("max_neili", query_neili_limit());



        set("neili", query("max_neili"));

}



void improve_jingli(int n)

{

        if (! can_improve_jingli())

                return;



        if (add("improve/jingli", n) > MAX_JINGLI_IMPROVE)

                set("improve/jingli", MAX_JINGLI_IMPROVE);



        add("max_jingli", (5 + random(40)) * n);

        if (query("max_jingli") > query_jingli_limit())

                set("max_jingli", query_jingli_limit());



        set("jingli", query("max_jingli"));

}



int accept_fight(object ob)

{

	if (query_temp("pending/fight") == ob)

		return 1;



        tell_object(this_object(), YEL "如果你愿意和对方进行比试，请你也对" +

                    ob->name() + "("+ (string)ob->query("id")+")"+

                    "下一次 fight 指令。\n" NOR);



	tell_object(ob, YEL "由于对方是由玩家控制的人物，你必须等对方同意才" +

              "能进行比试。\n" NOR);



        return 0;

}



int accept_hit(object ob)

{

        message_vision("$N大喝道：" + ob->name() + "，你要干什么？\n",

                       this_object(), ob);

        return 1;

}



int accept_kill(object ob)

{

        if (is_killing(ob))

                return 1;



        tell_object(this_object(), HIR "如果你要和" + ob->name() +

	        "性命相搏，请你也对这个人(" + (string)ob->query("id") +

                ")下一次 kill 指令。\n" NOR);

        return 1;

}



int accept_ansuan(object who)

{

        command(random(2) ? "say 嗯！怎么..." : "say 啊！不好！");

        return 1;

}



int reject_command()

{

        int t;



        if (wizardp(this_object()))

                return 0;



        t = time() & 0xFFFFFFFE;

        if (at_time != t)

        {

                at_time = t;

                user_command = 1;

                user_say = 0;

        } else

                user_command++;



        if (user_command > MAX_COMMAND_ONE_SECTION)

	{

		user_command = 0;

                if (! query("born"))

                        // not born yet

                        return 0;

                return 1;

	}



        return 0;

}



void ban_say_until(int ban_period, string msg)

{

        int t;



        t = time();

        if (ban_to > t)

                ban_to += ban_period;

        else

                ban_to = t + ban_period;

        ban_say_msg = msg;

}



int ban_say(int raw)

{

        int t;



        if (wizardp(this_object()))

                return 0;



        if (is_in_prison())

        {

                notify_fail("你省省吧，好好做你的牢，少折腾。\n");

                return 1;

        }



        t = time() & 0xFFFFFFFE;

        if (ban_to > t)

        {

                notify_fail(ban_say_msg + "，请于" +

                            appromix_time(ban_to - t) + "以后再尝试。\n");

                return 1;

        }



	if (! raw)

		return 0;



        if (at_time != t)

        {

                at_time = t;

                user_say = 1;

                user_command  = 0;

        } else

                user_say++;



        if (user_say > MAX_SAY_ONE_SECTION)

        {

                ban_say_until(BAN_SAY_PERIOD, "系统禁止你送出信息");

                CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",

                        "听说" + query("name") + "因为太罗嗦，被人堵住了嘴。");

                notify_fail(HIR "由于你发布的信息太多，因此系统暂时"

                            "禁止你发出信息。\n" NOR);

                return 1;

        }



        return 0;

}



void permit_say(int n)

{

        if (ban_to <= time())

                return;



        if (! n)

                ban_to = 0;

        else

                ban_to -= n;



        if (ban_to <= time())

                tell_object(this_object(), "你可以继续发布信息了！\n");

}



// thow the person into prison

void get_into_prison(object ob, string p, int time)

{

        object me;



        me = this_object();

        if (! p) p = prison;

        if (! p) p = DEFAULT_PRISON;



        if (prison && base_name(environment()) == p)

        {

                time_to_leave += time * 60;

                if (ob && time)

                        CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",

                                "听说" + query("name") + "的刑期被" +

                                ob->query("name") + "加长了" +

                                chinese_number(time) + "分钟。");

                return;

        }



        if (prison && prison == p && base_name(environment()) != prison)

        {

                p->catch_back(me);

                me->set("startroom", prison);

                me->move(prison);

                message_vision("“啪”的一声，$N狠狠的摔倒了地上。\n", me);

                if (living(me)) me->unconcious();



                CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",

                        "听说" + query("name") + "越狱潜逃，结果被抓"

                        "回去了。");



                save();

                return;

        }



        p->catch_ob(me);



        if (ob)

        {

                CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",

                        "听说" + query("name") + "被" + ob->query("name") +

                        "送进了" + p->short() + HIM "，禁闭" +

                        chinese_number(time) + "分钟。");

        }



        me->set("startroom", prison);

        me->move(p);

        prison = p;

        time_to_leave += time * 60;

        save();



        message_vision("“啪”的一声，$N重重的摔倒了地上。\n", me);

        me->set("jing", 1);

        me->set("eff_jing", 1);

        me->set("qi", 1);

        me->set("eff_qi", 1);

        me->set("jingli", 0);

        me->set("neili", 0);

        me->receive_damage("jing", 0);

        if (living(me)) me->unconcious();

}


//因为PK被关入地狱，edit by smallfish 2001-06-01
void pk_into_prison(string p)
{
        object me;

        me = this_object();
        if (! p) p = prison;
        if (! p) p = DEFAULT_PRISON;

        if (prison && prison == p && base_name(environment()) != prison)
        {
                p->catch_back(me);
                me->set("startroom", prison);
                me->move(prison);
                message_vision("“啪”的一声，$N狠狠的摔倒了地上。\n", me);
                if (living(me)) me->unconcious();

                CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
                        "听说" + query("name") + "越狱潜逃，结果被抓"
                        "回去了。");

                save();
                return;
        }

        p->catch_ob(me);

        me->set("startroom", prison);
        me->move(p);
        prison = p;
        save();

        message_vision("“啪”的一声，$N重重的摔倒了地上。\n", me);
        me->set("jing", 1);
        me->set("eff_jing", 1);
        me->set("qi", 1);
        me->set("eff_qi", 1);
        me->set("jingli", 0);
        me->set("neili", 0);
        me->receive_damage("jing", 0);
        if (living(me)) me->unconcious();
}


// out of prison

void leave_prison(object ob)

{

        object me;



        me = this_object();

        time_to_leave = 0;



        if (! prison->free_ob(me))

		return;



        prison = 0;



        if (living(me))

                me->enable_player();

        else

                me->revive();

        save();



        if (ob)

                CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",

                        "听说" + query("name") + "被" + ob->name() +

                        "提前释放了。");

        else

                CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",

                        "听说" + query("name") + "已经刑满释放了。");

}



varargs void die(object killer)

{

        if (prison)

        {

                set_temp("die_reason", "惨死在监狱中");

                clear_condition(0);

                receive_damage("qi", 0);

                prison = 0;

                if (living(this_object()))

                        enable_player();

        }



        ::die(killer);

        save();

}



// when the user was in prison, the heart beaten function of

// char will call damage heal_up, then the function will call

// it

void update_in_prison()

{

        object me;



        me = this_object();

        me->set("qi", 0);

        me->set("jing", 0);

        me->set("neili", 0);



	if (! living(me))

		return;



        if (time_to_leave > 0)

        {

                if (environment() && base_name(environment()) != prison)

                {

                        // escape from prison?

                        get_into_prison(0, 0, 0);

                }

                return;

        }


        if (me->query("pk_point") < 0 )
        {
                if (environment() && base_name(environment()) != prison)
                {
                        // escape from prison?
                        pk_into_prison(0);
                }
                return;
        }


        leave_prison(0);

}



// return true if the user was attached system, such as

// command sameip will run a much long time, in the period

// the user shouldn't receive message except from the system

int is_attach_system()

{

        return attach_flag;

}



// start attaching

int attach_system()

{

        attach_flag = 1;

}



// stop, deatched

int detach_system()

{

        attach_flag = 0;

}



string command_verb()

{

        return query_verb();

}



#define CRAZE_LIMIT_1   7000    // for 光明磊落

#define CRAZE_LIMIT_2   5000    // for 心狠手辣



// 愤怒气息

int query_craze() { return craze; }



// 最大的愤怒气息

int query_max_craze()

{

        switch (query("character"))

        {

        case "光明磊落" :

                return CRAZE_LIMIT_1;



        case "心狠手辣" :

                return CRAZE_LIMIT_2;

        default:

                return 0;

        }

}



// 现在是否处于最愤怒的状态

int is_most_craze()

{

        return (craze > 0) && (craze >= query_max_craze());

}



// 因为被打倒而震怒

void craze_of_defeated(string defeater_id)

{

        my_defeater_id = defeater_id;

}



// 因为被击毙而震怒

void craze_of_die(string killer_id)

{

        my_killer_id = killer_id;

        craze = query_max_craze();

}



// 愤怒的攻击对手后调用这个函数清除对象

void craze_defeated(string enemy_id)

{

        if (enemy_id == my_defeater_id)

                my_defeater_id = 0;



        if (enemy_id == my_killer_id)

                my_killer_id = 0;

}



// 是否憎恨某人

int is_hating(string enemy_id)

{

        if (enemy_id == my_defeater_id ||

            enemy_id == my_killer_id)

                return 1;



        return 0;

}



// 提升愤怒，返回提升的有效值

int improve_craze(int amount)

{

        int limit;



        if (amount < 0)

                error("error: improve_craze amount to be less than 0\n");



        limit = query_max_craze();

        craze += amount;

        if (craze > limit)

        {

                amount += limit - craze;

                craze = limit;

        }

        return amount;

}



// 消耗愤怒，返回消耗的有效值

int cost_craze(int n)

{

        if (n < 0)

                error("error: improve_craze amount to be less than 0\n");



        if (n > craze)

        {

                n = craze;

                craze = 0;

        } else

                craze -= n;

        return n;

}



// 编辑文件

void edit_file(string file)

{

        ed(file);

}



// 是否是结拜兄弟？

int is_brother(mixed ob)

{

        string id;



        if (stringp(ob))

                id = ob;

        else

        if (objectp(ob))

                id = ob->query("id");

        else

                return 0;



        // 是否是普通结拜兄弟

        if (query("brothers/" + id))

                return 1;



        // 是否是结盟的兄弟

        return 0;

}
