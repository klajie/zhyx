// 踏雪无痕
//created by kasumi

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill,lv;
		skill = me->query_skill("chess",1);
		
		if (skill<300)
		      return notify_fail("你弈棋之道不够纯熟，无法运功。\n");

        if (target != me)
                return notify_fail("你只能用踏雪无痕来提升自己的有效轻功。\n");

        if ((int)me->query("neili") < 150)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_temp("kl/taxue"))
                return notify_fail("你已经在运功中了。\n");
				
		if ((int)me->query_temp("kl/wuji"))
                return notify_fail("你已经运起了日月无极，无法同时再运用踏雪无痕了。\n");

        
        me->add("neili", -100);
        me->receive_damage("qi", 0);
		message_vision(MAG"$N气运丹田，高纵上跃，矫若游龙，宛似凌空飞行，飘然若仙！\n" NOR, me);        
        me->add_temp("apply/dodge", skill / 3);       
        me->set_temp("kl/taxue", 1);

		if ( (lv = me->query_skill("chess", 1)) >= 200 && me->query("family/family_name") == "昆仑派")
		{
			if (me->can_improve_skill("liangyi-shengong"))
			me->improve_skill("liangyi-shengong", lv * 2);
		}

        me->start_call_out((:call_other, __FILE__, "remove_effect", me, skill / 3:), skill);
        if (me->is_fighting()) me->start_busy(3);
        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("kl/taxue"))
        {
                me->add_temp("apply/dodge", -amount);               
                me->delete_temp("kl/taxue");
                tell_object(me, "你的踏雪无痕运行完毕，将内力收回丹田。\n");
        }
}