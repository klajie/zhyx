#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define ZONG "「" HIM "万剑纵横" NOR "」"

int perform(object me, object target)
{
        string msg,parry_str;
        int ap, dp,i,delta,lvl;
        int damage, skill;

        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/liumai-shenjian/zong"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZONG "只能对战斗中的对手使用。\n");

        if (me->query_skill_prepared("finger") != "liumai-shenjian")
                return notify_fail("你没有准备使用六脉神剑，无法施展" ZONG "。\n");

        skill = me->query_skill("liumai-shenjian", 1);

        if (skill < 500)
                return notify_fail("你的六脉神剑修为有限，无法使用" ZONG "！\n");

        if (me->query_skill("force") < 500)
                return notify_fail("你的内功火候不够，难以施展" ZONG "！\n");

        if (me->query("max_neili") < 8500)
                return notify_fail("你的内力修为不够,无法施展" ZONG "！\n");

        if (me->query("neili") < 1500)
                return notify_fail("你的内力不够，现在无法施展" ZONG "！\n");

        if (me->query_temp("weapon"))
                return notify_fail("你必须是空手才能施展" ZONG "！\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");


        msg = HIM "$N" HIM "一声清啸，十指纷弹，顿觉六脉剑谱已涌上心头，此起"
              "彼伏、连绵不绝。霎时剑气如奔，连绵无尽的万道剑气豁然贯向$n" HIM 
              "！\n" NOR;

        ap = me->query_skill("finger") + me->query_skill("force");
        dp = target->query_skill("parry") + target->query_skill("force");
        
        damage = ap*3/2 + (int)me->query_skill("jingluo-xue", 1)+(int)me->query_skill("yiyang-zhi", 1) + (int)me->query_skill("canhe-zhi", 1);
        damage = damage + random(damage);
        
        parry_str=target->query_skill_mapped("parry");

		lvl = (int) me->query_skill("kurong-changong", 1);
        
        if (lvl * 2 / 3 +random(lvl) > target->query_skill("force", 1))
		{
			target->map_skill("parry", 0);
		}

		if (lvl > 900)
		{delta = 500;}
		else if (lvl > 600)
		{delta = 300;}
		else if (lvl > 300)
		{delta = 200;}
		else delta = 0;

        
        if (ap + random(ap) > dp)
        {               	 
                me->add("neili", -400);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 150,
                                           HIR "只听$n" HIR "一声惨叫，万道剑气已"
                                           "透体而过，伤口处鲜血顿时狂涌，痛苦难当！\n" NOR);
        } else
        {
                me->add("neili", -200);
               
                msg += CYN "$n" CYN "见$N" CYN "来势汹涌，不敢轻易"
                       "招架，急忙提气跃开。\n" NOR;
        }
        message_combatd(msg, me, target);
        
        if ((int)target->query("qi")> 0&& me->is_fighting(target))
        {        
              msg = HIW "紧接着"HIW"$N" HIW "摊开双手，手指连弹，霎时间空气炙热，几"
              "欲沸腾，六道剑气分自六穴，一起冲向$n" HIW "！\n" NOR;

              msg += HIR "$n" HIR "只感剑气纵横，微一愣神，不禁心萌退意。\n" NOR;                  

                message_combatd(msg, me, target);

                me->add("neili", -600);               
                target->add_temp("apply/dodge", -delta);
                for (i = 0; i < 6; i++)
                {
               			 if (! me->is_fighting(target))
                        break;

                		if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);                

                	COMBAT_D->do_attack(me, target, 0, i * 3);
                }                
                target->add_temp("apply/dodge", delta);
       }
       me->start_busy(3+random (5));
       target->map_skill("parry", parry_str);
       

        return 1;
}

