#include <ansi.h>

inherit SKILL;
mapping *action = ({
([      "action":"$N吐气扬声，混身气劲爆发，凭玄武真气在周身运转" ]),
});

mapping query_action(object me, object weapon)
{
        return action[0];
}

string *parry_msg = ({
        "$n吐气扬声，混身气劲爆发，凭玄武真气守得水泄不通，$P一时无法下手。\n",
      });

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

string main_skill() { return "sixiang-shengong"; }

int valid_learn(object me)
{
        object ob;
  
        if ((int)me->query_skill("sixiang-shengong", 1))
                return notify_fail("你已将这种劲力融入四象神功，不必再分开练习了。\n");
        
        if (me->query("con") < 30)
                return notify_fail("你的先天根骨不足，无法领会玄武式。\n");

        if (me->query_skill("throwing", 1) < 10)
                return notify_fail("你的暗器技能不够娴熟。\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("xuanwu-shi", 1))
                return notify_fail("你的基本暗器水平有限，难以体会更精妙的玄武式。\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("xuanwu-shi", 1))
                return notify_fail("你的基本拳脚水平有限，难以爆发更强劲的玄武式。\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "parry";
}

int practice_skill(object me)
{
	return notify_fail("玄武式只能通过参悟玄武卷来提高。\n");
}

string perform_action_file(string action)
{
        return __DIR__"xuanwu-shi/" + action;
}
