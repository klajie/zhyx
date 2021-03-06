#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>


inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon,ob;
        int skill;
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「忘情诀」只能在战斗中使用。\n");

        if (!objectp(weapon = me->query_temp("weapon"))
                || (string)weapon->query("skill_type") != "sword")
                return notify_fail("「忘情诀」必须用剑才能施展。\n");

        if( (int)me->query_skill("wangqing-jian", 1) < 120 )
                return notify_fail("你的「忘情剑法」不够娴熟，不会使用「忘情诀」。\n");

        if( (int)me->query("neili") < 5000  ) 
                return notify_fail("你的内力不够。\n");

        skill = me->query_skill("wangqing-jian");

        msg = HIG "$N身行突变，使出忘情剑法的终级技能"HIR"忘情诀!\n"NOR;

        message_vision(msg, me, target);

        me->add("neili", -300);

        me->clean_up_enemy();
        ob = me->select_opponent();

        msg = RED"忘"HIR"情天河！\n"NOR;
        message_vision(msg, me, target);
        COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 1);
        msg = RED"情"HIY"流成河！\n"NOR;
        message_vision(msg, me, target);
        COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 1);
        msg = RED"天"HIG"冻冰川！\n"NOR;
        message_vision(msg, me, target);
        COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 1);
        msg = RED"书"HIB"满江红！\n"NOR;
        message_vision(msg, me, target);
        COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 1);


        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}


