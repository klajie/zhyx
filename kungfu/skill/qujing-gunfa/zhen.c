//3招化学连，攻击命中均和佛法有关。
#include <ansi.h>
#include <combat.h>

#define ZHEN "「" HIR "震雷乾坤" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, ap, dp, count;
		int damage;

        /*if (userp(me) && ! me->query("can_perform/qujing-gunfa/zhen"))
                return notify_fail("你所使用的外功中没有这种功能。\n");
                */

        if (! target) target = offensive_target(me);
		
		weapon = me->query_temp("weapon"); 

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHEN "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "club")
                return notify_fail("你使用的武器不对，难以施展" ZHEN "。\n");

        if (me->query_skill_mapped("club") != "qujing-gunfa")
                return notify_fail("你没有激发取经棍法，难以施展" ZHEN "。\n");

        if(me->query_skill("qujing-gunfa", 1) < 200 )
                return notify_fail("你取经棍法不够娴熟，难以施展" ZHEN "。\n");

        if( (int)me->query_skill("force") < 350 )
                return notify_fail("你的内功修为不够，难以施展" ZHEN "。\n");

        if( (int)me->query("max_neili") < 4500 )
                return notify_fail("你的内力修为太弱，难以施展" ZHEN "。\n");

        if( (int)me->query("neili") < 300 )
                return notify_fail("你现在的真气太弱，难以施展" ZHEN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

			  
        msg = HIW "$N" HIW "将手中" + weapon->name() + HIW "缓缓压向$n"
              HIW "，棍体隐隐带着风雷之劲，正是取经棍法杀着「" HIR "震"
              "雷乾坤" HIW "」！\n只见棍端竟全被紫电所笼罩，" +
              weapon->name() + HIW "幻作千百根相似，霹雳间连续向" HIW"$n" HIW"砸出了三招！\n" NOR;			  

        ap = me->query_skill("club") + me->query_skill("force") + me->query_skill("buddhism" ,1) / 2;
        dp = target->query_skill("parry") + target->query_skill("force");
		damage = ap / 2 + random(ap/2);


		msg += HIM"       ┃大闹阎罗府┃\n"  NOR; 
              
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                   HIR "结果只听见「轰」地一声巨响，$n被砸得血肉模糊，惨不忍睹！。\n" NOR);            
        
		msg += HIR "       ┃勇斗二郎神┃\n" NOR; 
              
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                   HIR "结果只听见「轰」地一声巨响，$n被砸得血肉模糊，惨不忍睹！。\n" NOR);     
								   
		msg += HIY"       ┃千钧澄玉宇┃\n" NOR; 
              
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                   HIR "结果只听见「轰」地一声巨响，$n被砸得血肉模糊，惨不忍睹！。\n" NOR);     								   
					
        message_combatd(msg, me, target);
        me->start_busy(3 + random(4));
        return 1;
}


