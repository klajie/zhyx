// shuang.c 国士无双
// 运用技能，随机选择一种性格 by xiner 2009/4/05


#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "国士无双" NOR; }

int perform(object me, string skill)
{
	if (! me->query("reborn"))
		return notify_fail("你尚未转世重生，无法使用此技能！\n");

	message_vision(HIC "$N" HIC "闭目端坐，冥神思索，试图"
                       "改变自己的先天性格。\n" NOR, me);   

	me->set_short_desc("正端坐在地上冥思苦想");
	me->delete_temp("pending/shuang");   
	me->start_busy((:call_other, __FILE__, "check" :), 
			(:call_other, __FILE__, "halt" :)); 
	return 1;
}

int check(object me)
{
	string char;

	if ( me->add_temp("pending/shuang", 1) < (30 + random(10)) )
		return 1;
   
	message_vision(HIW "$N" HIW "缓缓睁开双目，"
                    "结束了这次冥想。\n" NOR, me);

	if (random(6) != 0 )
		tell_object(me, HIC "\n你感到这次冥想并没有什么效果，"
                      "无法回忆起当初选择天赋的情景。\n"NOR);
	else
	{
        	tell_object(me, HIG"\n突然你感到心智顿开，"
                	         "回忆起世外桃源的情景重新选择了天赋。\n"NOR);

	        switch (random(4))
        	{
			case 0:
				char = "心狠手辣";
				break;
			case 1:
				char = "狡黠多变";
				break;
			case 2:
				char = "阴险奸诈";
				break;
			default:
				char = "光明磊落";
				break;
        	}
	        tell_object(me, HIW"\n你的天赋变成了"HIR +char+ HIW "。\n\n"NOR);
        	me->set("character", char);
	}
	me->set_short_desc(0);  
	me->delete_temp("pending/shuang");
	return 0;
}

int halt(object me)
{            
	message_vision(HIG"$N睁开双眼，结束了这此冥想。\n"NOR, me);        
	me->set_short_desc(0);  
	me->delete_temp("pending/shuang");     
	return 1;
}

