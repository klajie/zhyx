// Updated by Lonely

#include <ansi.h>
#include <combat.h>
#include <net/dns.h>

inherit F_CLEAN_UP;
string bar_string = "■■■■■■■■■■■■";
string blank_string = "□□□□□□□□□□□□";
string blank_string3 = "□□□□□□□□□□□□";
string blank_string2 = "　　　　　　　　　　　　";

mapping oprank = ([
        "宗师"     : HIW "★★★★★",
        "登峰造极" : HIY "★★★★☆",
        "超凡脱俗" : HIY "★★★★  ",
        "臻至化境" : HIR "★★★☆  ",
        "炉火纯青" : HIR "★★★    ",
        "已有大成" : HIC "★★☆    ",
        "非同凡响" : HIC "★★      ",
        "出类拔萃" : HIG "★☆      ",
        "身手不凡" : HIG "★        ",
        "已有小成" : HIM "☆        ",
]);

string display_attr(int gift, int value);
string status_color(int current, int max);
string tribar_graph(int val, int eff, int max, string color);
string tribar_graph2(int val, int eff, int max, string color);
string tribar_graph3(int a);
void create() { seteuid(ROOT_UID); }

int main(object me, string arg)
{
        object ob;
        mapping my,mci;
        string line , skill_type;
        object weapon;
        int attack_points, dodge_points, parry_points,jings, qis, j, i, x, cnt;
        string jbd, msg;
        mixed wind,cold,fire,lightning,poison;
        int can_score = 0;
        int age, month;
        string startroom = "";
        object the_room = 0;

        seteuid(getuid(me));

        if(! arg)
                ob = me;
        else
                ob = present(arg, environment(me));

        if (! ob) ob = find_player(arg);
        if (! ob) ob = find_living(arg);
        if (! ob) return notify_fail("你要察看谁的状态？\n");

        if (wizardp(me) || ob == me) 
                can_score = 1;
        else 
        if (ob->is_pet() && ob->query("owner") == me->query("id")) 
                can_score = 1;
        else 
        if (me->query("couple/child") == ob->query("id"))
                can_score = 1;
        else 
        if (stringp(startroom = ob->query("startroom")) &&
            objectp(the_room = load_object(startroom)) &&
            the_room->query("room_owner_id") == me->query("id"))
                can_score = 1;
        if (! can_score)
                return notify_fail("只有巫师能察看别人的状态。\n");

        my = ob->query_entire_dbase();
        mci = my["combat"];
        if (! mci) mci = ([ ]);
        
        if (playerp(ob) && (! stringp(my["born"]) || ! my["born"])) 
                return notify_fail("还没有出生呐，察看什么？\n"); 

        jings = (my["eff_jing"] * 12 / my["max_jing"]) * 2;
        qis = (my["eff_qi"] * 12 / my["max_qi"]) * 2;
        // line = sprintf("                          【" + MUD_NAME + "】个人档案                      \n\n", ob->query("language"),);
        line = sprintf( BOLD "\n%s" NOR "%s\n", RANK_D->query_rank(ob), ob->short(1) );
        // ob->update_age();
        
        line += sprintf( YEL "┏━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━┓\n" NOR );

	if (playerp(ob))
	{
                age = ob->query("age");
                month = ob->query("mud_age");
                if (age >= 60)
                {
                        month -= (age - 60) * 86400 * 4;
                        month = (month - 118 * 86400) / 7200 / 4 + 1;
                } else
                if (age >= 30)
                {
                        month -= (age - 30) * 86400 * 3;
                        month = (month - 28 * 86400) / 7200 / 3 + 1;
                } else
                if (age >= 18)
                {
                        month -= (age - 18) * 86400 * 2;
                        month = (month - 4 * 86400) / 7200 / 2 + 1;
                } else
                {
                        month -= (age - 14) * 86400;
                        month = month / 7200 + 1;
                }

                // not show invalid month
                if (month > 12 || month < 1)
                        month = 1;

        	line += sprintf( YEL "┃" HIY "【年龄】" NOR "%-24s  " YEL "  ┃" NOR ,
                        chinese_number(age) + "岁" + 
                        chinese_number(month) + "个月");
        } else
                line += sprintf( YEL "┃" HIY "【年龄】" NOR "%-24s  " YEL "  ┃" NOR , 
                        chinese_number(ob->query("age")) + "岁" +  
                        chinese_number((ob->query("mud_age")-(ob->query("age")-14)*86400)/7200 + 1 ) + "个月"); 
                
	if (objectp(weapon = ob->query_temp("weapon")))
        {
		skill_type = weapon->query("skill_type");
                attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
	} else
        {
                mapping prepare;
                string *sk;

                prepare = me->query_skill_prepare();
                if (! prepare) prepare = ([]);
                sk = keys(prepare);
        
                if (sizeof(sk) == 0) skill_type = "unarmed"; 
                else skill_type = sk[0];
                attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
                if (sizeof(prepare) == 2)
                {
                        int temp;
                        temp = COMBAT_D->skill_power(ob, sk[1], SKILL_USAGE_ATTACK);
                        if (attack_points < temp) attack_points = temp;
                }
        }

	parry_points = COMBAT_D->skill_power(ob, "parry", SKILL_USAGE_DEFENSE);
	dodge_points = COMBAT_D->skill_power(ob, "dodge", SKILL_USAGE_DEFENSE);

        line += sprintf( HIW "【战斗攻击力】" NOR " %10d" YEL " ┃\n" NOR ,
                attack_points/100 + 1);

        line += sprintf( YEL "┃" HIY "【性别】" NOR "%-26.8s" YEL "  ┃" NOR ,
                    ob->query("gender")+ob->query("race"));
                                        
        line += sprintf( HIW "【战斗防御力】" NOR " %10d" YEL " ┃\n" NOR ,
                (dodge_points + (weapon? parry_points: (parry_points/10)))/100 + 1);

        line += sprintf( YEL "┃" HIY "【性格】" NOR "%-28.28s" YEL "┃" NOR ,
                ob->query("character")?ob->query("character"):"还未确定" );

        line += sprintf( HIW "【战斗伤害力】" NOR " %10d" YEL " ┃\n" NOR ,
                weapon ? ob->query_temp("apply/damage")
                               : ob->query_temp("apply/unarmed_damage"));

        line += sprintf( YEL "┃" HIY "【生辰】" MAG "%-28.28s" NOR+YEL "┃" NOR ,
                CHINESE_D->chinese_date(ob->query("birthday")));

        line += sprintf( HIW "【战斗保护力】" NOR " %10d" YEL " ┃\n" NOR ,
                ob->query_temp("apply/armor"));

        line += sprintf( YEL "┃                          ┏━━━━┻━━━━━━━━━━━━━┫\n" NOR,);      
        if (mapp(my["family"]))
        {
                if( my["family"]["family_name"] )
                        line += sprintf( YEL "┃" HIG "【门派】" NOR "%-18.8s" YEL "┃" NOR,
                                my["family"]["family_name"] );
                else  
                        line += sprintf( YEL "┃" HIG "【门派】" NOR "普通百姓          " YEL "┃" NOR );
        }
        else  
                line += sprintf( YEL "┃" HIG "【门派】" NOR "普通百姓          " YEL "┃" NOR );
        line += sprintf( HIY "【膂力】" HIW "%2d |%3d   " HIY "【悟性】" HIW "%2d |%3d" NOR+YEL "   ┃\n" NOR , 
                ob->query("str"),
                ob->query_str(),
                ob->query("int"), 
                ob->query_int());

        if (mapp(my["family"]))
        {
                if( my["family"]["master_name"] )
                        line += sprintf( YEL "┃" HIG "【师承】" NOR "%-18.18s" YEL "┃" NOR,
                                my["family"]["master_name"] );
                else
                        line += sprintf( YEL "┃" HIG "【师承】" NOR "你还没有拜师      " YEL "┃" NOR );
        }
        else  
                line += sprintf( YEL "┃" HIG "【师承】" NOR "你还没有拜师      " YEL "┃" NOR );
        line += sprintf( HIY "【根骨】" HIW "%2d |%3d   " HIY "【身法】" HIW "%2d |%3d" NOR+YEL "   ┃\n" NOR , 
                ob->query("con"),           
                ob->query_con(),
                ob->query("dex"), 
                ob->query_dex());

        line += sprintf( YEL "┃" HIW "【帮派】" NOR "%-18.18s", stringp(ob->query("party/party_name"))?ob->query("party/party_name"):"自由人士");
        line += sprintf( YEL "┃" HIC "【拳脚】" NOR "%s" HIC "【兵器】" NOR "%s" NOR YEL "┃\n" NOR,ob->query("opinion/unarmed")? oprank[ob->query("opinion/unarmed")]:CYN "无评价    " NOR,ob->query("opinion/weapon")? oprank[ob->query("opinion/weapon")]:CYN "无评价    " NOR); 
        if (stringp(ob->query("degree")))
                line += sprintf( YEL "┃" HIW "【职务】" NOR "%" + sprintf("%d",18 + color_len(ob->query("degree"))) + "-s", ob->query("degree"));
        else
        if (stringp(ob->query("bunch/title")))
                line += sprintf( YEL "┃" HIW "【职务】" NOR "%" + sprintf("%d",18 + color_len(ob->query("party/title"))) + "-s", ob->query("party/title"));
        else
                line += sprintf( YEL "┃" HIW "【职务】" NOR "无                " );
        line += sprintf( YEL "┃" HIC "【内功】" NOR "%s" HIC "【轻功】" NOR "%s" NOR YEL "┃\n" NOR,ob->query("opinion/force")? oprank[ob->query("opinion/force")]:CYN "无评价    " NOR,ob->query("opinion/dodge")? oprank[ob->query("opinion/dodge")]:CYN "无评价    " NOR); 
        /*
        if (ob->query("is_vendor"))
                line += sprintf(YEL "┃" HIG "【职业】" NOR "商人              " );
        else
                line += sprintf(YEL "┃" HIG "【职业】" NOR "无                " );
        */
        line += sprintf(YEL "┃" HIG "【魅力】" NOR "%-10d        ", ob->query("meili"));
        line += sprintf( YEL "┃" HIY "【经验】" HIW "%-10d" HIY "【潜能】" NOR "%s%-10d" NOR YEL "┃\n" NOR ,my["combat_exp"],(int)ob->query("potential")>=(int)ob->query_potential_limit()?HIM:HIW,(int)ob->query("potential") - (int)ob->query("learned_points") );
        line += sprintf( YEL "┃" HIG "【威望】" NOR "%-18d" YEL "┃" NOR, ob->query("weiwang") );
        line += sprintf( HIY "【%s】" HIW "%-10d" HIY "【体会】" HIW "%s%-10d" NOR YEL "┃\n" NOR ,(ob->query("shen")>=0)?"正气":"邪气",ob->query("shen")?ob->query("shen"):0,my["combat_exp"] < 100000 ? HIR :
                        my["experience"] < ob->query_experience_limit() ? HIW : HIM,
                        (my["experience"] - my["learned_experience"]) );
        if (! ob->query("private_room"))
                line += sprintf(YEL "┃" HIW "【住宅】" NOR "%-18.8s" , "流浪街头");
        else
                line += sprintf(YEL "┃" HIW "【住宅】" NOR "%-18.8s" , ob->query("private_room/name") );
        line += sprintf( YEL "┃" HIY "【贡献】" HIW "%-10d" HIY "【灵惠】" NOR HIW "%-10d" NOR YEL "┃\n" NOR ,my["gongxian"] ,my["magic_points"] - my["magic_learned"] );
        /*
        if (mapp(my["couple"]))
        {
                line += sprintf(YEL "┃" HIW "【婚姻】" NOR "%-18.8s" , "结婚" + chinese_number(my["couple"]["married"]) + "次");
                line += sprintf( YEL "┃" HIY "【阅历】" NOR HIW "%-10d" NOR HIY "【戾气】"NOR HIW "%-10d" NOR YEL "┃\n" NOR ,ob->query("score")?ob->query("score"):0,ob->query("total_hatred")?ob->query("total_hatred"):0 );
                if (my["couple"]["have_couple"])
                {
                        line += sprintf(YEL "┃" HIW "【%s】" NOR "%-18.8s" YEL "┗━━━━━━━━━━━━━━━━━━┫\n" NOR , my["couple"]["couple_gender"],my["couple"]["couple_name"] + "(" + my["couple"]["couple_id"]  + ")");
                } else
                {
                        line += sprintf(YEL "┃" HIW "【伴侣】" NOR "%-18.8s" YEL "┗━━━━━━━━━━━━━━━━━━┫\n" NOR , "没有");
                }                       
                line += sprintf(YEL "┃" HIW "【子女】" NOR "%-56s" NOR YEL "┃\n", mapp(my["couple"]["child"]) ? my["couple"]["child"]["name"] : "没有");
        }
        */
        if (mapp(my["couple"]))
        {
                line += sprintf(YEL "┃" HIW "【婚姻】" NOR "%-18.8s" , my["couple"]["name"] ? "结婚" : "丧偶");
                line += sprintf(YEL "┃" HIY "【阅历】" NOR HIW "%-10d" NOR HIY "【戾气】"NOR HIW "%-10d" NOR YEL "┃\n" NOR ,ob->query("score")?ob->query("score"):0,ob->query("total_hatred")?ob->query("total_hatred"):0 );
                if (my["couple"]["name"])
                {
                        line += sprintf(YEL "┃" HIW "【%s】" NOR "%-18s" YEL "┗━━━━━━━━━━━━━━━━━━┫\n" NOR , "伴侣",my["couple"]["name"] + "(" + my["couple"]["id"]  + ")");
                } else
                {
                        line += sprintf(YEL "┃" HIW "【伴侣】" NOR "%-18.8s" YEL "┗━━━━━━━━━━━━━━━━━━┫\n" NOR , "没有");
                }                       
                line += sprintf(YEL "┃" HIW "【子女】" NOR "%-56s" NOR YEL "┃\n", mapp(my["couple"]["child_name"]) ? my["couple"]["child_name"] : "没有");
        }
        else
        { 
                line += sprintf( YEL "┃" HIW "【婚姻】" NOR "单身              " );
                line += sprintf( YEL "┃" HIY "【阅历】" NOR HIW "%-10d" NOR HIY "【戾气】"NOR HIW "%-10d" NOR YEL "┃\n" NOR ,ob->query("score")?ob->query("score"):0,ob->query("total_hatred")?ob->query("total_hatred"):0 );
                line += sprintf( YEL "┃" HIW "【伴侣】" NOR "没有              " YEL "┗━━━━━━━━━━━━━━━━━━┫\n" NOR );
                line += sprintf( YEL "┃" HIW "【子女】" NOR "%-56s" NOR YEL "┃\n", "没有" );
        }

        if (my["gender"] == "无性")
                line += sprintf( YEL "┃" HIW "【两性】" NOR "%-56s" NOR YEL "┃\n","你是个太监。" );
        else if (! ob->query("sex/times"))
        {
                if (my["gender"] == "女性")
                        line += sprintf( YEL "┃" HIW "【两性】" NOR "%-56s" NOR YEL "┃\n","你还是处女。" );
                else
                        line += sprintf( YEL "┃" HIW "【两性】" NOR "%-56s" NOR YEL "┃\n","你还是童男。" );
        } else
        {
                string *ks;
                        ks = keys(ob->query("sex"));
                        ks -= ({ "times", "first", "" });
                        if (sizeof(ks) >= 5)
                                line += sprintf( YEL "┃" HIW "【两性】" NOR "%-56s" NOR YEL "┃\n",
                                                "你曾经和数不清的人发生过关系，连自己都忘了有谁。");
                        else
			{
                                msg = "你曾经和" + implode(ks,"、") + "发生过关系。";
                                line += sprintf( YEL "┃" HIW "【两性】" NOR "%" + sprintf("%d", (56 + color_len(msg))) + "-s" NOR YEL "┃\n",
                                                "你曾经和" + implode(ks,"、") + "发生过关系。");
			}
        }

        line += sprintf(YEL "┃" HIW "【坐骑】" NOR "%-56s" NOR YEL "┃\n", mapp(ob->query("can_whistle")) ? "拥有" : "没有");
        
        if (ob->query("balance") <= 0)
                line += sprintf( YEL "┃" HIY "【钱庄】" HIY "没有积蓄                                                " NOR+YEL "┃\n" NOR );
        else
        {
                line += sprintf ( YEL "┃"  HIY "【钱庄】" NOR );
                line += sprintf (HIY"%-56.56s"NOR,
                MONEY_D->money_str((int)ob->query("balance")));
                line += sprintf ( NOR+YEL "┃\n" NOR );
        }
        cold=ob->query_temp("apply/cold_defence");
if (cold>=75) cold="最大"; else cold =cold+"％";
fire=ob->query_temp("apply/fire_defence");
if (fire>=75) fire="最大"; else fire =fire+"％";
lightning=ob->query_temp("apply/lightning_defence");
if (lightning>=75) lightning="最大"; else lightning =lightning+"％";
poison=ob->query_temp("apply/poison_defence");
if (poison>=75) poison="最大"; else poison =poison+"％";
wind=ob->query_temp("apply/wind_defence");
if (wind>=75) wind="最大"; else wind =wind+"％";

        line += HIW+"\n\n 防冰" +NOR+"："+cold +"\t   "+HIG+"防毒" + NOR+"："+poison+NOR+YEL+"\t   防风" +NOR+"："+ wind;
        line += HIR+"\n 防火" +NOR+"："+fire + "\t\t\t   "+HIB+"防电" + NOR+"："+lightning;
        line += sprintf( YEL "┃                                                                ┃\n" NOR );
        line += sprintf( YEL "┃" NOR HIY " 武学宗师： %s" NOR HIY "    任督二脉： %s" NOR HIY "   元婴出世： %s" NOR HIY "    转世重生：%s " NOR YEL "┃\n" NOR,
                ultrap(ob) ? "○" : HIC "×", ob->query("breakup") ? "○" : HIC "×", ob->query("animaout") ? "○" : HIC "×", ob->query("reborn") ? "○" : HIC "×" );
        
        /*
        msg = "";
        if (ultrap(ob))
                msg = " 你已经成为大宗师";
        if (ob->query("breakup"))
                msg += "、打通任督二脉";
        if (ob->query("animaout"))
                msg += "、修成元婴出世";
        if (ob->query("tianmo_jieti/times"))
                msg += "、天魔解体" + chinese_number((int)ob->query("tianmo_jieti/times")) + "次";

        if (msg != "")
        {       
                msg += "。";
                line += sprintf( YEL "┃" NOR HIC "%-64s" NOR YEL "┃\n" NOR, msg );
                line += sprintf( YEL "┃                                                                ┃\n" NOR );
        }

        if( my["max_jing"] >= my["eff_jing"])
                line += sprintf( YEL "┃" HIC" 精  "NOR"：%-24s   ", tribar_graph(my["jing"], my["eff_jing"], my["max_jing"], status_color(my["jing"], my["max_jing"])) + tribar_graph3(jings));
        else
                line += sprintf( YEL "┃" HIC" 精  "NOR"：%-24s   " , tribar_graph2(my["jing"], my["max_jing"], my["max_jing"], status_color(my["jing"], my["max_jing"]))+ tribar_graph3(jings));

        if( my["max_jingli"] > 0 )
                line += sprintf( HIC "精力"NOR"：%-24s"+ NOR+YEL+"┃\n"NOR, tribar_graph(my["jingli"], my["max_jingli"], my["max_jingli"], status_color(my["jingli"], my["max_jingli"])));
        else
                line += sprintf( HIC "精力"NOR "：" HIG "%-24s"+ NOR+YEL+"┃\n"NOR, blank_string );

        if( my["max_qi"] >= my["eff_qi"])
                line += sprintf( YEL "┃" HIC" 气  "NOR"：%-24s   ", tribar_graph(my["qi"], my["eff_qi"], my["max_qi"], status_color(my["qi"], my["max_qi"])) + tribar_graph3(qis));
        else    
                line += sprintf( YEL "┃" HIC" 气  "NOR"：%-24s   ", tribar_graph2(my["qi"], my["max_qi"], my["max_qi"], status_color(my["qi"], my["max_qi"])) + tribar_graph3(qis));

        if( my["max_neili"] > 0 )
                line += sprintf( HIC "内力"NOR"：%-24s"+ NOR+YEL+"┃\n"NOR, tribar_graph(my["neili"], my["max_neili"], my["max_neili"], status_color(my["neili"], my["max_neili"])));
        else
                line += sprintf( HIC "内力"NOR "：" HIG "%-24s"+ NOR+YEL+"┃\n"NOR, blank_string );

        if( ob->max_food_capacity() > 0 )
                line += sprintf( YEL "┃" HIC" 食物"NOR"：%-24s   ", tribar_graph(my["food"], ob->max_food_capacity(), ob->max_food_capacity(), YEL));
        else
                line += sprintf( YEL "┃" HIC" 食物"NOR"："YEL   "%-24s"+ NOR+YEL+"┃\n"NOR, blank_string );
        
        if( ob->max_water_capacity() > 0 )
                line += sprintf( HIC "饮水"NOR"：%-24s"+ NOR+YEL+"┃\n"NOR , tribar_graph(my["water"], ob->max_water_capacity(), ob->max_water_capacity(), CYN));
        else
                line += sprintf( HIC "饮水"NOR CYN"：%-24s"+ NOR+YEL+"┃\n"NOR, blank_string );

        */          
        line += sprintf( YEL "┣━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┫\n" NOR );        

        line += sprintf( YEL "┃" HIB "【杀生次数】" NOR HIR"%6d位"NOR, 
                (int)mci["MKS"] + (int)mci["PKS"]);
        line += sprintf( YEL "┃" HIB "【杀死玩家】" NOR HIR"%6d位"NOR, 
                (int)mci["PKS"]);
        line += sprintf( YEL "┃" HIB "【有意杀害】" NOR HIR"%6d位"NOR, 
                (int)mci["WPK"]);
        line += YEL "┃\n" NOR;

        line += sprintf( YEL "┃" HIB "【击晕玩家】" NOR HIR"%6d位"NOR, 
                (int)mci["DPS"]);
        line += sprintf( YEL "┃" HIB "【正派人士】" NOR HIR"%6d位"NOR, 
                (int)mci["DPS_GOOD"]);
        line += sprintf( YEL "┃" HIB "【邪派人士】" NOR HIR"%6d位"NOR, 
                (int)mci["DPS_BAD"]);
        line += YEL "┃\n" NOR;

        line += sprintf( YEL "┣━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┫\n" NOR );

        line += sprintf( YEL "┃" NOR HIB " 你目前的杀气是：%s%-47d"NOR YEL "┃\n" NOR,
                         ((int)ob->query("pk_score")>2000)?HIR:((int)ob->query("pk_score")>1000)?HIM:HIW,
                         (int)ob->query("pk_score") );

        msg = "";
        if ((int)mci["dietimes"])
 	        msg = sprintf(HIB " 你到目前为止总共到黑白无常那里"
				"串门%s次。" NOR,
				chinese_number(mci["dietimes"]));
        if (msg != "")
                line += sprintf( YEL "┃" NOR "%" + sprintf("%d",(64 + color_len(msg))) + "-s" NOR YEL "┃\n" NOR, msg );

        msg = "";
        if (stringp(mci["last_die"]))
			msg += sprintf(HIB " 你最后一次是%s。" NOR,
					mci["last_die"]);
        if (msg != "")
                line += sprintf( YEL "┃" NOR "%" + sprintf("%d",(64 + color_len(msg))) + "-s" NOR YEL "┃\n" NOR, msg );
        line += YEL "┗━━━━━━━━━━━━━━━━━━━━━━━━━【个人档案】━┛\n" NOR;

         write(line);
         return 1;
}


