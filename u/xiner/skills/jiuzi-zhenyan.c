//jiuzi-zhenyan.c九字真言(徐子陵)参照DTSL更新
//转世SK，威力较强，略低于天子剑
//update by xiner 2009-02-16

#include <ansi.h>

inherit SKILL;

string *parry_msg = ({
	"$n手掌变换无常，以守代攻地架开了$N的进攻。\n",
	"$n微微一笑，手掌一挥，$N的进攻已经被冰消瓦解！\n",
	"$n手掌一挥，随后闪开，寻找着进攻的机会。\N",
	"$n手掌不住变换，虽是简单的招式，却封住了$N的全部进攻之力！\n",
});

mapping *action = ({
([      "action": "$N不见半点情绪表情的波动，仿如入静的高僧，暗施出“不动根本印”，一股气劲自周身弥散开来。\n",
        "force"    : 500,
        "attack"   : 180,
        "dodge"    : 100,
        "parry"    : 100,
        "damage"   : 300,
        "weapon"   : HIW "不动根本印" NOR,
        "damage_type" : "内伤",
]),
([      "action": "$N手捏大金刚轮印，脸上红光闪现，只见一股热浪朝$n涌去！",
        "force"    : 450,
        "attack"   : 190,
        "dodge"    : 110,
        "parry"    : 110,
        "damage"   : 310,
        "weapon"   : HIW "大金刚轮印" NOR,
        "damage_type" : "内伤",
]),
([	"action": "$N一无所惧，长笑一声，倏又往右闪去，左手拍向$n，同时右手暗捏狮子印，沉喝一声“咄”！",
        "force"    : 500,
        "attack"   : 200,
        "dodge"    : 120,
        "parry"    : 120,
        "damage"   : 310,
        "weapon"   : HIW "外狮子印" NOR,
        "damage_type" : "内伤",
]),
([	"action": "$N右手暗捏内狮子印，左手一挥，只见一股气墙朝$n的拍去！",
        "force"    : 550,
        "attack"   : 200,
        "dodge"    : 110,
        "parry"    : 110,
        "damage"   : 320,
        "weapon"   : HIW "内狮子印" NOR,
        "damage_type" : "内伤",
]),
([      "action": "$N由内缚印改为外缚印，拇指改置外侧，劲气疾吐，$n登时应印而加速横翻过去！",
        "force"    : 500,
        "attack"   : 180,
        "dodge"    : 120,
        "parry"    : 120,
        "damage"   : 320,
        "weapon"   : HIW "外缚印" NOR,
        "damage_type" : "内伤",
]),
([      "action": "$N内缚印体内脉道真气交替，早严阵以待的真气汹涌的侵入$n体内经脉！",
        "force"    : 550,
        "attack"   : 180,
        "dodge"    : 120,
        "parry"    : 120,
        "damage"   : 330,
        "weapon"   : HIW "内缚印" NOR,
        "damage_type" : "内伤",
]),
([      "action": "$N按捏智拳印，突然拳法突变，宛如漫天流星，朝$n周身要害打去！",
        "force"    : 450,
        "attack"   : 200,
        "dodge"    : 130,
        "parry"    : 130,
        "damage"   : 330,
        "weapon"   : HIW "智拳印" NOR,
        "damage_type" : "内伤",
]),
([      "action": "$N按捏日轮印，手掌交错之间，四周已是热浪翻滚，几阵内劲朝$n涌去！",
        "force"    : 450,
        "attack"   : 200,
        "dodge"    : 150,
        "parry"    : 150,
        "damage"   : 340,
        "weapon"   : HIW "日轮印" NOR,
        "damage_type" : "内伤",
]),
([      "action": "$N按捏宝瓶印，宝瓶气拳劲再非高度集中的一团，而是像一堵墙般直朝$n压过去！",
        "force"    : 500,
        "attack"   : 200,
        "dodge"    : 120,
        "parry"    : 120,
        "damage"   : 350,
        "weapon"   : HIW "不动宝瓶印" NOR,
        "damage_type" : "内伤",
]),
});


string main_skill() { return "jiuzi-zhenyan"; }

