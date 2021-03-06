// updated by kasumi
#include <ansi.h>
inherit F_CLEAN_UP;

#define FRE "「" HIW "雪山神功" NOR "」"

void remove_effect(object me,int amount);

int exert(object me, object target)
{
        int skill;

        if (userp(me) && ! me->query("can_perform/xueshan-shengong/freezing"))
                return notify_fail("你所学的内功中没有这种功能。\n");

        if ((int)me->query_temp("freezing"))
                return notify_fail("你现在正在施展" FRE "。\n");

        if (target != me)
                return notify_fail(FRE "只能对自己使用。\n");

        skill = me->query_skill("xueshan-shengong", 1);

        if (me->query("con") < 32)
                return notify_fail("你的先天根骨不足，无法施展" FRE "。\n");

        if (skill < 200)
                return notify_fail("你的雪山神功等级不够，难以施展" FRE "。\n");

        if ((int)me->query("max_neili") < 2200)
                return notify_fail("你的内力修为不足，难以施展" FRE "。\n");

       

        if ((int)me->query("neili") < 500)
                return notify_fail("你目前的内力不够，难以施展" FRE "。\n");

        me->add("neili", -200);

        message_combatd(HIW "$N" HIW "一声冷笑，体内雪山神功迅速疾转数个周"
                        "天，霎时间透骨的寒意漫向四方。\n" NOR, me);
        me->set_temp("freezing", 1);
	    	me->add_temp("apply/armor", skill / 2);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill/2 :), skill);
        if (me->is_fighting())
                me->start_busy(3);

        return 1;
}

void remove_effect(object me,int amount)
{
        if (me->query_temp("freezing"))
        {
			       me->add_temp("apply/armor", -amount);
             me->delete_temp("freezing");
             tell_object(me, "你的" FRE "运行完毕，将内力收回丹田。\n");
        }
}

