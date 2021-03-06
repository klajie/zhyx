#include <ansi.h>
inherit SKILL;

mapping *action = ({
([	"action" : "$N用"+HIM+"后腿"+NOR+"往$n的$l用力一蹬",
	"force"  : 200,
	"attack" : 200,
	"dodge"  : 100,
	"parry"  : 200,
	"damage" : 100,
	"lvl"    : 0,
	"skill_name" : "蛙鸣三起",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N反转身用"+HIG+"尾巴尖"+NOR+"对准$n的$l一刺",
	"force"  : 210,
	"attack" : 200,
	"dodge"  : 100,
	"parry"  : 200,
	"damage" : 100,
	"lvl"    : 100,
	"skill_name" : "反手点穴",
	"damage_type":	"咬伤",
]),
([	"action" : "$N扑上来"+HIC+"张嘴"+NOR+"往$n的$l狠狠地一咬",
	"force"  : 220,
	"attack" : 200,
	"dodge"  : 100,
	"parry"  : 200,
	"damage" : 100,
	"lvl"    : 200,
	"skill_name" : "前瞻后跳",
	"damage_type":	"咬伤",
]),
([	"action" : "$N用"+HIW+"爪子"+NOR+"往$n的$l一抓",
	"force"  : 230,
	"attack" : 200,
	"dodge"  : 100,
	"parry"  : 200,
	"damage" : 100,
	"lvl"    : 300,
	"skill_name" : "分身无影",
	"damage_type":	"抓伤",
]),
([	"action" : "$N抬起"+HIR+"蹄子"+NOR+"往$n的$l一踹",
	"force"  : 240,
	"attack" : 200,
	"dodge"  : 100,
	"parry"  : 200,
	"damage" : 100,
	"lvl"    : 400,
	"skill_name" : "无敌蛤蟆",
	"damage_type":	"瘀伤",
])
});

int valid_enable(string usage) { return usage=="unarmed" || usage=="parry"; }      
int valid_learn(object me)
{
    return 1;
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
    level = (int)me->query_skill("puyaogedou", 1);
    for(i = sizeof(action); i > 0; i--)
    if(level > action[i-1]["lvl"])
      return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    return 1;
}
string perform_action_file(string action)
{
	return __DIR__"puyaogedou/" + action;
}