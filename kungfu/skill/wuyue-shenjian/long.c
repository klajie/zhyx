//updated by kasumi 
#include <ansi.h>
#include <combat.h>

#define LONG "「" HIC "天外玉龙" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg,str;
        int ap, dp,i;
        int damage,count;
        int neili, hit_point, time;


        if (! target) target = offensive_target(me);
		

        if (! target || ! me->is_fighting(target))
                return notify_fail(LONG "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，难以施展" LONG "。\n");

        if (me->query_skill("hanbing-zhenqi", 1) < 500)
                return notify_fail("你的寒冰真气修为不够，难以施展" LONG "。\n");

        if (me->query_skill("wuyue-shenjian", 1) < 800)
                return notify_fail("你的五岳神剑修为不够，难以施展" LONG "。\n");

        if (! me->query("reborn"))         
                return notify_fail("你尚未转世重生，无法领会此绝招！\n"); 
				
	if ((int)me->query("max_neili") < 6000)
                return notify_fail("你的内力修为不足，难以施展" LONG "。\n");

        if (me->query("neili") < 1200)
                return notify_fail("你的真气不够，难以施展" LONG "。\n");

        if (me->query_skill_mapped("sword") != "wuyue-shenjian")
                return notify_fail("你没有激发五岳神剑，难以施展" LONG "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");



		ap = me->query_skill("sword") + me->query_skill("force");
		dp = target->query_skill("dodge",1) + target->query_skill("force");

           
		 msg = HIW "\n但见$N" HIW "手中" + weapon->name() + HIW 
                      "自半空中横过，剑身似曲似直，便如一件活物一般，正"
                      "是五岳神剑的精髓「" HIY "天外玉龙" HIW "」，一"
                      "柄长剑被$N" HIW "使得如灵蛇，如神龙，猛然剑刺向$n" 
                      HIW "。\n" NOR;
        
        message_sort(msg, me, target);

        if (ap * 2/ 3 + random(ap) > dp)
        {
		    damage = ap * 3 + random(ap*2);
            target->receive_damage("qi", damage,me);
            target->receive_wound("qi", damage*4/5, me);
			me->add("neili", -300);        
	        str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	       	msg = "($n"+str+")\n";       
               
        } else
        {
                me->add("neili", -100);               
                msg = CYN "可却见" CYN "$n" CYN "猛的拔地而起，避开了"
                      CYN "$N" CYN "来势凶猛的一招。\n" NOR;
        }
        message_vision(msg, me, target);    
	  	   
	   if (me->query_skill("hanbing-zhenqi", 1) > 500 && me->query_skill_mapped("force") == "hanbing-zhenqi"){
	   
			msg = HIW "只见$N"HIW"将“寒冰真气”运至极致，数道寒气化为剑气，如银龙般扑向$n" HIW "！\n" NOR;
			message_combatd(msg, me, target);
			for (i = 0; i < 6; i++){
					damage = ap*2/3 + random(ap)/2;  
					msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80+random(30),
                                           HIR "$n" HIR "只觉眼前一黑，几道银光闪过，身上已多数个血流不止的血窟窿！\n" NOR);
					me->add("neili", -150);
					message_combatd(msg, me, target);
			}
		}else{
			msg = HIW "只见$N"HIW"气势不减，手中" + weapon->name() + HIW "蜿蜒盘桓，如神龙般扑向$n" HIW "！\n" NOR;
			message_combatd(msg, me, target);
			count = me->query_skill("sword",1)*2/3;
           me->add_temp("apply/attack", count);
           me->add_temp("apply/damage", count/2);
		   for (i = 0; i < 12; i++)
      	   {
               	if (! me->is_fighting(target))
               	        break;
				 if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1); 
                COMBAT_D->do_attack(me, target, weapon, 0);
			    me->add("neili", -50);
           }
		   me->add_temp("apply/attack", -count);
           me->add_temp("apply/damage", -count/2);
		}
		

	   
	    me->start_busy(2+random(4));

        return 1;
}