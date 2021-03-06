// shield.c 太极神功护体

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用太极神功来提升自己的防御力。\n");

        if ((int)me->query("neili") < 150)
                return notify_fail("你的真气不够。\n");

        if ((int)me->query_temp("shield"))
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        me->add("neili", -100);
        me->receive_damage("qi", 0);

        message_combatd(HIY "$N" HIY "双手平挥，运起太极神功，"
                        "只见一股雾气弥漫在$N" HIY "四周！\n" NOR, me);

        me->add_temp("apply/defense", skill / 3);
        me->set_temp("shield", 1);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 3:), skill);

        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("shield"))
        {
                me->add_temp("apply/defense", -amount);
                me->delete_temp("shield");
                tell_object(me, "你的太极神功运行完毕，将内力收回丹田。\n");
        }
}

