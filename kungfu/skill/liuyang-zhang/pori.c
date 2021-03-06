//created by kasumi.

#include <ansi.h>
#include <combat.h>

#define PO "「" HIW "九弧破" HIR "日" HIW "决" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;
        int ap, dp;

        //if (userp(me) && ! me->query("can_perform/liuyang-zhang/pori"))
             //   return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }
	if (! target || ! me->is_fighting(target))
                return notify_fail(PO "只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(PO "只能空手施展。\n");

        if ((int)me->query_skill("bahuang-gong", 1) < 400)
                return notify_fail("你八荒六合唯我独尊功火候不够，难以施展" PO "。\n");

        if ((int)me->query_skill("liuyang-zhang", 1) < 400)
                return notify_fail("你的天山六阳掌不够娴熟，难以施展" PO "。\n");

        if (me->query("max_neili") < 4500)
                return notify_fail("你的内力修为不足，难以施展" PO "。\n");

        if (me->query_skill_mapped("strike") != "liuyang-zhang")
                return notify_fail("你没有激发天山六阳掌，难以施展" PO "。\n");

        if (me->query_skill_prepared("strike") != "liuyang-zhang")
                return notify_fail("你没有准备天山六阳掌，难以施展" PO "。\n");

        if (me->query("neili") < 800)
                return notify_fail("你现在真气不足，难以施展" PO "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

	msg = HIW "$N" HIW "逆运真气，化空气中的水露为寒冰凝于掌中，继而手腕一抖,无数冰粒如雨点般激射向$n！\n"NOR;

	      
        ap = me->query_skill("force") + me->query_skill("strike") + me->query_skill("dodge") + me->query_skill("parry");
        dp = target->query_skill("force")*2 + target->query_skill("parry") + target->query_skill("dodge");
        if (ap * 3 / 5 + random(ap) > dp)   
        	{
        		damage=ap+random(ap/2);
        		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
        	                                   HIR "$n" HIR "慌忙抵挡，可已然不及，$N"
                                             HIR "碎粒尽数钉在了$n身上，一屡屡鲜血从伤口处涌出！\n" NOR);
            me->add("neili", -250);
          }
        else
        	{
        		msg += CYN "$n" CYN"眼见碎片已射至眼前，只得铤而走险，运劲鼓起袍袖将碎片拨了开！\n"NOR;
        		me->add("neili", -100);        		
        	}
        msg += HIG "\n紧接着" HIG "$N" HIG "将八荒六合唯我独尊功提运至极限，全身真气迸发，呼的一掌"
              "向$n" HIG "头顶猛然贯落。\n" NOR;
        		     

        if (ap * 2 /3  + random(ap) > dp)
	      {
                damage = 0;
                if (me->query("max_neili") > target->query("max_neili") * 2)
                {
                        msg += HIR "顿时只听“噗”的一声，$N" HIR "一掌将$n"
                               HIR "头骨拍得粉碎，脑浆四溅，当即瘫了下去。\n"
                               NOR "( $n" RED "受伤过重，已经有如风中残烛，"
                               "随时都可能断气。" NOR ")\n";
                        damage = -1;
                } else
		            {
			            damage = (int)me->query_skill("bahuang-gong", 1) * 8;
                    	damage += random(damage / 2);

	                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80+random(20),
        	                                   HIR "$n" HIR "慌忙抵挡，可已然不及，$N"
                                                   HIR "掌劲如洪水般涌入体内，接连震断数根"
                                                   "肋骨。\n" NOR);
		             }
		             me->add("neili", -200);
		             me->start_busy(3+random(3));
	       } else
	       {
		        msg += CYN "$p" CYN "见$P" CYN "掌劲澎湃，决计抵挡不"
                                           "住，当即身子向后横丈许，躲闪开来。\n" NOR;
		        me->start_busy(3+random(3));
		        me->add("neili", -100);
	       }
	message_combatd(msg, me, target);

        if (damage < 0)
                target->die(me);

	return 1;
}
