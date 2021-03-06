// bizhen-zhang.c 碧针清掌
// By Alf


inherit SKILL;

mapping *action = ({
([    "action" : "$N一式「嶙嶙接空碧」，双掌间升起一团淡淡的青气，缓缓推向$n的$l",
    "force" : 130,
    "dodge" : 20,
    "damage": 10,
    "lvl" : 0,
    "skill_name" : "嶙嶙接空碧",
    "damage_type" : "内伤"
]),
([    "action" : "$N一式「翳翳碎人愁」，身形凝立不动，双掌一高一低，令$n无法躲闪",
    "force" : 150,
    "dodge" : 10,
    "damage": 30,
    "lvl" : 20,
    "skill_name" : "翳翳碎人愁",
    "damage_type" : "内伤"
]),
([    "action" : "$N使一式「摧折任遨游」，左掌微拂，右掌乍伸乍合，猛地插往$n的$l",
    "force" : 150,
    "dodge" : 30,
    "damage": 40,
    "lvl" : 30,
    "skill_name" : "摧折任遨游",
    "damage_type" : "瘀伤"
]),
([    "action" : "$N双掌隐泛青气，一式「万古清如此」，犹如漫天碧绿松针般向$n击去",
    "force" : 250,
    "dodge" : 20,
    "damage": 55,
    "lvl" : 40,
    "skill_name" : "万古清如此",
    "damage_type" : "内伤"
]),
([    "action" : "$N提气上纵，使出一式「天风舟雁唳」，双掌并拢，笔直地插向$n的$l",
    "force" : 300,
    "dodge" : 25,
    "damage": 70,
    "lvl" : 60,
    "skill_name" : "天风舟雁唳",
    "damage_type" : "瘀伤"
]),
([    "action" : "$N身形微晃，一式「三生恨未休」展开，双掌挟萧飒劲气，猛然拍向$n",
    "force" : 350,
    "dodge" : 30,
    "damage": 85,
    "lvl" : 70,
    "skill_name" : "三生恨未休",
    "damage_type" : "内伤"
]),
([    "action" : "$N左掌凝重，右掌轻盈，使出一式「暮景月空流」，同时向$n的$l击去",
    "force" : 350,
    "dodge" : 30,
    "damage": 100,
    "lvl" : 80,
    "skill_name" : "暮景月空流",
    "damage_type" : "瘀伤"
]),
([    "action" : "$N突地一招「荆棘毁前路」，双掌阴阳变幻不定，一前一后的朝$n劈去",
    "force" : 450,
    "dodge" : 30,
    "damage": 120,
    "lvl" : 100,
    "skill_name" : "荆棘毁前路",
    "damage_type" : "内伤"
]),
});

int valid_enable(string usage) { return usage=="unarmed" || usage=="parry"; }

int valid_learn(object me)
{
    if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
        return notify_fail("练碧针清掌必须空手。\n");
//    if ((int)me->query_skill("zixia-shengong", 1) < 20)
//        return notify_fail("你的紫霞神功火候不够，无法学碧针清掌。\n");
    if ((int)me->query("max_neili") < 100)
        return notify_fail("你的内力太弱，无法练碧针清掌。\n");
    return 1;
}

mapping query_action(object me, object weapon)
{
    int i, level;
    level = (int) me->query_skill("bizhen-zhang",1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 30)
        return notify_fail("你的体力太低了。\n");
    if ((int)me->query("neili") < 40)
        return notify_fail("你的内力不够练碧针清掌。\n");
    me->receive_damage("qi", 25);
    me->add("neili", -10);
    return 1;
}

string perform_action_file(string action)
{
    return __DIR__"bizhen-zhang/" + action;
}


