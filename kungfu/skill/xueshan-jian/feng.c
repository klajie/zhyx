// feng.c

#include <ansi.h>
#include <combat.h>

#define FENG "「" HIW "剑气封喉" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg,str;
        int ap, dp, count,i,n;
        int damage;
		string parry_str;
			

        if (userp(me) && ! me->query("can_perform/xueshan-jian/feng"))
		{			
            return notify_fail("你所使用的外功中没有这种功能。\n");
		}		
		count = me->query("can_perform/xueshan-jian/times");	
		
		if (count > 2000000) 
			count = 2000000;	

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(FENG "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，难以施展" FENG "。\n");

        if (me->query_skill("force") < 240)
                return notify_fail("你的内功的修为不够，难以施展" FENG "。\n");

        if (me->query_skill("xueshan-jian", 1) < 160)
                return notify_fail("你的雪山剑法修为不够，难以施展" FENG "。\n");

        if (me->query("neili") < 600)
                return notify_fail("你的真气不够，难以施展" FENG "。\n");

        if (me->query_skill_mapped("sword") != "xueshan-jian")
                return notify_fail("你没有激发雪山剑法，难以施展" FENG "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "只听$N" HIW "一声清啸，手中" + weapon->name() +
              HIW "龙吟不止，迸出万道光华，疾闪而过，无数劲风席卷"
              "$n" HIW "而去！\n" NOR;
              
       	parry_str=target->query_skill_mapped("parry");
		
        ap = me->query_skill("sword",1);
        if (me->query_skill("shangqing-jian",1) >= 600)
        	ap = ap * 0.3 + ap;
		else if (me->query_skill("shangqing-jian",1) >= 400)
		    ap = ap * 0.2 + ap;
	    else ap = ap;
		
		if (me->query("reborn")){
			ap = ap * 0.2 + ap;
		}
		
        dp = target->query_skill("dodge",1);

        if (ap * 3 / 5  + random(ap) > dp)
        {
                damage = ap  + random(ap) + count / 100;
                me->add("neili", -200);
			    me->add("can_perform/xueshan-jian/times", 1);
                me->start_busy(2);

				if (count > 500000)
				{
					  me->add("neili", -400);				      
                      target->receive_wound("qi", damage, me);
	        	      str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	                  msg += HIR "$n" HIR "只感寒风袭体，还未看清" HIR "$N" HIR "手中的长剑是何时出鞘的，只觉得咽喉一凉，鲜血喷溅而出。\n"	NOR;
				      msg += "($n"+str+")\n";
				}
				else
				{
                      msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage,100,
                                           HIR "$n" HIR "只感寒风袭体，全身一阵冰"
                                           "凉，已被$N" HIR "剑气所伤。顿时喉咙一"
                                           "甜，喷出一大口鲜血。\n" NOR);
				}

				      if (count<2000000)
				      msg += HIC "$N" HIC"对雪山剑「" HIW "梅花六出和剑气封喉" HIC "」有了新的领悟。\n" NOR;
        } else
        {
                me->add("neili", -50);
                me->start_busy(2);
                msg += CYN "可是$n" CYN "看破" CYN "$N" CYN
                       "的招数，飞身跃开丈许，终于将这阴寒剑"
                       "气驱于无形。\n"NOR;
        }
        
       message_combatd(msg, me, target);
       
      
       if (me->query("reborn"))
       	{       		
          message_combatd(HIW "紧接着$N" HIW "手中" + weapon->name() + 
        	       HIW "抖动，只见寒星点点，虚中有实，实中有"
                     "虚，四面八方向$n" HIW "攻去！\n" NOR, me, target);
               me->add_temp("apply/attack", 100);
               for (i = 0; i < 6; i++)
              {
                if (! me->is_fighting(target))
                        break;
				        if (random(2)==1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
				 me->add("neili", -80);		
              }
              me->add_temp("apply/attack", -100);	       			
               me->start_busy(2+random(4));
               
       	}       
       
        

        return 1;
}
