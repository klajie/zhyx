#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能自己运功使用吸星大法。\n");
				
		 if ((int)me->query_skill("xixing-dafa", 1) < 350)
                return notify_fail("你的吸星大法等级不够。\n");		
				

        if ((int)me->query("neili") < 500)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_temp("xixing-dafa/xineili"))
                return notify_fail("你已经在运功中了。\n");
		if ((int)me->query_temp("xixing-dafa/xijing"))
                return notify_fail("你正在运功吸精入体中。\n");
		if ((int)me->query_temp("xixing-dafa/xiqi"))
                return notify_fail("你正在运功吸气入体中。\n");
		 if (me->query("family/family_name") != "日月神教")     
                return notify_fail("你已非日月神教弟子，无缘再用此绝学了。\n");

        skill = me->query_skill("xixing-dafa",1);
        me->add("neili", -100);
        me->receive_damage("qi", 0);
        message_combatd(HIY "$N" HIY "深深呼入一口气，运上"HIG"“吸力入体”"HIY "，顿时全身真气蒸腾，被罡劲所笼罩。\n" NOR, me);           
        me->set_temp("xixing-dafa/xineili", 1);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me:), skill);
        if (me->is_fighting()) me->start_busy(3);
        return 1;
}

void remove_effect(object me)
{
        if (me->query_temp("xixing-dafa/xineili"))
        {                
                me->delete_temp("xixing-dafa/xineili");
                tell_object(me, "你的吸力入体运行完毕，将内力收回丹田。\n");
        }
}
