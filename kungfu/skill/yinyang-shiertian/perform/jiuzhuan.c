#include <ansi.h>
#include <combat.h>

#define TIAN "「" HIW "九转乾坤" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage,count,i,attack_time;
        string msg, wn, wp,wp2,str;
        object weapon,weapon2;
        int ap, dp;
        me = this_player();

        
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(TIAN "只能在战斗中对对手使用。\n");
       
        if ((int)me->query_skill("yinyang-shiertian", 1) < 400)
                return notify_fail("你的阴阳九转十二重天火候不够，难以施展" TIAN "。\n");

	weapon = me->query_temp("weapon");

        if (! objectp(weapon))
        {
		if (me->query_skill_mapped("unarmed") != "yinyang-shiertian"
			|| me->query_skill_prepared("unarmed") != "yinyang-shiertian")
				return notify_fail("你没有准备阴阳九转十二重天，无法使用" TIAN "。\n");
        }
        else
	{
		if (objectp(weapon) && (string)weapon->query("skill_type") != "sword"
				&& (string)weapon->query("skill_type") != "blade")
                              return notify_fail("你使用的武器不对，无法施展" TIAN "。\n");
	}

        if (objectp(weapon) && me->query_skill_mapped("sword") != "yinyang-shiertian"
                 && (string)weapon->query("skill_type") == "sword")
                              return notify_fail("你还没有激发阴阳九转十二重天，无法施展" TIAN "。\n");
             
	else if (objectp(weapon) && (string)weapon->query("skill_type") == "blade"
                      && me->query_skill_mapped("blade") != "yinyang-shiertian")
                              return notify_fail("你还没有激发阴阳九转十二重天，无法施展" TIAN "。\n");    

        if ((int)me->query("max_neili") < 8500)
                return notify_fail("你的内力修为不足，难以施展" TIAN "。\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("你现在的真气不够，难以施展" TIAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");        
       
        message_sort(HIM "\n$N" HIM "口中默念：天道无常。心神沉入十二重天境界，"
                     "连空间似乎也扭曲了起来。$n" HIM "大惊失色，仿佛已身在异界！\n" NOR, me, target);

         message_sort(HIW "$N" HIW "双臂一震，一股浑厚至极的内劲汹涌澎湃，" 
                     "带着排山倒海之势向$n" HIW "席卷而至。\n" NOR, me, target);
        ap = me->query_skill("yinyang-shiertian", 1);

        dp = target->query_skill("dodge", 1);
        
	if (ap + random(ap) > dp)
                count = ap / 3;
	else
                count = ap / 10;

        me->add_temp("apply/attack", count);
	me->add_temp("apply/damage", count / 2);
	me->add_temp("apply/unarmed_damage", count / 2);
        me->add("neili", -250);

        attack_time = 1+(int)(me->query_skill("yinyang-shiertian", 1)/50);
        if (attack_time > 9) attack_time =9;

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);
                if (! objectp(weapon))
                   COMBAT_D->do_attack(me, target, 0, i * 2);
                else COMBAT_D->do_attack(me, target, weapon, i * 2);
        }
        me->add_temp("apply/attack", -count);
	me->add_temp("apply/damage", -count / 2);
	me->add_temp("apply/unarmed_damage", -count / 2);
        me->start_busy(2+random(4));
        me->add("neili", -1000);
       return 1;
}
        

        

