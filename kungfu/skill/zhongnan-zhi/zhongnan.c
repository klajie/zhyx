// zhongnan.c 终南一指

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("终南一指只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("zhongnan-zhi", 1) < 35)
                return notify_fail("你的终南指法不够娴熟，不会使用终南一指。\n");

        if ((int)me->query_skill("force") < 50)
                return notify_fail("你的内功修为不够，难以施展终南一指。\n");

        if ((int)me->query("neili") < 60)
                return notify_fail("你现在真气不够，无法使用终南一指。\n");

	if (me->query_temp("weapon"))
		return notify_fail("你必须要空手才能发出终南一指。\n");

        msg = HIY "$N" HIY "一指刺出，不住的晃动，攻向$n"
              HIY "的要穴。\n" NOR;

        if (random(me->query_skill("finger")) > target->query_skill("parry") / 2 || !living(target))
        {
                me->start_busy(2);
                damage = me->query_skill("finger");
                damage = 40 + damage / 4 + random(damage / 5);
                me->add("neili", -60);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 20,
                                           HIR "结果$p" HIR "招架失误，被$P" HIR
                                           "这一指点了个正着，内息登时一滞，气血倒流。\n" NOR);
        } else
        {
                me->start_busy(3);
                me->add("neili", -20);
                msg += CYN "可是$p" CYN "识破了$P"
                       CYN "这一招，斜斜一跃避开。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
