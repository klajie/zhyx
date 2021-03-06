// zhi.c 九阴无极指
// created by kasumi

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define ZHI "「" HIY "九阴无极指" NOR "」"

int perform(object me, object target)
{
        string msg,wp;
        object weapon;
        int n,count;
        int skill, ap, dp, damage;


        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        skill = me->query_skill("jiuyin-shengong", 1);

        if (! me->is_fighting(target))
                return notify_fail(ZHI "只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon"))
                return notify_fail(ZHI "只能空手施展！\n");

        if (skill < 299)
                return notify_fail("你的九阴神功等级不够，无法施展" ZHI "！\n");

        if (me->query("neili") < 800)
                return notify_fail("你现在真气不够，难以施展" ZHI "！\n");

        if (me->query_skill_prepared("finger") != "jiuyin-shengong"
           && me->query_skill_prepared("unarmed") != "jiuyin-shengong")
                return notify_fail("你没有准备使用九阴神功，无法施展" ZHI "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        me->add("neili", -400);

        ap = me->query_skill("jiuyin-shengong", 1) + me->query_skill("martial-cognize", 1);
        dp = target->query_skill("jiuyin-shengong",1) + target->query_skill("martial-cognize", 1);

        msg = HIY "$N" HIY "出手成指，随意点戳，似乎看尽了$n"
              HIY + "招式中的破绽。\n" NOR;
        if (ap + random(ap) > dp)
        {
                n = 8;
                if (ap * 3 / 5 + random(ap*2) > dp)
                {
					    count = ap / 5 ;
						me->add_temp("apply/attack", count);
	         	me->add_temp("apply/unarmed_damage", count / 2);
                        
						msg += HIY "$n" HIY "见来指玄幻无比，全然无法抵挡，慌乱之下破绽迭出，$N"
                               HIY "随手连出" + chinese_number(n) + "指！\n" NOR;
                        
						message_combatd(msg, me, target);
                        
                        while (n-- && me->is_fighting(target))
                        {
                                if (random(2) && ! target->is_busy())
                                	target->start_busy(1);
								if (me->query("reborn")) {
									damage = ap*2/3 + random(ap);
									msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 85 + random(15),
									HIR "只听噗嗤一声，$n" HIR "身上已经多了一个血肉模糊的窟窿！\n" NOR);
									message_combatd(msg, me, target);
								}else{
									COMBAT_D->do_attack(me, target, 0, 0);	
								}								
								if (objectp(weapon = target->query_temp("weapon")) && random(2)==1)
								{
                                    if (weapon->query("consistence") < 15 )
								    {
									  wp = weapon->name();                                                        
                                      weapon->set("consistence", 0);									 
                                      weapon->move(environment(me));
							       	  message_combatd(HIC "只听“锵”的一声脆响，$n" HIC "手"
                                                "中的" + wp + HIC "在$N" HIC "内力激荡"
                                                "下应声而碎，脱手跌落在地上。\n" NOR, me, target);                                      
								    }  
									else
                                    {
                                      wp = weapon->name();                                      
								      weapon->add("consistence", -10);
									  message_combatd(HIW "只听“珰”的一声，$n" HIW "手"
                                                "中的" + wp + HIW "在$N" HIW "内力激荡"
                                                "下颤抖不已。\n" NOR, me, target);
								    }
								}
                        } 
						me->start_busy(2 + random(5));
						me->add_temp("apply/attack", - count);
		        me->add_temp("apply/unarmed_damage", - count / 2);
                } else
                {
                        msg += HIY "$n" HIY "不及多想，连忙抵挡，全然无法反击。\n" NOR;
			            if (! target->is_busy())
                        	target->start_busy(5);
                        	message_combatd(msg, me, target);
                }
        } else
        {
                msg += HIC "不过$n" HIC "紧守门户，不露半点破绽。\n" NOR;
                me->start_busy(3 + random(4));
                message_combatd(msg, me, target);
        }

        
        return 1;
}
