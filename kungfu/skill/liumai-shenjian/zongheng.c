#include <ansi.h>
#include <combat.h>

#define ZONGHENG "「" HIY "六脉纵横" NOR "」"

inherit F_SSERVER;


int perform(object me, object target)
{
        mapping prepare;
        string msg, wp;
        int skill;        
        int damage;       
        int ap, dp, pp, p, str, aa, ab, ac;
        object weapon;

        if (! target) target = offensive_target(me);
        	   

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZONGHENG "只能对战斗中的对手使用。\n");

        if (me->query_skill_prepared("finger") != "liumai-shenjian")
                return notify_fail("你没有准备使用六脉神剑，无法施展" ZONGHENG "。\n");

        skill = me->query_skill("liumai-shenjian", 1);

        if (skill < 800)
                return notify_fail("你的六脉神剑修为有限，无法使用" ZONGHENG "。\n");

        if (me->query_skill("force") < 1200)
                return notify_fail("你的内功火候不够，难以施展" ZONGHENG "。\n");

        if (me->query("max_neili") < 12000)
                return notify_fail("你的内力修为没有达到那个境界。\n");

	if (! me->query("reborn"))        
		return notify_fail("你尚未转世重生，无法领会此绝招！\n");   

        if (me->query("neili") < 1000)
                return notify_fail("你的真气不够，现在无法施展" ZONGHENG "。\n");

        if (me->query_temp("weapon"))
                return notify_fail("你必须是空手才能施展" ZONGHENG "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "摊开双手，手指连弹，霎时间空气炙热，几"
              "欲沸腾，六道剑气分自六穴，一起冲向$n" HIW "！\n\n" NOR;   

                pp = (int)me->query_skill("buddhism", 1) + (int)me->query_skill("lamaism", 1);

		  damage = (int)me->query_skill("finger",1)/2 + (int)me->query_skill("liumai-shenjian",1) * (int)me->query_skill("jingluo-xue", 1) / 350;
               
                damage += pp/2;
      

       

       // 第一招
        ap = me->query_skill("liumai-shenjian",1)+ me->query_skill("jingluo-xue", 1) + pp/4;
        dp = target->query_skill("parry",1) + target->query_skill("jingluo-xue", 1);

	    msg += HIM "$N" HIM "双手拇指同时捺出，嗤嗤两声急响，「"+ HIY "少商剑"+ HIM "」有如石破天惊、风雨大至。\n" NOR ; 
       
        if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           HIR "$n" HIR "奋力抵挡，却哪里招架得住，被$N"
                                           HIR "这一指戳得鲜血迸流！\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "使出浑身解数，终于将$N"
                       CYN "这一指架开，丝毫无损。\n" NOR;
        }

        // 第二招
	 ap = me->query_skill("liumai-shenjian",1)+ me->query_skill("jingluo-xue", 1) + pp/4;
        dp = target->query_skill("parry",1)+ target->query_skill("jingluo-xue", 1);

	    msg += HIY "接着" HIY "$N" HIY "拇指一屈，食指随即点出，嗤嗤两声急响，变成商阳剑法，「" HIR "商阳剑" HIY "」激射刺出。\n"NOR; 
       
        if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           HIR "$n" HIR "试图抵挡，只听哧的一声，"
                                           HIR "无形剑气已破体而入，透体而出！\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "使出浑身解数，终于将$N"
                       CYN "这一指躲开，丝毫无损。\n" NOR;
        }

        //// 第三招
        ap = me->query_skill("liumai-shenjian",1)+ me->query_skill("jingluo-xue", 1) + pp/4;
        dp = target->query_skill("dodge",1)+target->query_skill("jingluo-xue", 1);

	    msg += HIG "只见" HIG "$N" HIG "右手中指一竖，「" HIC "中冲剑" HIG "」向前刺出。真气鼓荡，嗤然声响，无形剑气直指$n。 \n"NOR; 
       
        if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           HIR "$n" HIR "一愣，只听哧啦的一声，"
                                           HIR "已被剑气划得鲜血飞溅！\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "使出浑身解数，终于将$N"
                       CYN "这一指架开，丝毫无损。\n" NOR;
        }

        //// 第四招
	 ap = me->query_skill("liumai-shenjian",1)+ me->query_skill("jingluo-xue", 1) + pp/4;
        dp = target->query_skill("dodge",1)+target->query_skill("jingluo-xue", 1);

	    msg += HIC "$N" HIC "无名指轻轻一挥，「嗤啦」一声，拙滞古朴的「" MAG "关冲剑" HIC "」剑气向" HIC"$n" HIC"直射而出。\n"NOR; 
       
		 if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           HIR "$n" HIR "躲闪不及，被戳了碗口大个血窟窿，"
                                           HIR "鲜血喷涌而出！\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "左闪右跳，终于将$N"
                       CYN "这一指避开，丝毫无损。\n" NOR;
        }
      

        //// 第五招
	 ap = me->query_skill("liumai-shenjian",1)+ me->query_skill("jingluo-xue", 1) + pp/5;
        dp = target->query_skill("force",1)+target->query_skill("jingluo-xue", 1);

	    msg += HIB "忽见$N" HIB "左手小指一伸，一条气流从少冲穴中激射而出，一股「" HIW "少泽剑" HIB "」登时射向$n。\n"NOR; 
       
		 if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "$n" HIR "运气抵挡，只觉得一股透体凉意"
                                           "袭了上来，一个激凌，丹田立刻变得空空荡荡！\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "运气抵挡，硬生生接下了$N"
                       CYN "这一指。\n" NOR;
        }
		//// 第六招
        ap = me->query_skill("liumai-shenjian",1)+ me->query_skill("jingluo-xue", 1) + pp/5;
        dp = target->query_skill("force",1)+target->query_skill("jingluo-xue", 1);

	    msg += HIW "最后"HIW "$N" HIW"右手小指一挥，一招「" HIG "少冲剑" HIW "」点点刺刺破空刺出，宛如雕花刺画一般。\n"NOR; 
       
		 if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "$n" HIR "已然放弃抵抗，任凭气流摧袭"
                                           "只盼望一切早点结束....\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "运气抵挡，终于接下了$N"
                       CYN "这一指，已是狼狈不堪。\n" NOR;
        }              


     if ((int)target->query("qi")> 0&& me->is_fighting(target) && (int)me->query_skill("liumai-shenjian", 1) > 799 && !userp(target))
        	 {
                  ap = me->query_skill("liumai-shenjian",1)+ me->query_skill("jingluo-xue", 1) + pp/2;
                  dp = target->query_skill("force",1)+target->query_skill("jingluo-xue", 1);
                  aa = me->query_skill("kurong-changong",1);
                  ab = me->query_skill("kurong-changong",1);
                  ac = me->query_skill("kurong-changong",1);

        msg += HIC "\n$N" HIC "一阵狂攻，劲势已灭之际，又生新力，再续杀机。\n"
               HIM "$N" HIM "顿觉六脉剑谱已涌上心头，此起彼伏、连绵不绝，霎时剑气如奔，连绵无尽的万道剑气豁然而出。\n"
               HIY"这正是六脉神剑最强绝技「六脉纵横」,无数迅雷疾风相互冲撞激之际，\n"
               HIW"竟然汇集成一束凌厉无匹的剑柱，宛如一条白色巨蟒,闪电般疾射向$n！！！\n" NOR;
       
		 if (ap * 3 / 4 + random(ap) > dp)
                {
                damage = (int)me->query_skill("finger", 1)/2 + (int)me->query_skill("liumai-shenjian", 1) + (int)me->query_skill("jingluo-xue", 1)*5;               
                damage += pp;
                damage += aa*2;
                damage += ab*2;
                damage += ac*5;
                damage = damage + random(damage);
                target->receive_damage("qi", damage*2, me);
                target->receive_wound("qi", damage, me);
                msg += HIR "$n" HIR "避无可避，只有任凭气流摧袭。。。。。。\n" NOR;
	        	str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	        	msg += "($n"+str+")\n";
                if (objectp(weapon = target->query_temp("weapon"))
                   && weapon->query("stable", 1) < 100
                   && ap + random(ap) > dp)
                  {
                        wp = weapon->name();
                        msg += HIW "只听“锵”的一声脆响，$n" HIW "手"
                               "中的" + wp + HIW "在$N" HIW "内力激荡"
                               "下应声而碎，脱手跌落在地上。\n" NOR;
                        me->add("neili", -150);
                        weapon->set("consistence", 0);
                        weapon->move(environment(target));
                 }

                } 
                 else
                      {
                msg += CYN "$n" CYN "运气抵挡，终于接下了$N"
                       CYN "这一指，已是狼狈不堪。\n" NOR;
                      }  
           }   

	    message_combatd(msg, me, target);
	    me->add("neili", -1800);
        me->start_busy(2 + random(4));

        return 1;
}

