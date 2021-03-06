//目前设定为非转世的专用技能，为了平衡增加了配合内力和精力上限的效果
inherit SKILL;

mapping *action = ({
([      "action": "$N使一式「人间道」，手中$w嗡嗡微振，幻成一条疾光刺向$n的$l",
        "force" : 190,
        "attack": 130,
        "dodge" : 110,
        "parry" : 115,
        "damage": 115,
        "lvl"   : 0,
        "skill_name" : "人间道",
        "damage_type": "刺伤"
]),
([      "action": "$N错步上前，使出「畜生道」，剑意若有若无，$w淡淡地向$n的$l挥去",
        "force" : 240,
        "attack": 150,
        "dodge" : 115,
        "parry" : 125,
        "damage": 130,
        "lvl"   : 40,
        "skill_name" : "畜生道",
        "damage_type": "割伤"
]),
([      "action": "$N一式「饿鬼道」，纵身飘开数尺，运发剑气，手中$w遥摇指向$n的$l",
        "force" : 260,
        "attack": 160,
        "dodge" : 125,
        "parry" : 128,
        "damage": 140,
        "lvl"   : 80,
        "skill_name" : "饿鬼道",
        "damage_type": "割伤"
]),
([      "action": "$N纵身轻轻跃起，一式「修罗道」，剑光如轮疾转，霍霍斩向$n的$l",
        "force" : 280,
        "attack": 170,
        "dodge" : 120,
        "parry" : 135,
        "damage": 155,
        "lvl"   : 120,
        "skill_name" : "修罗道",
        "damage_type": "割伤"
]),
([      "action": "$N手中$w中宫直进，一式「地狱道」，无声无息地对准$n的$l刺出一剑",
        "force" : 320,
        "attack": 180,
        "dodge" : 125,
        "parry" : 142,
        "damage": 160,
        "lvl"   : 160,
        "skill_name" : "地狱道",
        "damage_type": "刺伤"
]),
([      "action": "$N手中$w斜指苍天，剑芒吞吐，一式「天极道」，对准$n的$l斜斜击出",
        "force" : 360,
        "attack": 185,
        "dodge" : 125,
        "parry" : 151,
        "damage": 170,
        "lvl"   : 200,
        "skill_name" : "天极道",
        "damage_type": "刺伤"
]),
([      "action": "$N左指凌空虚点，右手$w逼出丈许雪亮剑芒，一式「六道轮回」翻转向$n",
        "force" : 390,
        "attack": 190,
        "dodge" : 130,
        "parry" : 159,
        "damage": 175,
        "lvl"   : 240,
        "skill_name" : "六道轮回",
        "damage_type": "刺伤"
]),
});

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 5000)
                return notify_fail("你的内力修为不够，难以修炼释迦轮回剑。\n");

        if ((int)me->query_skill("force") < 350)
                return notify_fail("你的内功火候太浅，难以修炼释迦轮回剑。\n");

        if ((int)me->query_skill("sword", 1) < 250)
                return notify_fail("你的剑法根基不足，难以修炼释迦轮回剑。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("lunhui-jian", 1))
                return notify_fail("你的基本剑法水平有限，无法领会更高深的释迦轮回剑。\n");

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
        level = (int) me->query_skill("lunhui-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;
	int cost;

        if (me->query_skill("lunhui-jian", 1) > 100
	   && me->query("family/family_name") != "少林派")
                return notify_fail("没有达摩的指点，你不敢轻易锻炼轮回剑。\n");

	if (me->query_skill("lunhui-jian", 1) < 700)

	if (! me->query("can_perform/lunhui-jian/tiandao") && me->query_skill("lunhui-jian", 1) > 700)
		return notify_fail("你还没有悟透天极道，无法继续锻炼轮回剑。\n");
	if (! me->query("can_perform/lunhui-jian/rendao") && me->query_skill("lunhui-jian", 1) > 600)
		return notify_fail("你还没有悟透人间道，无法继续锻炼轮回剑。\n");
	if (! me->query("can_perform/lunhui-jian/xiuluodao") && me->query_skill("lunhui-jian", 1) > 500)
		return notify_fail("你还没有悟透修罗道，无法继续锻炼轮回剑。\n");
	if (! me->query("can_perform/lunhui-jian/eguidao") && me->query_skill("lunhui-jian", 1) > 400)
		return notify_fail("你还没有悟透恶鬼道，无法继续锻炼轮回剑。\n");
	if (! me->query("can_perform/lunhui-jian/diyudao") && me->query_skill("lunhui-jian", 1) > 300)
		return notify_fail("你还没有悟透地狱道，无法继续锻炼轮回剑。\n");
	if (! me->query("can_perform/lunhui-jian/chushengdao") && me->query_skill("lunhui-jian", 1) > 200)
		return notify_fail("你还没有悟透畜生道，无法继续锻炼轮回剑。\n");


        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

	cost = 200 + random(me->query_skill("lunhui-jian", 1) / 5);

	if( (int)me->query("jing") < cost)
		return notify_fail("你的精神无法集中了，休息一下再练吧。\n");

	if ((int)me->query("qi") < cost * 2)
		return notify_fail("你的体力不够练释迦轮回剑。\n");

	if ((int)me->query("neili") < cost * 2)
		return notify_fail("你的内力不够练释迦轮回剑。\n");

	me->receive_damage("jing", cost);
        me->receive_damage("qi", cost * 2);
        me->add("neili", - cost * 2);
        return 1;
}

int difficult_level(object me)
{
        string fam;
    
        me = this_player();

        fam = me->query("family/family_name");

        if (me->query("class") == "bonze"
           && fam == "少林派")
                return 300;
        else
                return 500;
}

string perform_action_file(string action)
{
        object me = this_player();
        if (me->query("family/family_name") != "少林派"	|| me->query("reborn"))
                return 0;

        return __DIR__"lunhui-jian/" + action;
}
