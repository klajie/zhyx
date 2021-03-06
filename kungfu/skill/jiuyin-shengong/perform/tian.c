// shang.c 伤字诀

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「天昏地暗」只能在战斗中对对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "whip")
                return notify_fail("你使用的武器不对。\n");

        if (me->query_skill("force") < 300)
                return notify_fail("你的内功的修为不够，不能使用这一绝技！\n");

        if (me->query_skill("jiuyin-shengong", 1) < 300)
                return notify_fail("你的九阴神功修为不够，目前不能使用天昏地暗！\n");

        if (me->query("neili") < 400)
                return notify_fail("你的真气不够，无法使用天昏地暗！\n");

        if (me->query_skill_mapped("whip") != "jiuyin-shengong")
                return notify_fail("你没有激发九阴神功，不能使用天昏地暗！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "嘿然冷笑，手中的" + weapon->name() +
              HIY "一卷，顿时卷起漫天迷雾，一股阴气象张大网罩向$n" + HIY "！\n" NOR;

                ap = me->query_skill("whip", 1) * 3 + me->query("dex") * 20 + 
                     me->query_skill("martial-cognize", 1); 
                dp = target->query_skill("parry") + target->query("dex") * 20 + 
                     target->query_skill("martial-cognize", 1); 

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap + random(ap / 1)*2;
                me->add("neili", -300);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 120,
                                           HIR "只见$p" HIR "一声惨叫，" + weapon->name() +
                                           HIR "竟然插在$p" + HIR "的身上，创口已经"
                                           "对穿，鲜血飞溅数尺，惨不堪言！\n" NOR);
        } else
        {
                me->add("neili", -100);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "运足内力，奋力挡住了"
                       CYN "$P" CYN "这神鬼莫测的一击！\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

