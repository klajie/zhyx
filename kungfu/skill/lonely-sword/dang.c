// 荡剑式 by kasumi

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
		return notify_fail("荡剑式只能对战斗中的对手使用。\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("无剑如何运用荡剑式？\n");

	if ((int)me->query("neili") < 1000)
		return notify_fail("你现在的真气不够，无法使用荡剑式！\n");

	if ((int)me->query_skill("lonely-sword", 1) < 700)
		return notify_fail("你的独孤九剑还不到家，无法使用荡剑式！\n");

	if (me->query_skill_mapped("sword") != "lonely-sword") 
		return notify_fail("你没有激发独孤九剑，无法使用荡剑式！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "提气往前一纵，长剑往地上轻轻一点，贴地掠向$n" HIC "，正是独孤九剑"HIM"“荡剑式”"HIC"。\n" NOR;

        damage = me->query_skill("lonely-sword",1) * 11;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 85,
		                           HIR "$n" HIR "看不出$N"HIR"招数来路，惊愕之中已受重创！\n" NOR);		
		
		if (! target->query_temp("lonely_dang"))
        {           
                target->add_temp("apply/force", -500);
                target->add_temp("apply/parry", -500);
                target->add_temp("apply/dodge", -500);
                target->set_temp("lonely_dang", 1);
        		msg += HIM "$n只觉得恍如灵魂出窍，全身的力气竟似一丝丝远离自己而去，无助之极。\n" NOR;
		}
		message_combatd(msg, me, target);
		call_out("dang_end", 5 + random(8), me, target);
		me->start_busy(2);
		me->add("neili", -300);
	

	return 1;
}

void dang_end(object me, object target)
{
        if (target && target->query_temp("lonely_dang"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "深深吸入一口气，脸色由"
                                        "白转红，看起来好多了。\n" NOR, target);                       
                }                
                target->add_temp("apply/force", 500);
                target->add_temp("apply/parry", 500);
                target->add_temp("apply/dodge", 500);
                target->delete_temp("lonely_dang");
        }
        return;
}