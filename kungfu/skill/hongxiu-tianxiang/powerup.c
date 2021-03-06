// powerup.c 红袖添香

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用红袖添香来提升自己的战斗力。\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_temp("powerup"))
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        me->add("neili", -500);
        me->receive_damage("qi", 0);

	message_combatd(HIW "$N" HIW "运起红袖添香，肌肤变得晶莹剔透，光滑异常，散发出令人心颤的寒气。\n" NOR, me);

	me->add_temp("apply/attack", skill * 2 / 3);
	me->add_temp("apply/parry", skill / 3);
	me->add_temp("apply/dodge", skill / 3);
	me->add_temp("apply/unarmed_damage", skill / 5);
	me->add_temp("apply/damage", skill / 5);
	me->set_temp("powerup", 1);

	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill);

	if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if ((int)me->query_temp("powerup"))
        {
                me->add_temp("apply/attack", - (amount * 2 / 3));
                me->add_temp("apply/parry", - (amount / 3));
                me->add_temp("apply/dodge", - (amount / 3));
                me->add_temp("apply/unarmed_damage", - (amount / 5));
                me->add_temp("apply/damage", - (amount / 5));
                me->delete_temp("powerup");
                tell_object(me, "你的红袖添香运行完毕，将内力收回丹田。\n");
        }
}

