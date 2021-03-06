#include <ansi.h>

inherit F_SSERVER;

#define LEI "「" HIY "电闪雷鸣" NOR "」"

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i;
        object weapon;
 
        
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(LEI "只能在战斗中对对手使用。\n");
 
        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "hammer")
                return notify_fail("你所使用的武器不对，难以施展" LEI "。\n");
                
        if ((int)me->query("neili") < 800)
                return notify_fail("你的真气不够！\n");

        if ((int)me->query_skill("leiting-fu", 1) < 220)
                return notify_fail("你的雷霆斧火候不够，无法施展" LEI "。\n");

        if ((int)me->query_skill("force") < 340)
                return notify_fail("你的内功修为不够，无法施展" LEI "。\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
              
       weapon = me->query_temp("weapon");

        msg = HIC "\n$N" HIC "一声爆喝，手中"+weapon->name()+HIC"舞成一团青光，携天崩地裂之势压向$n。\n" NOR;
              

        ap = me->query_skill("hammer") + me->query_skill("force");
        dp = target->query_skill("parry") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 6;
                msg += HIY "$n" HIY "见$P" HIY "这一招变化莫测，奇幻无"
                       "方，不由大吃一惊，慌乱中破绽迭出。\n" NOR;
        } else
        {
                msg += HIC "$n" HIC "不敢小觑$P" HIC
                       "的来招，腾挪躲闪，小心招架。\n" NOR;
                count = ap / 12;
        }

        message_sort(msg, me, target);
        me->add_temp("apply/attack", count);

        me->add("neili", -400);
        for (i = 0; i < 7; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(2) && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(2 + random(5));
        me->add_temp("apply/attack", -count);

        return 1;
}

