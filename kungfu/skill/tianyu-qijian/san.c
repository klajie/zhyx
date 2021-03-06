// san.c  天女散花

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int damage, sp, dp, i;
        string result, str, msg;

        damage =  (int)me->query_skill("force");
        damage += (int)me->query_skill("sword");

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("「天女散花」只能对战斗中的对手使用。\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");
                
        if( (int)me->query_skill("tianyu-qijian", 1) < 100 )
                return notify_fail("你的天羽奇剑不够娴熟，不会使用。\n");

        if ( me->query_skill_mapped("sword") != "tianyu-qijian")
                return notify_fail("你没有激发天羽奇剑到剑法上！\n"); 

        if ((int)me->query_skill("bahuang-gong", 1)<200)
                return notify_fail("你的八荒六合唯我独尊功火候不够。\n");

        if (me->query_skill_mapped("force") != "bahuang-gong")
                return notify_fail("你没有运用八荒六合唯我独尊功功！\n");       

        if( (int)me->query("neili", 1) < damage + 200 )
                return notify_fail("你现在内力太弱，不能使用「天女散花」。\n");
                        
        message_vision(CYN "\n$N凝神息气，手腕疾抖，挽出千万个剑花，铺天盖地飞向$n。\n"NOR, me,target);

        me->add_temp("apply/attack",damage/10);
        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        me->add_temp("apply/attack",-damage/10);

        if (! me->is_fighting(target) )
        {
                me->add("neili",-100);
                me->start_busy(1 + random(3));
                return 1;
        }

        sp = me->query_skill("sword") + me->query_skill("dodge") + me->query_str() * 10;
        dp = target->query_skill("parry") + target->query_skill("dodge") + target->query_dex() * 10;
        sp += me->query("jiali");
        if( sp/2 + random(sp) > dp || !living(target))
        {
                damage += random(damage/2);
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                me->add("neili",-damage/2);
                message_vision(HIR "\n只见$N剑花聚为一线，穿向$n。\n$n只觉一股热流穿心而过，喉头一甜，鲜血狂喷而出！\n\n" NOR, me,target);

                str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
                message_vision("($N"+str+")\n", target);
                target->start_busy(1+random(2));
                me->start_busy(2);
        } else 
        {
                message_vision(CYN "$n见势不妙猛地向后一跃,跳出了$N的攻击范围。\n"NOR, me,target);
                me->add("neili", -200);
                me->start_busy(4);
        }
        return 1;
}

