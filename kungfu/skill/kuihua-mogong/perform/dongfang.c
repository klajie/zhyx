//created by kasumi
#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";
#define DF "「" HIR "日"HIW"出东方" NOR "」"


inherit F_SSERVER;
int dongfang_hit(object me);
int perform(object me, object target)
{    
string msg = "";
    int damage, count, i;
    object weapon = me->query_temp("weapon");
    
    if (! target)
    {
        me->clean_up_enemy();
        target = me->select_opponent();
    }

    if (! target || ! me->is_fighting(target))
		return notify_fail(DF"只能对战斗中的对手使用。\n");	
	  

    if ( me->query_skill_mapped("unarmed") != "kuihua-mogong" || me->query_skill_prepared("unarmed") != "kuihua-mogong" )
                return notify_fail("你激发葵花魔功为拳脚，并且备好才能使用"DF"。\n");

    if (!weapon || weapon->query("skill_type") != "sword" || me->query_skill_mapped("sword") != "kuihua-mogong" ) 
                return  notify_fail("你需要装备剑和激发剑法为葵花魔功才能使用"DF"。\n");
    
    if ((int)me->query_skill("kuihua-mogong", 1) < 500)
        return notify_fail("以你目前的修为来看，还不足以运用"DF"\n");
    
    if (me->query("max_neili") < 6000)
        return notify_fail("你的内力修为不够运用"DF"所需！\n");
    
    if (me->query("neili") < 2000)
        return notify_fail("你的内力不够运用"DF"所需！\n");
		
    if (! living(target))
        return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
		
	weapon = me->query_temp("weapon");
  
msg += HIM "$N冷冷地扫了$n一眼，“呼”地一下失去了踪影，随之而来的是如暴雨般的漫天剑影，伴随着$N的歌声......\n";
	msg += HIG "\n                              天下风云出我辈，\n\n";
	message_combatd(msg, me, target);
	
	count = me->query_skill("kuihua-mogong", 1);
    me->add_temp("apply/attack", count);  
    me->add_temp("apply/damage",count);  
    
	for (i = 0; i < 5; i++)
	{
	   if (! me->is_fighting(target))
            break;
       if (random(2)==1 && ! target->is_busy())
            target->start_busy(1);
		COMBAT_D->do_attack(me, target, weapon, 0);
		me->add("neili", -50);
	}
	me->add_temp("apply/attack", -count);  
    me->add_temp("apply/damage",-count);  
    

	msg = HIG "\n                              一入江湖岁月催。\n\n";
	msg += HIM"剑雨渐小，忽然一道剑光宛若一道霹雳，劈向$n......\n";
    damage = (int)me->query_skill("kuihua-mogong", 1) + (int)me->query_skill("sword", 1);
	damage = damage*3 + random(damage*2);
	msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                   HIR "$n" HIR "闪避不及，长剑穿胸而过，鲜血飘散，之前的剑雨变成了如今的血雨。\n" NOR);   
    message_combatd(msg, me, target);
	me->add("neili", -250);


    weapon->move(me, 1);
    msg = HIG "\n                              鸿图霸业谈笑中，\n\n";
    msg += HIM"$N反转长剑，“呼”的欺身而近，无数掌影拍向$n全身要害$n......\n";	
	message_combatd(msg, me, target);
	me->add_temp("apply/attack", count);  
    me->add_temp("apply/damage",count);  
	for (i = 0; i < 5; i++)
	{
	   if (! me->is_fighting(target))
            break;
       if (random(2)==1 && ! target->is_busy())
            target->start_busy(1);
		COMBAT_D->do_attack(me, target, 0, 0);
		me->add("neili", -50);
	}
	me->add_temp("apply/attack", -count);  
    me->add_temp("apply/damage",-count);
	

	msg = HIG "\n                              不胜人间一场醉。\n\n";
	msg += HIM"$N于乱掌之中，突然伸出一指，直刺向$n胸口要穴......\n";	
	damage = (int)me->query_skill("kuihua-mogong", 1) + (int)me->query_skill("unarmed", 1);
	damage = damage*3 + random(damage*2);	
	msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                   HIR "$n" HIR "闪避不及，胸口要穴中招，“哇”地吐出一大口鲜血。\n" NOR);   
    message_combatd(msg, me, target);
	me->add("neili", -250);
	weapon->wield();
	
	me->start_busy(3+random(3));  


	if( (int)me->query("neili") > 1000
                &&  present(target->query("id"), environment(me)) 
                &&  me->is_fighting(target) 
                &&  living(target)
                &&  living(me)
                &&  me->is_fighting()
                &&  target->is_fighting()
                &&  !target->is_ghost()
                &&  me->query("reborn")
                &&  !me->is_ghost()
				)
	{
	   remove_call_out("dongfang_hit");
           if (me->query("family/master_name") == "东方不败")
                call_out("dongfang_hit",1, me);
           else call_out("dongfang_hit",1+random(2), me);
	}
return 1;
}

int dongfang_hit(object me)
{
     
     object target;
     string msg;
     int damage,i,p;
	 object weapon = me->query_temp("weapon");
	 if( !target ) target = offensive_target(me);   
        if(!living(target))     return 1;

	 msg = HIY "突然间狂风骤雨般的攻击突然停止了，周围一切都陷入了死寂，仿佛空气都已凝结。\n"
	       HIY "$N手中的"+ weapon->name()+ HIY "渐渐发出炫目的万道光华，正如初升的太阳，这正是：\n"
		   HIR "\n                              日出东方，唯我不败！！\n\n" NOR;
     message_combatd(msg, me);
	 
	 damage = (int)me->query_skill("kuihua-mogong", 1) + (int)me->query_skill("force");
	 damage = damage*4 + random(damage*2);

	 target->receive_wound("qi", damage, me);
	 target->set("neili",0);
	 target->set("jingli",0);
	 p = (int)target->query("qi") * 100 / (int)target->query("max_qi");
		
	msg = HIR "光华闪过，$n却是呆立当场，七窍流血，神情扭曲，全身精力内力尽失。\n" NOR;
	msg += "( " + target->name() + eff_status_msg(p) + " )\n\n";
	message("vision", msg, environment(me), target); 
	 
	 me->add("neili", -500);
	 me->start_busy(2);  
}





