// qi.c 无形剑气

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define QI "「" HIG "无形剑气" NOR "」"

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg,str;
        int ap, dp;

        if (! target) target = offensive_target(me);


        if (userp(me) && ! me->query("can_perform/liumai-shenjian/qi"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(QI "只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("force") < 420)
                return notify_fail("你的内功火候不够，使不出" QI "。\n");

        if (me->query("max_neili") < 5000)
                return notify_fail("你的内力修为还不足以使出如此犀利的" QI "。\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("你的真气不够，无法使用" QI "。\n");

        if (me->query_skill("liumai-shenjian", 1) < 200)
                return notify_fail("你的六脉神剑修为有限，无法使用" QI "！\n");

        if (me->query_skill_prepared("finger") != "liumai-shenjian")
                return notify_fail("你没有准备六脉神剑，无法使用" QI "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIG "$N" HIG "中指一按，一股凌厉无伦的无形剑气直奔$n" HIG "胸前射去。\n" NOR;  

        ap = me->query_skill("finger")+  (me->query_skill("jingluo-xue", 1) + me->query_skill("lamaism", 1)  + me->query_skill("buddhism", 1)) / 2 ;
        dp = target->query_skill("force") + (target->query_skill("jingluo-xue", 1) + target->query_skill("lamaism", 1)  + target->query_skill("buddhism", 1)) / 2;
        weapon = target->query_temp("weapon");
       
        if (ap * 3 / 5 + random(ap) > dp)
        { 
                damage = ap + (int)me->query_skill("yiyang-zhi", 1) + (int)me->query_skill("canhe-zhi", 1) + random(ap * 6);
                me->add("neili", -300);
                if (! objectp(weapon) || weapon->query("skill_type") == "pin")                     
				{
						msg +=  HIR "$n" HIR "只觉得胸前一阵剧痛，鲜血自创口激射而出，眼前顿时一黑！\n" NOR;
				        target->receive_wound("qi",damage,me);
		                str =  COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		                msg += "($n"+str+")\n" ;	
				}
                else
                if (weapon->is_item_make() || weapon->query("damage") > 180 || weapon->query("skill_type") == "hammer")
				{
                        msg += HIR "$n" HIR "横" + weapon->name() + HIR "试图招架，"
                                     HIR "怎奈这股剑气如此犀利，透过" + weapon->name() +
                                     HIR "直震得$n" HIR "狂吐鲜血，五脏六腑都要翻转过来！\n" NOR;
				        target->receive_wound("qi",damage,me);
		                str =  COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		                msg += "($n"+str+")\n" ;	
		        }
                else
                {
                        msg +=  HIR "$n" HIR "横转" + weapon->name() + HIR "，挡在胸"
                                             "前，只听啪啦一声，" + weapon->name() +
                                      HIR "碎成数截，激飞上天！\n$n" HIR "连退"
                                            "几步，“哇”的吐了一口鲜血，脸色变的惨白。\n" NOR;
                        target->receive_wound("qi",damage,me);
		                str =  COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		                msg += "($n"+str+")\n" ;	
                        weapon->move(environment(me));
                        weapon->set("no_wield", weapon->name() + "已经碎掉了，没法装备了。\n");
                        weapon->set_name("碎掉的" + weapon->name());
                        weapon->set("value", 0);
                }
        } else
        {
                msg += CYN "可是$p" CYN "内功颇为深厚，轻轻将这道剑气化解于无形。\n" NOR;
        }
        message_combatd(msg, me, target);

		me->start_busy(1+random(2));

        return 1;
}

