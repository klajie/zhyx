// wanli.c 晴空万里
// updated by kasumi 2007.4.5
// 连续单招pfm，威力逐级翻倍。


#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object  weapon;
	      int     damage;
	      string  msg;
        string  pmsg;
        string *limbs;
        string  limb;
        int ap, dp,n,i;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("晴空万里只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("never-defeated", 1) < 320)
		return notify_fail("你的不败神功还不够娴熟，不能使用晴空万里。\n");
        /*
        if (((int)me->query_skill("count", 1) > 1) && (me->query("reborn")))
		return notify_fail("你觉得心烦意乱，无从使用晴空万里。\n");
        */	                        
        if ((int)me->query("neili", 1) < 1000)
		return notify_fail("你现在内力太弱，不能使用晴空万里。\n");
			
        if (! objectp(weapon = me->query_temp("weapon")))
                return notify_fail("你必须手持兵刃才能施展晴空万里！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        ap = me->query_skill("never-defeated", 1) * 3 / 2 + me->query_skill("martial-cognize", 1) + me->query_skill("dodge", 1) * 3 / 4;
        dp = target->query_skill("parry") + target->query_skill("martial-cognize", 1);
        
        damage = (int) me->query_skill("never-defeated", 1);
        
        n=1+4;      
        
        for (i = 1; i < n+1; i++)        
        {
        	 if (! me->is_fighting(target))
                        break; 
           message_sort(HIC "$N" HIC "怀抱" + weapon->name() + HIC "，一"
                            "圈圈的划向$n" HIC "，将$p" HIC "卷在当中！\n" NOR, me, target);   
        	 damage=damage*i;        	 
           if (ap * 3 / 5 + random(ap * 2) > dp)
            {	
               if (arrayp(limbs = target->query("limbs")))
                        limb = limbs[random(sizeof(limbs))];
                else
                        limb = "要害";
                pmsg = HIR "$n"HIR"连忙腾挪躲闪，然而“扑哧”一声，" + weapon->name() +
		                   HIR "正好击中$p" HIR "的" + limb + "，$p"
		                   HIR "一声惨叫，连退数步。\n" NOR;
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50, pmsg);
                message_sort(msg, me, target);
                
	          } else 
	          {		
	          	message_sort(CYN "可是$p" CYN "看破了$P"
                       CYN "的变化，见招拆招，没有受到任何伤害。\n"NOR, me, target);         
	          }
	          
        }
        me->add("neili", -100*n);
        me->start_busy(2+random(5));

	return 1;
}
