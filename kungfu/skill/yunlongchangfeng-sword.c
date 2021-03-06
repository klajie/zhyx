// yunlongchangfeng-sword.c
// 华夏玩家meng的自创武功：云龙长风剑法
// Modified by smallfish@huaxia Sep.1998
#include <ansi.h>

inherit SKILL;

string is_private_skill() {return "meng";}
int can_not_hubo() {return 1;}

mapping *action = ({
([      "skill_name":    "龙困浅滩",
        "action":  "$N一抹剑身，$w仿佛如盘龙一般直飞天际，顿时天地为之变色，$n只觉眼前一黑，「龙困浅滩」已攻至面前",
        "dodge" : 80,
        "damage": 180,
        "force" : 330,
        "attack": 130,
        "parry" : 80,
        "lvl"   : 0,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "风随云龙",
        "action":  "$n眼前的$N恍如突然消失一般，惊讶之际，$N「风随云龙」已然使出，$w带着一丝风啸只刺$n双眼",
        "dodge" : 80,
        "damage": 180,
        "force" : 330,
        "attack": 130,
        "parry" : 80,
        "lvl"   : 0,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "龙飞在天",
        "action":  "青影重重，$N已经被层层青光包裹，消失原地，片刻之间人却已在半空，一招「龙飞在天」，$w挟著闪闪金光逼向$n",
        "dodge" : 90,
        "damage": 190,
        "force" : 340,
        "attack": 135,
        "parry" : 85,
        "lvl"   : 120,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "云龙探爪",
        "action":  "$N轻旋$w，此刻在$n眼中，$N如梦似幻般看不清楚，犹豫之间，龙爪已扑面而来，正是一招「云龙探爪」",
        "dodge" : 95,
        "damage": 200,
        "force" : 350,
        "attack": 140,
        "parry" : 90,
        "lvl"   : 140,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "龙腾虎涧",
        "action":  "$N双足轻点，顿时便化作层层幻影，一招「龙腾虎涧」，$w如猛虎一般只扑$n",
        "dodge" : 95,
        "damage": 200,
        "force" : 350,
        "attack": 140,
        "parry" : 90,
        "lvl"   : 140,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "龙形百变",
        "action":  "$N缓缓飞升，口中一阵怒吼，一招「龙形百变」，手中$w化成一条腾空的巨龙，冲向$n",
        "dodge" : 105,
        "damage": 210,
        "force" : 360,
        "attack": 145,
        "parry" : 95,
        "lvl"   : 160,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "猛龙腾海",
        "action":  "手中$w暴发出一阵白光，身随剑走，一招「猛龙腾海」，$N如一支离弦的箭，直攻$n的$l",
        "dodge" : 110,
        "damage": 220,
        "force" : 370,
        "attack": 150,
        "parry" : 100,
        "lvl"   : 180,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "龙行万里",
        "action":  "$w绕着$N急速的旋转着，一阵强光闪过，人影顿时消失，又瞬时在$n身边出现，一招「龙行万里」剑身随着$N的意念急向$n攻去",
        "dodge" : 115,
        "damage": 230,
        "force" : 380,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "游龙戏凤",
        "action":  "$n面前突然出现了两个$N，叫人难分真伪，刹那间两个身影同时攻向$n，一招「游龙戏凤」，$w直刺心脏，把$n至于死地",
        "dodge" : 115,
        "damage": 230,
        "force" : 380,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "刺伤"
]),
});

int valid_learn(object me)
{
    object ob;
    if( (int)me->query("max_neili") < 1000 )
        return notify_fail("你的内力不够，没有办法练云龙长风剑法。\n");

    if( (int)me->query_skill("martial-cognize",1) < 300 )
        return notify_fail("你的武学修养不够，没有办法练云龙长风剑法。\n");

    if( !(ob = me->query_temp("weapon"))
    ||      (string)ob->query("skill_type") != "sword" )
        return notify_fail("你必须先找一把剑才能练剑法。\n");

    return 1;
}

int valid_enable(string usage)
{
    return usage=="sword" || usage=="parry";
}

string query_skill_name(int level)
{
    int i;
    for(i = sizeof(action)-1; i >= 0; i--)
        if(level >= action[i]["lvl"])
            return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
    int i, level;
    level   = (int) me->query_skill("yunlongchangfeng-sword",1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 60)
        return notify_fail("你的体力不足以练习云龙长风剑法。\n");

    if ((int)me->query("neili") < 60 )
        return notify_fail("你的内力不够，没有办法练习云龙长风剑法。\n");

    me->receive_damage("qi", 50);
    me->add("neili", -50);

    return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yunlongchangfeng-sword/" + action;
}
