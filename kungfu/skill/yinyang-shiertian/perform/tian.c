#include <ansi.h>
#include <combat.h>

#define TIAN "「" HIW "九转乾坤"HIY"十二天" NOR "」"

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
       
        if ((int)me->query_skill("yinyang-shiertian", 1) < 500)
                return notify_fail("你的阴阳九转十二重天火候不够，难以施展" TIAN "。\n");

	weapon = me->query_temp("weapon");

        if (! objectp(weapon))
        {     if (me->query_skill_mapped("unarmed") != "yinyang-shiertian"
                        || me->query_skill_prepared("unarmed") != "yinyang-shiertian")
                              return notify_fail("你没有准备阴阳九转十二重天，无法使用" TIAN "。\n");
        }
        else if (objectp(weapon) && (string)weapon->query("skill_type") != "sword"
                      && (string)weapon->query("skill_type") != "blade")
                              return notify_fail("你使用的武器不对，无法施展" TIAN "。\n");

             if (objectp(weapon) && me->query_skill_mapped("sword") != "yinyang-shiertian"
                 && (string)weapon->query("skill_type") == "sword")
                              return notify_fail("你还没有激发阴阳九转十二重天，无法施展" TIAN "。\n");
             
             else if (objectp(weapon) && (string)weapon->query("skill_type") == "blade"
                      && me->query_skill_mapped("blade") != "yinyang-shiertian")
                              return notify_fail("你还没有激发阴阳九转十二重天，无法施展" TIAN "。\n");    

        if ((int)me->query("max_neili") < 20000)
                return notify_fail("你的内力修为不足，难以施展" TIAN "。\n");

        if ((int)me->query("neili") < 2500)
                return notify_fail("你现在的真气不够，难以施展" TIAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");        
        
        message_sort(HIM "\n$N" HIM "运起阴阳九转十二重天，仿佛九天神龙翱翔天际，"
                     HIM "正是无上绝学\n" HIW "               「"HIC" 九 转 乾 坤"HIY" 十 二"HIR" 天" HIW " 」" HIM " ！\n\n" NOR, me, target);
                     
        ap = me->query_skill("yinyang-shiertian", 1) + me->query_skill("force", 1) + me->query_skill("martial-cognize", 1);
        dp = target->query_skill("dodge", 1) + target->query_skill("parry", 1) + target->query_skill("martial-cognize", 1); 
        attack_time = 1+(int)(me->query_skill("yinyang-shiertian", 1)/55);
        if (attack_time > 12) attack_time =12;
       
        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                message_sort(HIW "$N" HIW "身若游龙，挟风雷之力，从空中向$n" 
                             HIW "猛扑下来！\n" NOR, me, target);
		
                if (ap * 3 / 2 + random(ap) > dp)
                {
			damage = ap + random(ap);
			if (me->query_skill("yinyang-shiertian",1)>999 && random(5)>2)
			{
				target->receive_damage("qi", damage, me);
				target->receive_wound("qi", damage * 2 / 3, me);
				target->receive_damage("jing", damage, me);
				target->receive_wound("jing", damage * 2 / 3, me);
				msg = HIY "$n" HIY "奋力招架，不料" HIY "$N" HIY "的内劲绵绵不绝，" HIY "$n" HIY "顿遭重创！\n" NOR;
			}else
			{
				if (me->query_temp("weapon"))
				{
        	                        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, (i + 1) * 20,
                	                                          HIR "$n" HIR "躲闪不及被$N" HIR
                        	                                  "的内劲已破体而入，喉头一甜，喷出一大"
                                	                          "口鲜血。\n" NOR);
	                        } else
        	                {
                	                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, (i + 1) * 20,
                        	                                  HIR "$n" HIR "躲闪不及被$N" HIR
                                	                          "的内劲已破体而入，喉头一甜，喷出一大"
	                                       	                  "口鲜血。\n" NOR);
        	                }
			}
                } else
                {
                       	msg = CYN "$n" CYN "气凝双臂，奋力招架，将"
                              "$N" CYN "的内劲卸掉。\n" NOR;
                }
		me->add("neili", -200);
                message_sort(msg, me, target);

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);
        }
        me->start_busy(3+random(4));
        return 1;        
}

