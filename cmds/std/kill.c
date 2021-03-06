// kill.c

#include <ansi.h>
inherit F_CLEAN_UP;

string *master=({
"玄慈大师",
"张三丰",
"灭绝师太",
"岳不群",
"洪七公",
"黄药师",
"丁春秋",
"无崖子",
"杨过",
"小龙女",
"丘处机",
"玄冥老祖",
"何太冲",
"张无忌",
"向问天",
"虚竹",
"洪安通",
"金轮法王",
"司徒焚",
"文泰来",
"血刀老祖",
"何红药",
"黑白子",
"王维扬",
"白自在",
"左冷禅",
"莫大",
"欧阳锋",
"胡斐",
"慕容复",
"段正淳",
"商剑鸣",
"苗人凤",
"公孙止" });
string *npc=({
"封弓影",
"杨永福",
"唐楠",
"刘素素",
"钱眼开",
"曾柔",
"天乙道人",
"天柏道人",
"天松道人",
"建除道人",
"多隆",
"郑克爽",
"冯锡范",
"玄贞道长",
"徐天川",
"樊纲",
"风际中",
"祁彪清",
"关安基",
"贾老六",
"钱老本",
"海公公",
"小桂子",
"齐元凯",
"神照上人",
"张康年",
"赵齐贤",
"康亲王",
"秦伟邦",
"姚春",
"胡掌柜",
"归钟",
"归二娘",
"归辛树",
"柳大洪",
"张德贵",
"程老板",
"平一指",
"刘老实",
"如花",
"慕容豪",
"时九公",
"万青山",
"凌飞雪",
"萧万喜",
"张兰香",
"金复还",
"梁喜禄",
"书痴",
"净明",
"净玄",
"慧通禅师",
"陈继盛",
"梁兴禄",
"张衡",
"萧群",
"李可秀",
"胡庆余",
"程嘲风",
"唐槐",
"唐掌柜",
"一灯大师",
"薛老板",
"傅思归",
"冯正东",
"甄有庆",
"王合计",
"范一飞",
"吕正平",
"高三娘子",
"风良",
"白二",
"陈七",
"史镖头",
"林震南",
"郑镖头",
"王夫人",
"崔镖头",
"贾人达",
"余人彦",
"戈什哈",
"沙天江",
"凤一鸣",
"胖商人",
"瘦商人",
"胡雪源",
"高丽商",
"秦掌柜",
"萧南忠",
"周逸风",
"朱饮",
"朱政",
"韩云",
"邱航",
"黄真",
"郭芙",
"赵德言",
"周松天",
"巫攀冰",
"马超兴" }); 




