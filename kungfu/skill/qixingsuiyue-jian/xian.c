#include <ansi.h>
#include <combat.h>

#define ZHUAN "「" HIW "七星聚月" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, i;

        if (userp(me) && ! me->query("can_perform/qixingsuiyue-jian/xian"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHUAN "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你所使用的武器不对，难以施展" ZHUAN "。\n");

        if ((int)me->query_skill("qixingsuiyue-jian", 1) < 80)
                return notify_fail("你的七星随月剑法不够娴熟，难以施展" ZHUAN "。\n");

        if (me->query_skill_mapped("sword") != "qixingsuiyue-jian")
                return notify_fail("你没有激发七星随月剑法，难以施展" ZHUAN "。\n");

        if ((int)me->query_skill("dodge") < 120)
                return notify_fail("你的轻功修为不够，无法施展" ZHUAN "！\n");

        if (me->query("neili") < 200)
                return notify_fail("你目前的真气不够，难以施展" ZHUAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIM "$N" HIM "使出黑龙使张淡月绝技「" HIW "七星聚月" HIM "」，"
              "手中" + weapon->name() + HIM "从北斗七星方位，朝$n击来！\n" NOR;

        me->add("neili", -270);

        message_vision(msg, me, target);

        for (i = 0; i < 7; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (! target->is_busy() && random(2) == 1)
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(3 + random(5));

        return 1;
}

