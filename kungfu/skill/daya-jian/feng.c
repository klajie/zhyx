// feng.c 大雅剑 风雨如晦
//Created by kasumi
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define feng "「" HIM "风雨如晦" NOR "」"


int perform(object me, object target)
{
	object weapon;
    int damage,ap,dp,n,i;
	int skill;
	string msg;

	if (! target) target = offensive_target(me);

	if (userp(me) && ! me->query("can_perform/daya-jian/feng"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

	if (! target || ! me->is_fighting(target))
		return notify_fail(feng"只能对战斗中的对手使用。\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");

	if ((int)me->query_skill("daya-jian", 1) < 180)
		return notify_fail("你的大雅剑不够娴熟，不会使用「风雨如晦」。\n");
	
	if ((int)me->query_skill("force") < 270)
		return notify_fail("你的内功不够娴熟，不会使用「风雨如晦」。\n");
	
	if ((int)me->query("neili") < 400)
		return notify_fail("你的内力不够。\n");	

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");	  


	   msg = HIG "$N" HIG "心随意动，以气御剑，只见千千万万道剑光裹着一条白色的影子回旋飞舞，\n"
		     HIG"剑身微颤，破空之声犹如惊涛骇浪......\n"NOR;
	    ap = me->query_skill("sword") + me->query_skill("tanqin-jifa", 1);
        dp = target->query_skill("dodge") + target->query_skill("tanqin-jifa", 1);

		if (me->query_skill("chess", 1) > 250)
		{
			ap=ap+me->query_skill("chess", 1);
			dp=dp+target->query_skill("chess", 1);
		}

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = ap + random(ap);                
                me->add("neili", -150);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                           HIR "$n" HIR "只觉嗡嗡一阵耳鸣，浑身剧痛，仿佛浑身骨节寸寸断裂！\n" NOR);

				if (me->query_skill("chess", 1) >= 275 && me->query("family/family_name") == "昆仑派")
				{
					msg += HIW"只听琴声渐弱，剑气尤加。漫天剑影如星罗棋布的棋网洒向$n。\n"NOR;
					n= 1 + random((int) (me->query_skill("chess", 1)/100));
					if (n>5)
						n=5;
					for (i = 0; i < n; i++)
					{
						  damage = ap + random(ap/2);  
			              msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50+random(10),
                                           HIR "$n" HIR "只觉眼前一黑，几道白光闪过，身上已中数剑，血流不止！\n" NOR);
						  me->add("neili", -150);
					}
				}

        } else
        {
                me->start_busy(2);
                msg += CYN "可是$n" CYN "看破了$N"
                       CYN "的企图，向旁一跃，躲了开去。\n" NOR;
        }

        message_combatd(msg, me, target);
	return 1;
}
