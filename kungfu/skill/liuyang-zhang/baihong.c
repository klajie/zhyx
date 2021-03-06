
// baihong.c 「白虹掌力」updated by Kasumi
#include <ansi.h>
inherit F_CLEAN_UP;
inherit F_SSERVER;

void remove_effect(object me, int amount);

int perform(object me)
{       
        int skill;
        string msg;

        if ((int)me->query_skill("liuyang-zhang", 1) < 300)
                return notify_fail("你的天山六阳掌不够娴熟，不会使用「白虹掌力」。\n");

        if ((int)me->query("neili") < 400 )
                return notify_fail("你的真气不够，无法使用「白虹掌力」。\n");

        if ((int)me->query_temp("lingjiu/baihong"))
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("liuyang-zhang", 1)/2;

        msg = HIW "\n$N左掌拍出，右掌一带，左掌之力吞吐不定。这门功夫乃是逍遥派上乘掌法中\n"
                  "的"+ HIW +"‘白虹掌力’，此刻$N掌力曲直如意，当真了得！\n" NOR;
        message_combatd(msg, me);

        me->add_temp("apply/strike", skill);     
        me->set_temp("lingjiu/baihong", 1);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill :), skill);

        me->add("neili", -100);
        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("lingjiu/baihong"))
        {
                me->add_temp("apply/strike", -amount);
                me->delete_temp("lingjiu/baihong");
                message_combatd(WHT "\n$N左掌一挥，右掌在前胸画了个弧，收起了吞吐不定的掌力。\n"NOR, me);
        }
}
