#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

#define MIESHI "「" HIR "灭世" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, clv, str;
        int damage;
 
        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/canhe-zhi/mieshi"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(MIESHI "只能在战斗中对对手使用。\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("你必须空手才能使用" MIESHI "。\n");

        clv = me->query_skill("canhe-zhi", 1);

        if (clv < 800)
                return notify_fail("你的参合指修为有限，难以施展" MIESHI "。\n");

        if (me->query_skill_prepared("finger") != "canhe-zhi")
                return notify_fail("你现在没有准备使用参合指，难以施展" MIESHI "。\n");

        if (me->query_skill("zihui-xinfa", 1) < 500)
                return notify_fail("你的紫徽心法修为不够，难以施展" MIESHI "。\n");

        if ((int)me->query("max_neili") < 16000)
                return notify_fail("你的内力修为不足，难以施展" MIESHI "。\n");

        if (me->query("con") < 51)
                return notify_fail("你的先天根骨太低，难以施展" MIESHI "。\n"); 

        if (me->query("str") < 47)
                return notify_fail("你的先天臂力太低，难以施展" MIESHI "。\n"); 

        if (me->query("neili") < 2000)
                return notify_fail("你的内力不够，难以施展" MIESHI "。\n");
                
        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

                    message_vision(HIR"$N啸声连连，气势冲天，剑气所指之处，施展出参合指最终绝技 【 灭 世 】！！\n"NOR, me);

        ap = clv + me->query_skill("parry") + me->query_skill("zihui-xinfa", 1) + me->query_skill("martial-cognize", 1);
        dp = target->query_skill("dodge") + target->query_skill("parry") + target->query_skill("martial-cognize", 1);

                damage = ap * 3 / 2 + random(ap*3/2);

                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           MAG "剑气像亿万银鱼跳跃追逐，又似无数游龙排成一线，乘风破浪而来！！\n"NOR);
        message_combatd(msg, me, target);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           MAG "前波未平，第二层剑气又至，似满江碎银狂泻，如托起耸江潮峰，澎湃而来！！\n" NOR);
        message_combatd(msg, me, target);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           MAG "三重剑气相激，势如满江涌潮，声如山崩地裂，掀起万钧的巨浪，摧枯拉朽！！\n" NOR);
        message_combatd(msg, me, target);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           MAG "剑气接踵而至，潮尖如受惊猛狮突兀立起，陡起丈高水柱，剑气纷飞，破水而出！！\n" NOR);
        message_combatd(msg, me, target);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           MAG "剑气滚滚而来，像银山滚动，雪屋耸摇，顷刻，剑气呼啸而过，如大浪淘尽，波涛泛白，经久不息！！\n" NOR);
        message_combatd(msg, me, target);

        if (ap + random(ap) > dp)
        {
                target->set("neili",0); 
                me->start_busy(3+random(3)); 
                if (random(3) > 1)
                {
                me->add("neili", -1000); 
                target->receive_damage("qi", damage*2, me); 
                target->receive_wound("qi", damage, me);
                str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
                msg = HIR "$N最后一式“毁天灭世”汹涌而至，穿透$n" HIR "的躯体，只留下剑气的破空之声， 
$n"HIR"的眼中突然流露出莫名的恐惧，所有的景象已变得支离破碎， 
"HBMAG"$n绝望之际，丹田被数股剑气贯穿而过，顿时血流如注，全身真气尽失！\n" NOR;
                msg += "($n"+str+")\n";
                } else
                {
                damage = ap * 2 + random(ap*2);
                me->add("neili", -500); 
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                           HIR "$N最后一式“毁天灭世”汹涌而至，穿透$n"HIR"的躯体，只留下剑气的破空之声，
$n"HIR"的眼中突然流露出莫名的恐惧，所有的景象已变得支离破碎，
$n"HIR"绝望之际，丹田被数股剑气贯穿而过，顿时血流如注，全身真气尽失！\n" NOR); 
                 }
        } else
        {
                me->add("neili", -800);
                me->start_busy(3+random(4));
                msg = CYN "$n" CYN "见$P" CYN "来势汹涌，不敢轻易抵"
                       "挡，连忙飞身腾挪，躲闪开来。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}