mapping sub_skills = ([
        "shou-yin"	: 300,        // 1
        "fengyun-shou"	: 200,        // 2
        "qianye-shou"	: 200,        // 3
        "longzhua-gong"	: 200,        // 4
        "yingzhua-gong"	: 200,        // 5
        "nianhua-zhi"	: 200,        // 6
        "wuxiang-zhi"	: 200,        // 7
        "luohan-quan"	: 200,        // 8
        "changquan"	: 300,        // 9
]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        object ob;

        if (me->query("gender") == "无性")
        {
                tell_object(me, "你演练完毕，只感气血上涌，看来自己阴阳不调"
                                "，无法学此奇功。\n" NOR);
                return 0;
        }

        if (me->query("int") < 35)
        {
                tell_object(me, "你演练完毕，只感九种武功毫无牵连，看来"
                                "依你的悟性，无法将其合一。\n");
                return 0;
        }

        if (me->query("con") < 35)
        {
                tell_object(me, "你演练完毕，发现自己的先天根骨太差，无法演练"
                                "九字真言。\n");
                return 0;
        }

        if (me->query("str") < 35)
        {
                tell_object(me, "你演练完毕，只觉手臂又酸又软，看来无法将九种"
                                "技能合一。\n");
                return 0;
        }

        if (me->query("dex") < 35)
        {
                tell_object(me, "你演练完毕，只觉自己的身法灵动性太差，无法贯通"
                                "九字真言。\n");
                return 0;
        }

        if (me->query_skill("literate", 1) < 300)
        {
                tell_object(me, "你觉得九字真言极其深奥，看来多研究一下学问可能更有帮"
                                "助。\n");
                return 0;
        }

        if (me->query_skill("lamaism", 1) < 300)
        {
                tell_object(me, "你演练完毕，发现如果通晓密宗心法应该更有帮助。\n");
                return 0;
        }

        if (me->query_skill("buddhism", 1) < 300)
        {
                tell_object(me, "你演练完毕，发现如果通晓禅宗心法应该更有帮助。\n");
                return 0;
        }

        if (me->query_skill("force", 1) < 450)
        {
                tell_object(me, "你觉得自己基本内功修为太浅，看来暂且无法演练"
                                "九字真言。\n");
                return 0;
        }

        if (me->query_skill("martial-cognize", 1) < 300)
        {
                tell_object(me, "你演练完毕，发现自己的武学修养尚待提高，暂"
                                "且无法将九字真言演练合一。\n");
                return 0;
        }

        if ((int)me->query_skill("hand", 1) < 300)
        {
                tell_object(me, "你觉得自己的基本手法还有待提高，暂且无法贯通九"
                                "字真言。\n");
                return 0;
        }



        if ((int)me->query("max_neili") < 6000)
        {
                tell_object(me, "你演练完毕，丹田提不起半点力来，看来应该"
                                "继续锻炼内力。\n");
                return 0;
        }

        if (random(30) <= 28)
        {
                tell_object(me, "你对九字真言的奥妙颇有领悟，或许再演练几次"
                                "就能融会贯通。\n");
                return 0;
        }

        tell_object(me, HIW "一阵凡尘往事涌上心头，你几欲放声长叹。霎那间，"
                        "你放眼回首，竟有一股莫名\n的悲哀。宗师泰斗那种高出"
                        "不胜寒、登泰山而小天下之感犹然而生，你只觉得以\n往"
                        "的武学现在看来是多么的渺小可笑。\n" NOR);
        return 1;
}

int double_attack() { return 1; }

int valid_enable(string usage) { return usage == "hand" || usage == "parry"; }

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("jiuzi-zhenyan",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

/*
mixed valid_damage(object ob, object me, int damage, object weapon)
{}
*/

mixed hit_ob(object me, object victim, int damage_bonus)
{
	int lvl = me->query_skill("jinshe-jian", 1);

        if (damage_bonus < 100) return 0;

	switch(random(3))
	{
           case 0:
             if (damage_bonus / 4 > victim->query_str() &&
                 ! me->is_busy() &&
                 ! victim->is_busy())
		{
                 message_sort( HIY "$N" HIY "手掌变换无常，仿佛西方如来佛祖亲临，"
			       "将$n" HIY "牢牢围住动弹不得！\n" NOR,me,victim);
                 me->start_busy(1);
                 victim->start_busy(1 + random(lvl / 10));
	        }
		break;

           default :
	        if (damage_bonus / 4 > victim->query_str())
	        {
        	        victim->receive_wound("qi", (damage_bonus - 140) / 2);
                	victim->add("neili", -((damage_bonus - random(90)) / 2), me);
	                return HIR "$N" HIR "突然连出数掌，$n" HIR "只感觉眼前"HIW"佛影"HIR"不断，"
        	                    "登时连中数掌，吐血不止！\n" NOR;
	        }
	}
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练九字真言必须空手。\n");

        if ((int)me->query("int") < 35)
                return notify_fail("你的先天悟性太低，无法领会九字真言。\n");

        if ((int)me->query("dex") < 35)
                return notify_fail("你的先天身法孱弱，无法修炼九字真言。\n");

        if ((int)me->query("con") < 35)
                return notify_fail("你的先天根骨太低，无法领会九字真言。\n");

        if ((int)me->query("str") < 35)
                return notify_fail("你的先天臂力孱弱，无法修炼九字真言。\n");

        if (! me->query("reborn"))
                return notify_fail("你还没有通过佛祖的考验，无法修炼九字真言。\n");

        if ((int)me->query_skill("martial-cognize", 1) < 300)
                return notify_fail("你的武学修养太低，无法修习九字真言。\n");

        if ((int)me->query_skill("buddhism", 1) < 300)
                return notify_fail("你对禅宗心法参悟不够，无法修习九字真言。\n");

        if ((int)me->query("max_neili") < 8000)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force") < 400)
                return notify_fail("你的内功火候太浅。\n");

        if ((int)me->query_skill("hand", 1) < 300)
                return notify_fail("你的基本手法火候太浅。\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("jiuzi-zhenyan",1))
                return notify_fail("你的基本手法水平有限，无法领会更高深的九字真言。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

int practice_skill(object me)
{
        object weapon;

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练九字真言印法必须空手。\n");

        if ((int)me->query("qi") < 350)
                return notify_fail("你的体力不够，练不了九字真言。\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("你的内力不够，练不了九字真言。\n");

        me->receive_damage("qi", 200);
        me->add("neili", -300);
        return 1;
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("jiuzi-zhenyan", 1);
        if (lvl < 200) return 50;
        if (lvl < 300) return 70;
        if (lvl < 400) return 90;
        if (lvl < 500) return 100;
        return 110;
}

string perform_action_file(string action)
{
        return __DIR__"jiuzi-zhenyan/" + action;
}

