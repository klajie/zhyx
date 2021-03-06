//kingkong.c 大力金刚

#include <ansi.h>
#include <combat.h>

inherit F_CLEAN_UP;
inherit F_SSERVER;

string name() { return HIR "大力金刚" NOR; }



#define KINGKONG "「" HIR "大力金刚" NOR "」"

int perform(object me, object target)
{
        string msg;
        int ap, dp, count;

        if (! me->query("reborn"))        
            return notify_fail("你尚未转世重生，无法使用此技能！\n");

        if (! me->is_fighting())
                return notify_fail(KINGKONG "只能对战斗中的对手使用。\n");

        target = me->select_opponent();

        if (! target || ! target->is_character()
           || target->query("not_living"))
                return notify_fail("你打算对谁施展" KINGKONG  "？\n");

//	if ( ! target->query_temp("no_die") )
//		return notify_fail("对方并没有运起不死金身呀 ？\n");

	if ( ! target->query_temp("no_die") )
	{
		if ((int)me->query_temp("jingang"))
			return notify_fail("你已经在运功中了。\n");

		if ((int)me->query("neili") < 500)
			return notify_fail("你的真气不够，无法施展「大力金刚」！\n");

		message_vision( HIR "$N" HIR "面色突然变得赤红，全身真力全数灌入手臂，"
			"奋不顾身的扑向$n。\n\n" NOR, me, target);

		count = (int)me->query("str");
		me->add_temp("str", count);
		me->set_temp("jingang", 1);
		me->start_call_out((: call_other, __FILE__, "remove_effect", me, count :), 50);
		me->add("neili", -500);

	}
	else
	{
		message_vision( HIR "$N" HIR "面色突然变得赤红，双手灌入巨大真力，"
			"重重一招袭向$n。\n\n" NOR, me, target);

		ap = me->query_str(); 
		dp = target->query_con();

		if ( ap / 2 + random(ap) > dp )
		{
			target->delete_temp("no_die");

			message_vision(CYN"只听$n" CYN"闷哼一声，"
				"不死金身竟被$N击溃！\n\n"NOR, me, target);

			tell_object(target, HIW"你的不死金身被"NOR + me->name() 
        	                + HIW"破除了！\n\n"NOR);           
		} else
			message_vision(HIY"只见$n" HIY"硬生生接下$N这一招，"
                	            "不死金身丝毫不为所动！\n\n"NOR, me, target);
		me->start_busy(3 + random(3));
	}
	return 1;
}

void remove_effect(object me, int amount)
{
	if ((int)me->query_temp("jingang"))
	{
		me->add_temp("str", -amount);
		me->delete_temp("jingang");
		tell_object(me, HIR "你感觉双臂中的真力消耗殆尽，面色逐渐恢复正常。\n"NOR);
	}
}
