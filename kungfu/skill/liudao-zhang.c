// liudao-zhang 六道杖法
// By Alf, Last Update 2001.10

// 阿鼻地狱　饿鬼徘徊　畜生历业　修罗相煎　人界苦短　天相晦明 

inherit SKILL;

mapping *action = ({
([  "action": "$N使出一招「阿鼻地狱」，手中$w大开大阖，直向$n的$l的击去",
        "force" : 100,
        "dodge": -5,
        "damage": 40,
        "lvl" : 10,
        "damage_type": "挫伤"
]),
([      "action": "$N手中$w横扫，带起阵阵风响，一招「饿鬼徘徊」向$n的$l攻去",
        "force" : 110,
        "dodge": -5,
        "damage": 50,
        "lvl" : 20,
        "damage_type": "挫伤"
]),
([      "action": "$N手中$w高举过顶，居高临下使一招「畜生历业」，砸向$n的$l",
        "force" : 120,
        "dodge": -10,
        "damage": 60,
        "lvl" : 30,
        "damage_type": "挫伤"
]),
([      "action": "$N吐气开声，一招「修罗相煎」展开，手中$w挟厉风砸向$n的$l",
        "force" : 130,
        "dodge": -10,
        "damage": 70,
        "lvl" : 40,
        "damage_type": "挫伤"
]),
([      "action": "$N使出「人界苦短」，手中$w去势变幻不定，将$n的$l尽数罩住",
        "force" : 140,
        "dodge": -20,
        "damage": 80,
        "lvl" : 50,
        "damage_type": "挫伤"
]),
([      "action": "$N身形不动，手中$w连挥，一招「天相晦明」，霍霍劈向$n的$l",
        "force" : 150,
        "dodge": -20,
        "damage": 100,
        "lvl" : 60,
        "damage_type": "挫伤"
]),
});

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("liudao-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int valid_enable(string usage) { return (usage == "staff") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 100)
                return notify_fail("你的内力不够。\n");
        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "staff")
                return notify_fail("你使用的武器不对。\n");
        if ((int)me->query("qi") < 50)
                return notify_fail("你的体力不够练六道杖法。\n");
        me->receive_damage("qi", 25);
        return 1;
}

string perform_action_file(string action)
{
    return "/kungfu/skill/liudao-zhang/" + action;
}

