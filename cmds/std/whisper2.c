// whisper.c

#include <ansi.h>

inherit F_CLEAN_UP;

int reply_whisper(object me, object who, string msg);

int main(object me, string arg)
{
	string dest, msg;
       int r;
	object ob;
        object env;
        mixed info;

	if (! arg )
       return notify_fail("你要对谁耳语些什么？\n");
       if ( sscanf(arg, "%s to %s", msg, dest) != 2 
            && sscanf(arg, "%s %s", dest, msg) != 2 )
	return notify_fail("指令格式：whisper <讯息> to <某人>\n");

        env = environment(me);
	ob = present(dest, env);

	if (! ob || ! ob->is_character())
		return notify_fail("你要对谁耳语？\n");

        if (ob == me)
		return notify_fail("你无法将嘴凑到自己的耳朵旁说话。\n");

        if (me->ban_say(1))
                return 0;

        if (info = env->query("no_say"))
        {
                if (stringp(info))
                {
                        write(info);
                        return 1;
                }

                write("这个地方不能讲话。\n");
                return 1;
        }

        if (me->query("doing") == "scheme")
        {
                if (me->query("jing") < 100)
                        return notify_fail("你现在的精神不济，等一会儿吧。\n");
                me->add("jing", -50);
        }

	write(WHT "你在" + ob->name() + WHT "的耳边悄声说道：" +
	      msg + "\n" NOR);
	tell_room(environment(me), me->name() + "在" + ob->name()
		+ "耳边小声地说了些话。\n", ({ me, ob }));

	if (! userp(ob)) ob->relay_whisper(me, msg);
	else
		tell_object(ob, WHT + me->name() +
				WHT "在你的耳边悄声说道：" + msg + "\n" NOR);
      //配合长安府传暗号任务新增部分
       if ( ! userp(ob) )
       {
          if ( me->query("changanjob/kind") != "whisper" ||
               me->query("changanjob/target") != ob->name() )  
              tell_room(environment(me), CYN + ob->name() + "说道："NOR + HIG
              "你在我耳边即即歪歪说什么?真是牛头不对马嘴。\n"NOR);
          else
              {
                 if ( me->query("changanjob/whisper") )
                 {
                      tell_room(environment(me), CYN + ob->name() + "说道："NOR 
                                 + HIG "啊,多谢把暗号带到。\n"NOR);           
                      if ( me->query("changanjob/whisper") == msg )
                           me->set("changanjob/ok",1);                     
                      me->delete("changanjob/whisper");  
                 } else
                 {
                      tell_room(environment(me), CYN + ob->name() + "说道："NOR 
                                  + HIG"你已经告诉我暗号了呀!\n"NOR);   
                 }            
                 
	if (! userp(ob)) 
       {
              r = 0;
              if (me->query("bang_quest") && me->query("bang_quest/type") == "传口信")
                      r = reply_whisper(me,ob,msg);
              if (!r)
                      ob->relay_whisper(me, msg);
       }
	else
		tell_object(ob, WHT + me->name() +
				WHT "在你的耳边悄声说道：" + msg + "\n" NOR);
               }
       }
	return 1;
}

int reply_whisper(object me, object who, string msg)
{
        mapping bang_quest,b;

        int exp;
        int pot;
        int score;
        int weiwang;

        bang_quest = me->query("bang_quest");

        //传错人了
        if (bang_quest["target"] != base_name(who))
                return 0;

        //传错话了
        if (msg != bang_quest["send_msg"])
                return 0;

        message_sort("$N面色凝重，一边听着一边对$n使劲的点头：“这位" +
                     RANK_D->query_respect(who) +
                     "，多谢你把话带到！”\n", who, me);

        // 奖励
        me->add("pk_score",-2);
        if (me->query("pk_score") < 0) me->set("pk_score",0);

        exp = bang_quest["bonus"];
        exp += random(exp/2);
        exp += me->query("combat_exp")/5000;
        pot = exp/(2 + random(2));
        score = 5 + random(10);
        weiwang = 5 + random(10);

        b = ([ "exp" : exp,
               "pot" : pot,
               "score" : score,
               "weiwang" : weiwang,
               "prompt": "在把口信传给" + who->name() +
                         HIG "的过程中，经过锻炼" ]);

        QUEST_D->delay_bonus(me, b);

        me->delete("bang_quest");
        me->add_temp("finish_bang_times",1);

        return 1;
}
int help(object me)
{
	write( @TEXT
指令格式：whisper <讯息> to <某人> 

这个指令可以用来和同一房间中的人耳语，包括 NPC 在内。
TEXT );
	return 1;
}
