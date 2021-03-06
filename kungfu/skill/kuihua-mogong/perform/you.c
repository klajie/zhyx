// you.c 幽冥一击
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
int perform(object me, object target)
{
       object weapon;
	     string msg;
	     int ap, dp;
       int damage;
       

        if (! target)
        {
        	me->clean_up_enemy();
        	target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("幽冥一击只能对战斗中的对手使用。\n");
 
	if (me->query_skill("kuihua-mogong", 1) < 120)
		return notify_fail("你的葵花魔功还不够娴熟，不能使用幽冥一击！\n");

       if (me->query_skill_mapped("force") != "kuihua-mogong")
                return notify_fail("你还没有激发葵花魔功为内功，无法施展幽冥一击。\n");  

        if (weapon = me->query_temp("weapon"))
        {
                if (weapon->query("skill_type") != "sword" &&
                    weapon->query("skill_type") != "pin")
                        return notify_fail("你手里拿的不是剑，怎么施"
                                           "展幽冥一击？\n");
        } else
        {
                if (me->query_skill_prepared("unarmed") != "kuihua-mogong")
                        return notify_fail("你并没有准备使用葵"
                                           "花魔功，如何施展幽冥一击？\n");
        }

        if (weapon && me->query_skill_mapped("sword") != "kuihua-mogong")
                return notify_fail("你没有准备使用葵花魔功，难以施展幽冥一击。\n");

        if (! weapon && me->query_skill_prepared("unarmed") != "kuihua-mogong")
                return notify_fail("你没有准备使用葵花魔功，难以施展幽冥一击。\n");

        if (me->query("neili") < 200)
                return notify_fail("你的内力不够，不能使用幽冥一击！\n");
 
       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
  
       ap = me->query_skill("dodge") + me->query("dex") * 20 + me->query_skill("unarmed");
	     dp = target->query_skill("dodge") + target->query("dex") * 10 + target->query_skill("unarmed");
  
       if (me->query_temp("weapon"))
  		       msg = HIR "$N" HIR "忽的扑上前去，霎时便逼近$n" HIR"，忽的手中" + weapon->name() + HIR"猛然刺向$p的要害！\n" NOR;
  		 else   	
	           msg = HIR "$N" HIR "忽的扑上前去，霎时便逼近$n" HIR"，忽的伸手猛然拍向$p的要害！\n" NOR;
 
	       

        if (ap / 2 + random(ap) < dp)
        {
		       msg += HIG "然而$n" HIG "抵挡得法，将$N" HIG "的攻势一一化解。\n" NOR;
		       me->add("neili",-80);
		       me->start_busy(1);  
        } else        	
	      {		
           damage = ap  + random(ap / 2) + random(100);
           if (me->query_temp("weapon"))
           {
           	msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                           HIR "$n" HIR "急忙后退，阵脚已乱，结果连中$N"
                                           HIR "数招，鲜血溅了一地！\n" NOR);
           }else
           {
            msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                           HIR "$n" HIR "急忙后退，阵脚已乱，结果连中$N"
                                           HIR "数招，鲜血溅了一地！\n" NOR);	
           }
           me->add("neili",-100);
           me->start_busy(1);  
	 }

	message_combatd(msg, me, target);
	return 1;
}
