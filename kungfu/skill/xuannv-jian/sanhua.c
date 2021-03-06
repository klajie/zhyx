#include <ansi.h>
#include <combat.h>

#define SANHUA "「" HIM "天女散花步" NOR "」"

inherit F_SSERVER;

void remove_effect(object me, int amount);


int perform(object me, object target)
{
        string msg;
	 int level, count;
        
        if ((level = me->query_skill("xuannv-jian", 1)) < 250)
                return notify_fail("你的玄女剑法还不够熟练，难以施展" SANHUA "。\n" NOR);

        if ((int)me->query("neili") < 600)
                return notify_fail("你现在真气不足，难以施展" SANHUA "。\n" NOR);

        if (me->query_temp("sanhua"))
                return notify_fail("你已经运起" SANHUA "了。\n");

       
        msg = HIM "\n$N踏出天女散花步，身形轻盈无比，不带一丝凡间俗气。\n"
                  "其景宛若仙子下凡，静若处子，动若疾风，霞光四射。\n"
                  "看得众人不禁如痴如醉，流连忘返，竟似不知身在何处。\n" NOR;       

        message_sort(msg, me);

        count = level / 20;       

        if (me->is_fighting())
                me->start_busy(2);

        me->add_temp("dex", count);
        me->add_temp("apply/dodge", count * 6);	
        me->set_temp("sanhua", 1);
        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, count :),  level / 3);  
        me->add("neili", -400);
        return 1;

}

void remove_effect(object me, int amount)
{
        if ((int)me->query_temp("sanhua"))
        {
                me->add_temp("dex", -amount);
                me->add_temp("apply/dodge", - amount * 6);
                me->delete_temp("sanhua");
                tell_object(me, "你的" SANHUA "运用完毕，将内力收回丹田。\n");
        }
}
