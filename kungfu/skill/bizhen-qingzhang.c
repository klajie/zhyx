#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N身形急晃，一跃而至$n跟前，右掌带着切骨之劲砍向$n的$l",
        "force" : 300,
        "attack": 100,
        "dodge" : 80,
        "parry" : 80,
        "damage": 140,
        "lvl"   : 0,
        "damage_type" : "割伤"
]),
([      "action" : "$N飞身跃起，双掌至上而下斜砍而出，顿时万千道掌寒劲从四面八方席卷$n",
        "force" : 350,
        "attack": 150,
        "dodge" : 100,
        "parry" : 100,
        "damage": 150,
        "lvl"   : 50,
        "damage_type" : "割伤"
]),
([      "action" : "$N平掌为刀，斜斜砍出，幻出一道道刚猛的掌劲如飓风般裹向$n的全身",
        "force" : 400,
        "attack": 180,
        "dodge" : 120,
        "parry" : 120,
        "damage": 160,
        "lvl"   : 100,
        "damage_type" : "割伤"
]),
([      "action" : "$N反转右掌护住全身，身形猛跃至$n面前，力注左掌，横向$n拦腰砍去",
        "force" : 450,
        "attack": 190,
        "dodge" : 130,
        "parry" : 130,
        "damage": 170,
        "lvl"   : 150,
        "damage_type" : "割伤"
]),
([      "action" : "$N右掌后撤，手腕一翻，猛地挥掌砍出，幻出一道无比凌厉的掌劲直斩向$n的$l",
        "force" : 500,
        "attack": 200,
        "dodge" : 140,
        "parry" : 140,
        "damage": 180,
        "lvl"   : 200,
        "damage_type" : "割伤"
]),
([      "action" : "$N双手挥舞出，形成一个大圈，一股劲气澎湃汹涌而来，逼得$n踉踉后退",
        "force" : 550,
        "attack": 220,
        "dodge" : 150,
        "parry" : 150,
        "damage": 200,
        "lvl"   : 250,
        "damage_type" : "割伤"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

int valid_learn(object me)
{
//        if (me->query("character") == "阴险奸诈")
//                return notify_fail("你心中暗想：这武功难练得紧，学它做甚？\n");

        if ((int)me->query("str") < 38)
                return notify_fail("你的先天膂力孱弱，难以修炼碧针清掌。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练碧针清掌必须空手。\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("你的内功火候不够，无法练习碧针清掌。\n");

        if ((int)me->query("max_neili") < 3000)
                return notify_fail("你的内力太弱，无法练习碧针清掌。\n");

        if ((int)me->query_skill("strike", 1) < 180)
                return notify_fail("你的基本掌法火候不够，无法练习碧针清掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("bizhen-qingzhang", 1))
                return notify_fail("你的基本掌法水平有限，无法领会更高深的碧针清掌。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("bizhen-qingzhang",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        int cost;

        if ((int)me->query("str") < 38)
                return notify_fail("你的先天膂力孱弱，难以修炼碧针清掌。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练碧针清掌必须空手。\n");

        if ((int)me->query("qi") < 200)
                return notify_fail("你的体力太低了。\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("你的内力不够练碧针清掌。\n");

        cost = me->query_skill("bizhen-qingzhang", 1) / 2 + 100;

        me->receive_damage("qi", 100);
        me->add("neili", -cost);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;

        lvl = me->query_skill("bizhen-qingzhang", 1);

        if (damage_bonus < 100 || lvl < 150 ) return 0;

        if (random(me->query_skill("force")) > victim->query_skill("force") / 3)
        {
                victim->receive_wound("qi", (damage_bonus - 50) / 2);
                return HIR "只听" + victim->name() +
                       HIR "前胸“喀嚓”一声，竟像是肋骨碎断的声音！\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"bizhen-qingzhang/" + action;
}
