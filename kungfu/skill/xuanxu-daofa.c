// by Lonely

inherit SKILL;

string *action_msg = ({
        "$N刀锋斜引，身体跃起丈许,一招「劈风展翅」，手中的$w向$n的$l横劈过去",
        "$N一招「风拂山岗」，手中$w向$n的下盘划去，招未使老，忽又直挑$n的$l",
        "$N一招「拨云见日」，手中的$w向$n虚砍一刀，刀刃忽又转向$n的$l砍去",
        "$N身随刀进，青光闪跃，一招「苍鹰望月」，直攻$n右肩，半徒刀锋兜了个半圆，方向突变,斜劈$n的$l",
        "$N陡然身行飞起，一招「满天飞雪」，手中的$w舞出万道寒光，向$n的$l掠去",
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }


int valid_learn(object me)
{
       if ((int)me->query("max_neili") < 50)
               return notify_fail("你的内力不够练习玄虚刀法。\n");
       if ((int)me->query_skill("taiji-shengong", 1) < 10)
               return notify_fail("你的太极神功火候太浅。\n");
       return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 120 + random(30),
                "attack": 60 + random(10),
                "dodge" : 60 + random(10),
                "parry" : 60 + random(10),
                "damage_type" : "割伤",
        ]);
}

int practice_skill(object me)
{
       object weapon;

       if (!objectp(weapon = me->query_temp("weapon"))
       || (string)weapon->query("skill_type") != "blade")
               return notify_fail("你使用的武器不对。\n");
       if ((int)me->query("qi") < 20)
               return notify_fail("你的体力不够练玄虚刀法。\n");
       me->receive_damage("qi", 20);
       return 1;
}
string perform_action_file(string action)
{
        return __DIR__"xuanxu-daofa/" + action;
}

