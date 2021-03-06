#include <ansi.h>
#include <combat.h>

#define QIAN "「" HIW "千剑纵横势" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
        int count;
	int i, attack_time;

        if (userp(me) && ! me->query("can_perform/wushen-jian/qian"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
                return notify_fail(QIAN "只能对战斗中的对手使用。\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，难以施展" QIAN "。\n");

	if ((int)me->query_skill("wushen-jian", 1) < 220)
		return notify_fail("你的衡山五神剑不够娴熟，难以施展" QIAN "。\n");

	if (me->query("neili") < 300)
		return notify_fail("你的真气不够，难以施展" QIAN "。\n");

        if (me->query_skill_mapped("sword") != "wushen-jian")
                return notify_fail("你没有激发衡山五神剑，难以施展" QIAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

	msg = HIW "\n$N" HIW "运转衡山五神剑，手中" + weapon->name() +
              HIW "迸出无数剑光，宛若飞虹擎天，席卷$n" HIW "而去。" NOR;

        message_sort(msg, me, target);

	ap = me->query_skill("sword");
	dp = target->query_skill("dodge");
  attack_time = 1+(int)(me->query_skill("wushen-jian", 1)/40);

	if (ap * 3/ 5 + random(ap * 2) > dp)
	{
		msg = HIR "结果$n" HIR "被$N" HIR "攻了个措手不及，$n"
                      HIR "慌忙招架，心中叫苦。\n" NOR;
                count = ap / 4;                
        } else
        {
                msg = HIC "$n" HIC "见$N" HIC "这几剑招式凌厉，凶猛异"
                      "常，只得苦苦招架。\n" NOR;
                count = 0;
        }
    	message_combatd(msg, me, target);
       

        me->add_temp("apply/attack", count);
        me->add_temp("apply/damage", count / 2);
        
        me->add("neili", -attack_time * 10);
	me->start_busy(1 + random(attack_time / 2));
        
	for (i = 0; i < attack_time; i++)
	{
		if (! me->is_fighting(target))
		       break;

                if (! target->is_busy() && random(3) == 1)
                       target->start_busy(1);
 
	        COMBAT_D->do_attack(me, target, weapon, 0);
	}        

        me->add_temp("apply/attack", - count);
        me->add_temp("apply/damage", - count / 2);
	return 1;
}
