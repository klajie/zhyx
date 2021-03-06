#include <ansi.h>
#include <combat.h>

#define HUI "「" HIW "回"HIY"天"HIW"剑"HIR"舞" NOR "」"

inherit F_SSERVER;

string final1(object me, object target, int damage);
string final2(object me, object target, int damage);
string final3(object me, object target, int damage);
string final4(object me, object target, int damage);
string final5(object me, object target, int damage);



int perform(object me, object target)
{
        object weapon;
        string wn, msg;       
        int ap, dp, damage, lvl;

	if (userp(me) && ! me->query("can_perform/suxin-jian/hui"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUI "只能对战斗中的对手使用。\n");

        if (me->query("gender") == "男性")
                return notify_fail("此招不适合男性使用！\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，难以施展" HUI "。\n");

        if ((int)me->query_skill("force") < 400)
                return notify_fail("你的内功修为不够，难以施展" HUI "。\n");

        if ((int)me->query("max_neili") < 4500)
                return notify_fail("你的内力修为不够，难以施展" HUI "。\n");

        if ((int)me->query_skill("suxin-jian", 1) < 350)
                return notify_fail("你玉女素心剑法火候不够，难以施展" HUI "。\n");

	if ((int)me->query_skill("yunv-xinjing", 1) < 300)
                return notify_fail("你玉女心经火候不够，难以施展" HUI "。\n");

	/* if(me->query_temp("no_hui"))
                return notify_fail("你内息未稳，无法使用" HUI "！\n");      */

        if (me->query_skill_mapped("sword") != "suxin-jian")
                return notify_fail("你没有激发玉女素心剑法，难以施展" HUI "。\n");

	if ((string)me->query_skill_mapped("force") != "yunv-xinjing")
                return notify_fail("你必须激发玉女心经才能施展出" HUI "！\n");

        if ((int)me->query("neili") < 1200)
                return notify_fail("你现在真气不够，难以施展" HUI "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

	wn = weapon->name();
	lvl = (int)me->query_skill("suxin-jian", 1);

        message_combatd(HIW "$N" HIW "轻身一跃从"HIW"$n"HIW"的招数中抽身而出，挺剑翩然而上，风姿绰约，飘逸无比，\n"
                        HIW "已然用上了玉女心经最后一章的绝学！\n" NOR, me, target);

	

	ap = me->query_skill("sword") + me->query_per() * 15;
	if (me->query_temp("wang") && target->query("gender") == "男性")
		ap = ap * 1.5;	
	if (target->query("family/family_name") == "全真派")
       ap = ap * 1.75;	
	dp = target->query_skill("dodge") + target->query_per() * 15;   

        // 第一招           

	message_vision(HIW"\n  「回"HIY"天"HIW"剑"HIR"舞"HIW"」 之" HIG"  春梦无痕 \n" NOR, me, target); 

	if (ap * 2/3 + random(ap) > dp)
	{
	    damage = ap + random(ap/2);
		msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 
		20 + random(30),(: final1, me, target, damage, weapon, lvl :));        
	} else
	{
               msg = CYN "可是$n" CYN "收敛心神，奋力招"
                      "架，将剑招卸于无形。\n" NOR;
        }
        message_vision(msg, me, target);

	// 第二招

	message_vision(HIW"\n    「回"HIY"天"HIW"剑"HIR"舞"HIW"」 之" HIW"  飘絮随风 \n" NOR, me, target); 

	if (ap * 2/3  + random(ap) > dp)
	{
	        damage = ap + random(ap/2);
               msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 
               20 + random(40),(: final2, me, target, damage, weapon, lvl :));        

	} else
        {
               msg = CYN "可是$n" CYN "收敛心神，奋力招"
                      "架，将剑招卸于无形。\n" NOR;
        }
        message_vision(msg, me, target);

	// 第三招

	message_vision(HIW"\n      「回"HIY"天"HIW"剑"HIR"舞"HIW"」 之" HIC"  霜冷长河 \n" NOR, me, target); 

	if (ap * 2/3  + random(ap) > dp)
	{
	  damage = ap + random(ap/2);
               msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage,
               25 + random(50),(: final3, me, target, damage, weapon, lvl :));
	} else
	{
               msg = CYN "可是$n" CYN "收敛心神，奋力招"
                      "架，将剑招卸于无形。\n" NOR;
	}
        message_vision(msg, me, target);

	// 第四招

	message_vision(HIW"\n        「回"HIY"天"HIW"剑"HIR"舞"HIW"」 之" HIM"  玄羽乱舞 \n" NOR, me, target); 

	if (ap * 2/3  + random(ap) > dp)
	{ 
	       damage = ap + random(ap/2);
	       msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 
	       25 + random(60),(: final4, me, target, damage, weapon, lvl :));        
	} else
	{
               msg = CYN "可是$n" CYN "收敛心神，奋力招"
                      "架，将剑招卸于无形。\n" NOR;
	}
	message_vision(msg, me, target);

	// 第五招

	message_vision(HIW"\n          「回"HIY"天"HIW"剑"HIR"舞"HIW"」 之" HIY"  七星追月 \n" NOR, me, target); 

	if (ap * 2/3  + random(ap) > dp)
	{
	      damage = ap + random(ap/2);
	       msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 
	       30 + random(70),(: final5, me, target, damage, weapon, lvl :));        
	} else
	{
	       msg = CYN "可是$n" CYN "收敛心神，奋力招"
	              "架，将剑招卸于无形。\n" NOR;
	}
	message_vision(msg, me, target);

	/* call_out("hui_ok", 1 + random(2), me);     */
	me->start_busy(2 + random(4));
	me->add("neili", -1000);
	//me->set_temp("no_hui",1);
	
	return 1;
}

/* void hui_ok(object me)
{
	if (!me) return;
	me->delete_temp("no_hui");
} */

string final1(object me, object target, int damage)
{
        return HIG " $n" HIG "如痴如醉的望着宛如凌波仙子的" HIG"$N" HIG"，完全忘却了躲闪！\n" NOR;
}

string final2(object me, object target, int damage)
{
        return HIG " $n" HIG "一瞥" HIG"$N" HIG"，惊若天人，僵立当场！\n" NOR;
}

string final3(object me, object target, int damage)
{
        return HIG " $n" HIG "望见" HIG"$N" HIG"，不由得心驰神荡，魂不守舍！\n" NOR;
}

string final4(object me, object target, int damage)
{
        return HIG " $n" HIG "自惭形秽，无地自容，防御破绽百出！\n" NOR;
}

string final5(object me, object target, int damage)
{
        return HIG " $n" HIG "长叹一声，自愧不如，顺手提起长剑就往自己颈上抹去！\n" NOR;
}