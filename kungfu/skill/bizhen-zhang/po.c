// po.c 碧针清掌绝招：凝碧破
// By Alf

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
    object weapon;
    int damage, dp;
    string msg;

    if( !target ) target = offensive_target(me);

    if( !target || !target->is_character() || !me->is_fighting(target) )
        return notify_fail("凝碧破只能对战斗中的对手使用。\n");

    if( (int)me->query_skill("bizhen-zhang", 1) < 100 )
        return notify_fail("你的碧针清掌不够娴熟，不会使用凝碧破。\n");

//    if( (int)me->query_skill("zixia-shengong", 1) < 80 )
//        return notify_fail("你的紫霞神功等级不够，无法使出凝碧破。\n");

    if( (int)me->query("neili", 1) < 300 )
        return notify_fail("你现在内力太弱，强使凝碧破有损无益！\n");

    msg = HIG "$N双掌盘旋翻飞，幻化作一团绿影，突然间掌力疾吐，分袭$n各处要害！\n"NOR;

    if (living(target))
           dp = target->query_skill("force")/2;
    else    dp = 0;

    if (random(me->query_skill("force")) > dp )
    {
        me->start_busy(1);

        damage = (int)me->query_skill("bizhen-zhang", 1) + (int)me->query_skill("force",1);
        damage = damage/2 + random(damage/2) ;

        target->receive_damage("qi", damage);
        target->start_busy(4);
        me->add("neili", -300);

        msg += HIR"$n只觉全身大穴宛遭针刺，喉头一甜，口中鲜血如雨般喷出！\n"NOR;

    }

    else
    {
        me->start_busy(3);
        msg += CYN"$n见势不妙，连忙着地一滚，狼狈万状的避了开去。\n"NOR;
    }
    message_combatd(msg, me, target);

        if(!target->is_fighting(me)) target->fight_ob(me);
        if(userp(target)) target->fight_ob(me);
        else if( !target->is_killing(me) ) target->kill_ob(me);
    return 1;
}


