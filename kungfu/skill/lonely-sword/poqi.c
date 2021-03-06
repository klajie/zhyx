// Code of JHSH
// pojian.c 独孤九剑「破气式」
// qfy July 5, 1996.

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	string msg;
	object weapon;
	int dugu_skill;

	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("破气式只能对战斗中的对手使用。\n");
		
	if( !objectp(weapon = me->query_temp("weapon")) ||
            weapon->query("skill_type") != "sword")
		return notify_fail("你手中无剑，如何使用独孤九剑？\n");

	if( (int)me->query_skill("lonely-sword", 1) < 90 || (int)me->query("max_neili") < 400 )
		return notify_fail("你的独孤九剑或内力修为不够，还未学成「破气式」。\n");

        if( me->query("neili") <= 100 )
                return notify_fail("你的内力不够！\n");

	if ((int)target->query("neili") < 1)
		return notify_fail("对方内力已经枯竭了，不需要再破气。\n");

	dugu_skill = me->query_skill("lonely-sword",1);

	msg = CYN "$N潜运独孤九剑「破气式」，运气贯剑使其由利返钝，毫无花俏地直刺$n的丹田。\n";
	message_vision(msg, me, target);

        if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/2 || !living(target))
	{
		msg = HIR "$n只觉的丹田一阵刺痛，内力飞泄而出，惊怒之下，不由喷出一口鲜血！\n" NOR;

		target->add("neili",-dugu_skill*5);
		message_vision(msg, me, target);
		target->start_busy(1+random(2));
		me->start_busy(2);
	} else {
		msg = "可是$p看破了$P的剑路，还招挡开。\n" NOR;
		me->start_busy(2 + random(2));
		message_vision(msg, me, target);
	}

	me->add("neili", -dugu_skill/2);

	return 1;
}
