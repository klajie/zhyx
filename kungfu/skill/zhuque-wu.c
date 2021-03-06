#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action":"$N功运脚底，如翩翩起舞之凤凰" ]),
});
mapping query_action(object me, object weapon)
{
        return action[0];
}

string *dodge_msg = ({
        "$n功运脚底，如翩翩起舞之凤凰，与$P保持适当距离，令其欲攻无从。\n"
});

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

string main_skill() { return "sixiang-shengong"; }

int valid_learn(object me)
{
        object ob;
  
        if ((int)me->query_skill("sixiang-shengong", 1))
                return notify_fail("你已将这种劲力融入四象神功，不必再分开练习了。\n");
        
        if (me->query("dex") < 30)
                return notify_fail("你的先天身法不足，无法领会朱雀舞。\n");

        if (me->query_skill("throwing", 1) < 10)
                return notify_fail("你的暗器技能不够娴熟。\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("zhuque-wu", 1))
                return notify_fail("你的基本暗器水平有限，难以体会更精妙的朱雀舞。\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("zhuque-wu", 1))
                return notify_fail("你的基本拳脚水平有限，难以爆发更强劲的朱雀舞。\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "dodge";
}

int practice_skill(object me)
{
	return notify_fail("朱雀舞只能通过参悟朱雀卷来提高。\n");
}