string display_attr(int gift, int value)
{
        if( value > gift ) return sprintf( HIY "%6s" NOR, chinese_number(value) );
        else if( value < gift ) return sprintf( CYN "%6s" NOR, chinese_number(value) );
        else return sprintf("%6s", chinese_number(value));
}

string status_color(int current, int max)
{
        int percent;

        if( max ) percent = current * 100 / max;
        else percent = 100;

        if( percent > 100 ) return HIC;
        if( percent >= 90 ) return HIG;
        if( percent >= 60 ) return HIY;
        if( percent >= 30 ) return YEL;
        if( percent >= 10 ) return HIR;
        return HIB;
}

string tribar_graph(int val, int eff, int max, string color)
{
        return color + bar_string[0..(val*12/max)*2-1]
                + ((eff > val) ? blank_string[(val*12/max)*2..(eff*12/max)*2-1] : "") + NOR;
}
string tribar_graph2(int val, int eff, int max, string color)
{
        return color + bar_string[0..(val*12/max)*2-1]
                + ((eff > val) ? blank_string2[(val*12/max)*2..(eff*12/max)*2-1] : "") + NOR;
}
string tribar_graph3(int a)
{
        return BLU + blank_string3[0..(23-a)] + NOR;
}
int help(object me)
{
        write(@HELP
指令格式 : score
           score <对象名称>                   (巫师专用)

这个指令可以显示你(你)或指定对象(含怪物)的基本资料。
基本资料的设定请参阅 'help setup'。

see also : hp
HELP
    );
    return 1;
}

