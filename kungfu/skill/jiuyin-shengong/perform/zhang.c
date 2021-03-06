// zhang.c 九阴焚身掌
// created by kasumi

#include <ansi.h>

inherit F_SSERVER;

#define ZHANG "「" HIM "九阴焚身掌" NOR "」"

int perform(object me, object target)
{
	    string msg,name,parry_str;
	    object equipment;
        int ap, dp;
        int i, times, count;


	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail(ZHANG "只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon"))
                return notify_fail("此招只能空手施展！\n");

	if ((int)me->query_skill("jiuyin-shengong", 1) < 349)
		return notify_fail("你的九阴神功不够深厚，不会使用" ZHANG "。\n");	

        if (me->query_skill_prepared("unarmed") != "jiuyin-shengong"
           && me->query_skill_prepared("strike") != "jiuyin-shengong")
                return notify_fail("你没有准备使用九阴神功，无法施展" ZHANG "。\n");

	if ( me->query("neili") < 800 )
		return notify_fail("你的内力不够，不能使用" ZHANG "。\n");

        if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

	msg = HIY "$N" HIY "双掌一错，幻化出无数掌影，层层叠荡向$n"
              HIY "逼去！\n" NOR;
              
  message_combatd(msg, me, target);
		parry_str=target->query_skill_mapped("parry");
        ap = me->query_skill("jiujin-shengong", 1);
        dp = target->query_skill("parry", 1);

        if (ap * 3/5 + random(ap) > dp)
                count = ap / 6; 
        else count = ap / 8;
		if (me->query("reborn")) {
			target->map_skill("parry", 0);
		}

        me->add_temp("apply/attack", count);		
        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
                                //破手套
				                if (objectp(equipment = target->query_temp("armor/hands")) && random(3)==1)
								{
                                    if (equipment->query("consistence") < 15 )
								    {
									  name = equipment->name();                                                        
                                      equipment->set("consistence", 0);									 
                                      equipment->move(environment(me));
							       	  message_combatd(HIC "只听“轰”的一声闷响，$n" HIC "身"
                                       "着的" + name + HIC "在$N" HIC "内力震荡"
                                       "下应声而裂，化成一块块碎片。\n" NOR, me, target);                                      
								    }  
									else
                                    {
                                      name = equipment->name();                                      
								      equipment->add("consistence", -10);
									  message_combatd(HIW "只听“砰”的一声闷响，$n" HIW "身"
                                       "上的" + name + HIW "在$N" HIW "内力震荡"
                                       "下闪现出一丝裂痕。\n" NOR, me, target);
								    }
									continue;
								}
								//破防具
								if (objectp(equipment = target->query_temp("armor/cloth")) && random(3)==1)
								{
                                    if (equipment->query("consistence") < 15 )
								    {
									  name = equipment->name();                                                        
                                      equipment->set("consistence", 0);									 
                                      equipment->move(environment(me));
							       	  message_combatd(HIC "只听“轰”的一声闷响，$n" HIC "身"
                                       "着的" + name + HIC "在$N" HIC "内力震荡"
                                       "下应声而裂，化成一块块碎片。\n" NOR, me, target);                                      
								    }  
									else
                                    {
                                      name = equipment->name();                                      
								      equipment->add("consistence", -10);
									  message_combatd(HIW "只听“砰”的一声闷响，$n" HIW "身"
                                       "上的" + name + HIW "在$N" HIW "内力震荡"
                                       "下闪现出一丝裂痕。\n" NOR, me, target);
								    }
									continue;
								}
								//破甲								
								if (objectp(equipment = target->query_temp("armor/armor")) && random(3)==1)
								{
                                    if (equipment->query("consistence") < 15 )
								    {
									  name = equipment->name();                                                        
                                      equipment->set("consistence", 0);									 
                                      equipment->move(environment(me));
							       	  message_combatd(HIC "只听“轰”的一声闷响，$n" HIC "身"
                                       "着的" + name + HIC "在$N" HIC "内力震荡"
                                       "下应声而裂，化成一块块碎片。\n" NOR, me, target);                                      
								    }  
									else
                                    {
                                      name = equipment->name();                                      
								      equipment->add("consistence", -10);
									  message_combatd(HIW "只听“砰”的一声闷响，$n" HIW "身"
                                       "上的" + name + HIW "在$N" HIW "内力震荡"
                                       "下闪现出一丝裂痕。\n" NOR, me, target);
								    }
									continue;
								}
        }
		if (me->query("reborn")) {
			target->map_skill("parry", parry_str);
		}
        me->start_busy(3 + random(5));
        me->add("neili", -700);

        me->add_temp("apply/attack", -count);
		
	

	return 1;
}
