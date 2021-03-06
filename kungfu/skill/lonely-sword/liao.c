// 撩剑式 by kasumi

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
	    object weapon;
        string msg, wp;
        int ap, dp;
        int damage;
		object weapon2;
 
        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("撩剑式只能对战斗中的对手使用。\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("无剑如何运用撩剑式？\n");

	if ((int)me->query("neili") < 1000)
		return notify_fail("你现在的真气不够，无法使用撩剑式！\n");

	if ((int)me->query_skill("lonely-sword", 1) < 600)
		return notify_fail("你的独孤九剑还不到家，无法使用撩剑式！\n");

	if (me->query_skill_mapped("sword") != "lonely-sword") 
		return notify_fail("你没有激发独孤九剑，无法使用撩剑式！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "手中长剑轻轻一挑，使出独孤九剑"HIM"“撩剑式”"HIC",剑锋闪耀，刺向$n"HIC"。\n" NOR;

        damage = me->query_skill("lonely-sword",1) * 8;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
		                           HIR "$n" HIR "一愣不知如何闪避，片刻之间已然中招，鲜血长流，精神不振，面若死灰！\n" NOR);
		
		message_combatd(msg, me, target);
		target->set("jingli",0);
		target->set_temp("no_perform", 1);
        call_out("liao_end", 3 + random(5), me, target);
		me->start_busy(2);
		me->add("neili", -300);
	

	return 1;
}

void liao_end(object me, object target)
{
        if (target && target->query_temp("no_perform"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "深深吸入一口"
                                        "气，脸色由白转红，看起来好"
                                        "多了。\n" NOR, target);

                        tell_object(target, HIY "你感到被扰乱的真气"
                                            "慢慢平静了下来。\n" NOR);
                }
                target->delete_temp("no_perform");
	}
	return;
}
