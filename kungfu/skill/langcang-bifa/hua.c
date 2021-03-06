#include <ansi.h>
#include <combat.h>

#define DIAN "「" HIM "江山如画" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int i, attack_time;

        if (userp(me) && ! me->query("can_perform/langcang-bifa/hua"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(DIAN "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "dagger")
                return notify_fail("你所使用的武器不对，难以施展" DIAN "。\n");

        if ((int)me->query_skill("langcang-bifa", 1) < 100)
                return notify_fail("你的浪沧笔法不够娴熟，难以施展" DIAN "。\n");

        if (me->query_skill_mapped("dagger") != "langcang-bifa")
                return notify_fail("你没有激发浪沧笔法，难以施展" DIAN "。\n");

        if (me->query("neili") < 300)
                return notify_fail("你目前的真气不够，难以施展" DIAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
        
        msg = HIY "$N" HIY "左手微摆，右手执笔，目光凝视$n，手中" + weapon->name() + HIW "一扬，\n"
                  "看似苍海涌动,亦似虚谷纳川,忽静忽动,忽左忽右,忽远忽近,动作变幻无穷令人如梦似幻!\n"NOR
              
              HIC "※※※※※※※※※※※※※※※※※※※※※※※※※※※\n" 
              HIC "※" HIW "  江        山      如      此      多      骄!" HIC "   ※\n" 
              HIC "※" HIW "  无        数      英      雄      折      腰!" HIC "   ※\n"      
              HIC "※※※※※※※※※※※※※※※※※※※※※※※※※※※\n"NOR;   
               
        attack_time = 4;

        ap = me->query_skill("dagger");

        attack_time += random(ap / 40);

        if (attack_time > 8)
                attack_time = 8;

        me->add("neili", -attack_time * 30);
        message_sort(msg, me, target);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (! target->is_busy() && random(2) == 1)
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(attack_time));

        return 1;
}

