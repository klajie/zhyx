#include <ansi.h>
#include <combat.h>

#define JING "「" HIY "白虎劲" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object anqi;
        int damage;
        string msg;
        int ap, dp, att;

        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/baihu-jing/jing"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(PO "只能在战斗中对对手使用。\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail(PO "只能空手施展。\n");

        if (! objectp(anqi = me->query_temp("handing"))
           || (string)anqi->query("skill_type") != "throwing")
                return notify_fail("你现在手中并没有拿着暗器。\n");

        if (anqi->query_amount() < 5) 
                return notify_fail("你现在手中暗器不够, 无法发出白虎劲。\n");
     
        if (me->query_skill_mapped("throwing") != "baihu-jing") 
                return notify_fail("你没有激发白虎劲，难以施展" PO "。\n");

        if ((int)me->query_skill("baihu-jing", 1) < 10)
                return notify_fail("你的白虎劲不够强劲，难以施展" PO "。\n");

        if ((int)me->query_skill("force") < 15)
                return notify_fail("你的内功火候不够，难以施展" PO "。\n");

        if ((int)me->query("neili") < 150)
                return notify_fail("你现在真气不足，难以施展" PO "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "突然只听$N" HIY "喝道：“$n" HIY "吃我一记白虎劲！”"
              "说完右手连闪5下，袖底顿时窜出五道白光，分五路向$n" HIY
              "直罩而去！\n" NOR;

        ap = me->query_str() * 5 + 
             me->query_skill("throwing", 1) +
             me->query_skill("unarmed", 1);

        dp = target->query_str() * 5 + 
             target->query_skill("unarmed");

        att = ((int)me->query_skill("baihu-jing", 1);

        damage = int( ap / 15 );

        me->start_busy(3);

        me->add("neili", -150);

        if (anqi->query_amount() > 5) anqi->add_amount(-5);

        if (ap / 2 + random(ap) > dp)
        { 
                if ( att < 100) 
                     { msg += HIW + "！$n见状连忙闪避，轻松闪过四发" + anqi->name() + HIW ","
                              HIW + "哪知白虎之势竟是四虚一实，$n不及闪避，被最后一发打了个正中，"
                                    "惨叫一声，血流如注。\n" NOR;
                        damage += 5;
                      }
 
                if ( att > 100 && att < 120 ) 
                      { msg += HIW + "！$n见状连忙闪避，眼看已闪过三发" + anqi->name() + HIW ","
                              HIW + "哪知白虎之势竟是三虚两实，$n不及闪避，被最后两发打了个正中，"
                                    "冒出两个血洞。\n" NOR;
                        damage += 10;
                       }
  
                if ( att > 120 && att < 140 ) 
                      { msg += HIW + "！$n见状连忙闪避，险险闪过两发" + anqi->name() + HIW ","
                               HIW + "哪知白虎之势竟是两虚三实，$n不及闪避，连中三记，"
                                    "攒出三朵血花。\n" NOR;
                            damage += 15;
                       }

                if ( att > 140 && att < 160 ) 
                      { msg += HIW + "！$n见状连忙闪避，勉强已闪过第一发" + anqi->name() + HIW ","
                              HIW + "哪知白虎之势竟是一虚四实，$n不及闪避，被后面四发侯个正着，"
                                    "口中喷出一口鲜血。\n" NOR;
                            damage += 20;
                       }


                if ( att > 160 && att < 180 ) 
                       { msg += HIW + "！$n已看不见来势，被五发" + anqi->name() + HIW "连环击中,"
                              HIW + "顿时血肉横飞。\n" NOR;
                            damage += 25;
                       }

                if ( att > 180 ) 
                       {msg += HIW + "只见五发" + anqi->name() + HIW "劲力奇大，竟现出白虎之型"
                              HIW + "$n惊得目瞪口呆，被" + anqi->name() + HIW "当胸穿过。\n" NOR;
                            damage += 30;
                       }

                 target->receive_damage("qi", damage, me);
                                              
        } else
        {
                msg += HIY "可是$p" HIY "看破了$P" HIY "的招式，身形"
                       "连闪，已脱出寒光笼罩的范围。\n" NOR;
                damage = 10;
        }
        
               message_combatd(msg, me, target);

        if ( att < 180 )
        {      tell_object(me, HIY "你对「白虎劲」有了新的体会。\n" NOR);
               me->improve_skill("baihu-jing", random(damage + me->query_str()));
        } 

        return 1;
}