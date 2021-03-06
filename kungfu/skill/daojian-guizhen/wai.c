#include <ansi.h>
#include <combat.h>

#define TIANWAI "「" HIR "刀剑啸傲天外天" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string type1, type2, msg,name;
        object weapon1, weapon2;
		object equipment;
        int ap, dp, damage, str;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(TIANWAI "只能对战斗中的对手使用。\n");

        weapon1 = me->query_temp("weapon");
        weapon2 = me->query_temp("handing");

        if (! objectp(weapon1) || ! objectp(weapon2))
                return notify_fail("你没有同时装备刀剑，难以施展" TIANWAI "。\n");

        if (weapon2->query("consistence") <= 0)
                return notify_fail("你的" + weapon2->name() + "已经严重"
                                   "损坏，无法继续使用了。\n");

        type1 = weapon1->query("skill_type");
        type2 = weapon2->query("skill_type");

        if ((type1 != "sword" && type1 != "blade")
           || (type2 != "sword" && type2 != "blade"))
                return notify_fail("你所使用的武器不对，难以施展" TIANWAI "。\n");

        if ((type1 == "sword" && type2 != "blade")
           || (type1 == "blade" && type2 != "sword"))
                return notify_fail("你没有同时装备刀剑，难以施展" TIANWAI "。\n");

        if (me->query_skill_mapped("sword") != "daojian-guizhen"
           || me->query_skill_mapped("blade") != "daojian-guizhen")
                return notify_fail("你没有激发刀剑归真，难以施展" TIANWAI "。\n");

        if (me->query_skill("daojian-guizhen", 1) < 800)
                return notify_fail("你的刀剑归真等级不够，难以施展" TIANWAI "。\n");

        if (me->query_skill("lengyue-shengong", 1) < 500)
                return notify_fail("你的冷月神功等级不够，难以施展" TIANWAI "。\n");

	if (! me->query("reborn"))        
		return notify_fail("你尚未转世重生，无法领会此绝招！\n");    

        if (me->query_skill("force") < 1000)
                return notify_fail("你的本门内功都没学好，难以施展" TIANWAI "。\n");

        if (me->query("neili") < 1500)
                return notify_fail("你现在的真气不够，难以施展" TIANWAI "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        ap = me->query_skill("sword") +
             me->query_skill("blade") +
             me->query_skill("force");

        dp = target->query_skill("force") +
             target->query_skill("sword") +
             target->query_skill("blade");

        damage = ap + random(ap);

        msg = HIY "$N" HIY "将" + weapon1->name() + HIY "与" + weapon2->name() + HIY "横置于胸前，运转出功力，内劲如海啸般爆发。\n"
              HIY"空气、云都变成了暗红色，整个天地灵气，一草一木上散发出来的生机，包括你强大的杀气、刀魂、剑意，\n"
              HIY"在瞬间全部凝聚成一起，随着手中的的共鸣，所有阻挡在 \n"
              HIY "$n" HIY "面前的东西，好像全部在瞬间被击碎，破开，整个天空，也似乎被斩成了两半。\n"
              HIY"这一人、一刀、一剑毫不留情的，狠狠的飞向了$n。 \n" NOR;

        if (ap / 2 + random(ap) > dp)
        {

                msg += HIR "$n" HIR "见$N" HIR "杀气大涨，不禁心"
                       "生惧意，招架顿时散乱，全然不成章理。\n" NOR;
                ap += ap / 2;
                damage += damage;
        } else
        {
                msg += HIG "$n" HIG "见$N" HIG "杀气大涨，丝毫不"
                       "敢大意，急忙收敛心神，努力不受干扰。\n" NOR;
        }

        msg += HIW "\n突然间$N" HIW "身形一展，右手" + weapon1->name() +
               HIW "忽地一振，凌空卷出一道半弧，直劈$n" HIW "而去。\n" NOR;

        if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                           HIR "$n" HIR "奋力抵挡，却哪里招架得住"
                                           "，被$N" HIR "一招划中要脉，鲜血四处飞"
                                           "溅。\n" NOR);
				//破防具
				if (objectp(equipment = target->query_temp("armor/cloth")) && random(3)==1)
				{
					name = equipment->name();                                                        
					equipment->set("consistence", 0);									 
					equipment->move(environment(me));
					msg += MAG "只听“轰”的一声闷响，$n" MAG "身"
										"着的" + name + MAG "在$N" MAG "刀锋剑气震荡"
										"下应声而裂，化成一块块碎片。\n" NOR;   
				}
				//破甲								
				if (objectp(equipment = target->query_temp("armor/armor")) && random(3)==1)
				{
					name = equipment->name();                                                        
					equipment->set("consistence", 0);									 
					equipment->move(environment(me));
					msg += MAG "只听“轰”的一声闷响，$n" MAG "身"
										"着的" + name + MAG "在$N" MAG "刀锋剑气震荡"
										"下应声而裂，化成一块块碎片。\n" NOR;   
				}
        } else
        {
                msg += CYN "$n" CYN "心知这一招的凌厉，急忙凝神"
                       "聚气，小心拆招，丝毫无损。\n" NOR;
        }

        msg += HIW "\n接着$N" HIW "又将左手" + weapon2->name() +
               HIW "朝$n" HIW "平平递出，招式看似简单，却蕴藏着"
               "极大的杀着。\n" NOR;

        if (ap * 3 / 4 + random(ap) > dp)
        {
                // 转移武器
                weapon1->move(me, 1);
                weapon2->wield();

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 110,
                                           HIR "$n" HIR "只觉眼花缭乱，全然无法洞"
                                           "察先机，$N" HIR "一招命中，射出一柱鲜"
                                           "血。\n" NOR);
                // 转移回初始状态
                weapon2->move(me, 1);
                weapon1->wield();
                me->set_temp("handing", weapon2);
			//破手套
			if (objectp(equipment = target->query_temp("armor/hands")) && random(3)==1)
			{
					name = equipment->name();                                                        
					equipment->set("consistence", 0);									 
					equipment->move(environment(me));
					msg += MAG "只听“轰”的一声闷响，$n" MAG "身"
										"着的" + name + MAG "在$N" MAG "刀锋剑气震荡"
										"下应声而裂，化成一块块碎片。\n" NOR;  
			}
			//破兵器
			if (objectp(equipment = target->query_temp("weapon")) && random(3)==1)
			{
					name = equipment->name();                                                        
					equipment->set("consistence", 0);									 
					equipment->move(environment(me));
					msg += MAG "只听“轰”的一声闷响，$n" MAG "手"
										"持的" + name + MAG "在$N" MAG "刀锋剑气震荡"
										"下应声而裂，化成一块块碎片。\n" NOR;  
			}
        } else
        {
                msg += CYN "$n" CYN "心知这一招的凌厉，急忙凝神"
                       "聚气，小心拆招，丝毫无损。\n" NOR;
        }


     if ((int)target->query("qi")> 0&& me->is_fighting(target) && (int)me->query_skill("daojian-guizhen", 1) > 799 && !userp(target))
             {                              
                           if (ap + random(ap) > dp)
                           {       
                            target->receive_damage("qi", damage*2, me);
                            target->receive_wound("qi", damage, me);
	        	      str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
                           msg += HIC"猛然间，"HIC"$N"HIC"手中"+ weapon1->name() + HIC "和" + weapon2->name() + HIC"发出震天般的长啸，伴随着两道光华飞至天际，\n"
                                 HIC"但见风云突变，两道光华从天边划过，飞向" HIC"$n，正是刀剑最强绝招：  \n	 "             
                                 HIR"\n     ★" HIG"★" HIY"★" HIB"★" HIM"★" HIC"★" HIW"★" HIR"★" HIG"★" HIY"★" HIB"★" HIM"★" HIC"★" HIW"★\n"
                                               HIY"     " HIR"★"  HIY"  " HIY " 刀 "  HIC " 剑 "  HIR" 啸 "  HIW" 天 "  HIB" 外 " HIY"  " HIC"★"
                                                 HIR"\n     ★" HIG"★" HIY"★" HIB"★" HIM"★" HIC"★" HIW"★" HIR"★" HIG"★" HIY"★" HIB"★" HIM"★" HIC"★" HIW"★\n\n" 
                                  HIC"$n"HIC "腾挪闪躲，竭尽全力，也没办法躲开这一刀、一剑，被击了个正着！\n" NOR;
                           msg += "($n"+str+")\n";   
                                       if (random(3) == 1
                                           && target->query("neili"))
                                          {
                                           msg += HIY "\n$n" HIY "的丹田恰好被$N" HIY "刀剑连中，全身真气涣"
                                           "散，宛如黄河决堤，内力登时狂泻而出。\n\n" NOR;
	              	                             target->set("neili", 0);
                                             }
                             }
                         else
                          {
                                   msg += CYN "幸而$n" CYN "精通刀剑，严阵以待，$N" CYN "无处下手。\n" NOR;
                         }  
                }
        me->start_busy(3 + random(3));
        me->add("neili", -1800);
        message_combatd(msg, me, target);
        return 1;
}
