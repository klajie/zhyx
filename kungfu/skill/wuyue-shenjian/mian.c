#include <ansi.h>
#include <combat.h>

#define MIAN "「" HIW "绵里藏针" NOR "」"

inherit F_SSERVER;
inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int perform(object me, object target)
{
        object weapon;
        string msg;
		int count;

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，难以施展" MIAN "。\n");

        if (me->query_skill("force") < 300)
                return notify_fail("你的内功的修为不够，难以施展" MIAN "。\n");

        if (me->query_skill("wuyue-shenjian", 1) < 400)
                return notify_fail("你的五岳神剑修为不够，难以施展" MIAN "。\n");

        if (! me->query("reborn"))         
                return notify_fail("你尚未转世重生，无法领会此绝招！\n"); 

        if (me->query("neili") < 500)
                return notify_fail("你的真气不够，难以施展" MIAN "。\n");

        if (me->query_skill_mapped("parry") != "wuyue-shenjian")
                return notify_fail("你没有激发五岳神剑为招架，难以施展" MIAN "。\n");
				
		if ((int)me->query_temp("wysj_mian"))
                return notify_fail("你已经在施展" MIAN "了。\n");
				
		if (me->is_fighting())
                me->start_busy(3);
                
        count=(int) (me->query_skill("wuyue-shenjian", 1)/3);        
		msg = HIW "$N" HIW "轻轻一抖手中的" + weapon->name() + HIW "，只见剑芒闪烁，已然用上了五岳神剑中恒山派绝学“绵里藏针”。\n" NOR;
		message_combatd(msg, me, target);               
		me->add("neili", -200);            
		me->set_temp("wysj_mian", 1);
		me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, count :), count);            
        
        return 1;
}
        

void remove_effect(object me, int amount)
{
        if (me->query_temp("wysj_mian"))
        {    	
        	me->delete_temp("wysj_mian");
        	tell_object(me, "你的" MIAN "运行完毕，将内力收回丹田。\n");
        }
}