int main(object me, string arg)
{
        object obj, env;
        string *killer, callname;

        if (me->is_chatter())
                return 0;

        if (environment(me)->query("no_fight"))
                return notify_fail("这里不准战斗。\n");

        if (! arg)
                return notify_fail("你想杀谁？\n");

        if (! objectp(obj = present(arg, environment(me))))
                return notify_fail("这里没有这个人。\n");

        if (! obj->is_character() || obj->is_corpse())
                return notify_fail("看清楚一点，那并不是活物。\n");

        if (obj == me)
                return notify_fail("用 suicide 指令会比较快:)。\n");
 
      /*  if (! living(obj) &&  obj->is_player())
                return notify_fail("你还是等人家醒过来再说吧。\n");*/

        if (obj->query_temp("sleeped"))
                return notify_fail("你还是等人家醒过来再说吧。\n");

       env = environment(obj); 
       if ( me->query("special_skill/lonely") )
       {
           if (me->query_condition("killer") && obj->is_player())
           return notify_fail("你现在是官府捉拿的要犯，不可造次！\n");
       }
     //  else
     //  if (obj->is_player()  && file_name(env)[0..5] != "/d/pk/")    
     //     return notify_fail("只有在屠人场内才能PK!\n");  
   
    /*   if (obj->is_player() && me->query("quest_count") < 300
           && file_name(env)[0..5] != "/d/pk/")    
           return notify_fail("完成300个门派任务才能袭击一次玩家。\n"); */
                
     //   if (obj->is_player())  return notify_fail("目前特殊时期，暂时关闭PK。\n");  

        if (arrayp(me->query_team()) &&
            member_array(obj, me->query_team()) != -1)
                return notify_fail("连你自己队伍中的人也要杀吗？太不人道了吧！\n");

        if (me->is_fighting(obj) && me->is_killing(obj->query("id")))
                return notify_fail("你正在和人家生死相扑呢。\n");

        if ((int)obj->query_condition("die_guard"))
                return notify_fail("这个人正被官府保护着呢，还是别去招惹。\n");

        if ( obj->query("age") < 30 && ( obj->query("special_skill/emperor")
             || obj->query("special_skill/queen") ) )
                return notify_fail("此人受上天庇佑且又尚未成年，还是别去招惹。\n");

        if ( obj->is_player() && me->query("age") < 30 
             && ( me->query("special_skill/emperor")
             || obj->query("special_skill/queen") ) )
                return notify_fail("你在成年之前不能袭击玩家!\n");

        if (! me->is_fighting(obj) &&
            me->query("qi") < me->query("max_qi") * 3 / 10)
                return notify_fail("你现在没有力气战斗了。\n");

        //记录屠杀funquest npc的人
    /*  if ( ! userp(obj) && strsrch(npc, obj->query("name")) > 0
             && ! obj->query_temp("born_time") )
           log_file("static/killnpc", sprintf("%s(%s) 杀 %s at %s.\n",
             me->name(1), me->query("id"), obj->query("name"), ctime(time()))); */
             
  if ( ! userp(obj) && ! obj->query_temp("born_time") 
             && member_array(obj->query("name"), npc) != -1) 
  log_file("static/killnpc", sprintf("%s(%s) 杀 %s at %s.\n",
             me->name(1), me->query("id"), obj->query("name"), ctime(time()))); 
             
  /*  if ( ! userp(obj) && ! obj->query_temp("born_time") 
             && member_array(obj->query("name"), npc) != -1) 
         return notify_fail("趣味任务npc不得杀害!\n");  */
  
  if ( ! userp(obj) && ! obj->query_temp("born_time") 
             && member_array(obj->query("name"), master) != -1) 
  log_file("static/killmaster", sprintf("%s(%s) 杀 %s at %s.\n",
             me->name(1), me->query("id"), obj->query("name"), ctime(time()))); 
             
   

        callname = RANK_D->query_rude(obj);

        if (obj->query("can_speak"))
        {
                if (! living(obj))
                        message_vision(HIR "\n$N" HIR "看了看晕倒在地的$n" HIR "，冷笑"
                                       "一声，喝道：" + callname + HIR  "，给我见阎王去"
                                       "吧！\n\n" NOR, me, obj);
                else if (random(3) > 1)
                        message_vision(HIR "\n$N" HIR "对著$n" HIR "喝道：" + callname +
                                       HIR  "，今日不是你死就是我活！\n\n" NOR, me, obj);
                else
                        message_vision(HIR "\n$N" HIR "对著$n" HIR "喝道：" + callname +
                                       HIR "，明年今日就是你的忌日！\n\n" NOR, me, obj);
        }

        switch(obj->accept_kill(me))
        {
        case 0:
                return (! objectp(obj));
        case -1:
                return 1;
        default:
        }

        if (userp(me) && userp(obj) && ! obj->is_want_kill(me->query("id")))
                me->want_kill(obj);

        me->kill_ob(obj);
        if (living(obj) && ! userp(obj))
                obj->kill_ob(me);
        else
                obj->fight_ob(me);

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : kill <人物>
 
这个指令让你主动开始攻击一个人物，并且试图杀死对方，kill 和 fight 最大的
不同在於双方将会真刀实枪地打斗，也就是说，会真的受伤。由於 kill 只需单方
面一厢情愿就可以成立，因此你对任何人使用 kill 指令都会开始战斗，通常如果
对方是 NPC 的话，他们也会同样对你使用 kill。

当有人对你使用 kill 指令时会出现红色的字样警告你，对於一个玩家而言，如果
你没有对一名敌人使用过 kill 指令，就不会将对方真的打伤或杀死。

其他相关指令: hit, fight

HELP);
        return 1;
}

