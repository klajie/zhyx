//updated by kasumi
#include <ansi.h>
#include <combat.h>

#define ZHEN "「" HIW "反璞归真" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage,count;
        string msg;
        int i, ap, dp;
        object weapon;

        if (userp(me) && ! me->query("can_perform/guzhuo-zhang/zhen"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHEN "只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
                return notify_fail(ZHEN "只能空手使用。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你内功修为不够，难以施展" ZHEN "。\n");

        if ((int)me->query("max_neili") < 3600)
                return notify_fail("你内力修为不够，难以施展" ZHEN "。\n");

        if ((int)me->query_skill("guzhuo-zhang", 1) < 220)
                return notify_fail("你古拙掌法火候不够，难以施展" ZHEN "。\n");

        if (me->query_skill_mapped("strike") != "guzhuo-zhang")
                return notify_fail("你没有激发古拙掌法，难以施展" ZHEN "。\n");

        if (me->query_skill_prepared("strike") != "guzhuo-zhang")
                return notify_fail("你没有准备古拙掌法，难以施展" ZHEN "。\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("你现在真气不够，难以施展" ZHEN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "陡然间$N" HIW "施出「" HIY "璞" HIW "」字诀，双掌向$n"
              HIW "平平推去，招数朴实无华，毫无半点花巧可言。\n" NOR;  

        ap = me->query_skill("strike") + me->query_skill("force") + me->query("str") * 10;
        dp = target->query_skill("force") + target->query_skill("dodge") + target->query("dex") * 10;

        if (ap * 2/3 + random(ap) > dp)
        { 
                damage = ap/2 + random(ap/2);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70+random(15),
                                           HIR "$n" HIR "勘破不透掌中虚实，$N" HIR
                                           "双掌正中$p" HIR "前胸，“喀嚓喀嚓”接"
                                           "连断了数根肋骨。\n" NOR);
                msg += HIG"$n"HIG"的真元瞬即被$N"HIG"吸入体内！\n" NOR;
                me->add("qi", damage/2);
                if (me->query("qi") > me->query("eff_qi"))
                	me->set("qi", me->query("eff_qi") );                	
        } else
        {
                msg += CYN "$n" CYN "见$N" CYN "这掌来势非凡，不敢"
                       "轻易招架，当即飞身纵跃闪开。\n" NOR;
        }

        msg += HIW "\n紧接着$N" HIW "变招「" HIY "真" HIW "」字诀，霎"
               "时只见$N" HIW "双掌纷飞，化出漫天掌影笼罩$n" HIW "四面"
               "八方。\n"NOR;
        message_combatd(msg, me, target);
        
        count=(int) (me->query_skill("strike")/5);
        me->add_temp("apply/attack", count); 
        me->add_temp("apply/unarmed_damage", count/2);

        for (i = 0; i < 7; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);

        	COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->add_temp("apply/unarmed_damage", -count/2);
        me->add_temp("apply/attack", -count);
        me->add("neili", -400);
        me->start_busy(3 + random(4));
        return 1;
}

