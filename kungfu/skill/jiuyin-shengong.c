//updated by kasumi 2007.6.7

#include <ansi.h>

inherit FORCE;

/*
string *dodge_msg = ({
        "$n动也不动，把$N震到一边。\n",
        "$n身形微微一抖，将$N迫退。\n",
        "$n手足忽的一晃，$N竟然无法进击，只能自保。\n",
        "$n轻轻一格，将天下所有进攻招数全部封死。\n",
});
*/

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("jiuyin-shengong", 1);
        return lvl * lvl * 22 * 15 / 100 / 200;
}

int query_jingli_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("jiuyin-shengong", 1);
        return lvl * 14 / 5;
}

mapping *actionf = ({
([      "action":"$N伸手一探，顿时气流呼啸而至，单手毫无花巧的插向$n$l",
        "force" : 550,
        "attack": 180,
        "dodge" : 100,
        "parry" : 90,
        "damage": 200,
        "weapon": HIW "九阴无极劲" NOR,
        "damage_type":  "刺伤"
]),
([      "action":"$N双手齐抓，幻出千万道耀眼的金光，齐齐照向$n的$l",
        "force" : 560,
        "attack": 180,
        "dodge" : 110,
        "parry" : 120,
        "damage": 220,
        "weapon": HIW "九阴无极劲" NOR,
        "damage_type":  "割伤"
]),
([      "action":"$N身形一转，拳头携着疾速旋转的气流挥出，疾如闪电，势如雷霆，击向$n",
        "force" : 570,
        "attack": 190,
        "dodge" : 110,
        "parry" : 120,
        "damage": 250,
        "weapon": HIW "九阴无极劲" NOR,
        "damage_type":  "刺伤"
]),
([      "action":"$N移步向前，一掌不紧不慢的拍向$n的$l，空气中顿时传来一阵刺耳的暴响",
        "force" : 590,
        "attack": 220,
        "dodge" : 120,
        "parry" : 115,
        "damage": 260,
        "weapon": HIW "九阴无极劲" NOR,
        "damage_type":  "割伤"
]),
([      "action":"$N身体一侧，一掌凌空劈出，一股凛冽的气流顿时澎湃涌至$n的$l处",
        "force" : 600,
        "attack": 250,
        "dodge" : 130,
        "parry" : 120,
        "damage": 270,
        "weapon": HIW "九阴无极劲" NOR,
        "damage_type":  "割伤"
]),
([      "action":"$N双手合拳，蓦的张开，只听“嗤嗤”破空之声，十道劲气一齐射向$n的$l",
        "force" : 610,
        "attack": 200,
        "dodge" : 115,
        "parry" : 120,
        "damage": 280,
        "weapon": HIW "九阴无极劲" NOR,
        "damage_type":  "刺伤"
]),
});


mapping *actionw = ({
([      "action" : "$N攻势忽缓而不疏，$w变化无常，捉摸不定向$n慢慢卷去",
        "force" : 470,
        "attack": 180,
        "dodge" : 75,
        "parry" : 115,
        "damage": 225,
        "damage_type": "擦伤"
]),
([      "action":"$N手中的$w突焕气象森严，便似千军万马奔驰而来，$w就如棍棒一般横扫$n",
        "force" : 450,
        "attack": 160,
        "dodge" : 85,
        "parry" : 125,
        "damage": 210,
        "damage_type": "擦伤"
]),
([      "action":"$N卷起手中的$w，就如铁锤一般对着$n乱砍乱砸，没有半点章法",
        "force" : 460,
        "attack": 175,
        "dodge" : 80,
        "parry" : 125,
        "damage": 205,
        "damage_type": "割伤"
]),
([      "action":"$N运用$w幻化做一个一个圆圈，似乎要将$n团团包围",
        "force" : 525,
        "attack": 160,
        "dodge" : 65,
        "parry" : 125,
        "damage": 190,
        "damage_type": "内伤"
]),
([      "action":"$N含笑回转$w，伸手一指，颇得拈花指之意，点向$n的$l",
        "force" : 540,
        "attack": 180,
        "dodge" : 70,
        "parry" : 120,
        "damage": 260,
        "damage_type": "刺伤"
]),
});



string main_skill() { return "jiuyin-shengong"; }

mapping sub_skills = ([
        "dafumo-quan"      : 230,
        "jiuyin-baiguzhao" : 230,
        "cuixin-zhang"     : 230,
        "shexing-lifan"    : 230,
        "yijin-duangu"     : 230,
        "yinlong-bian"     : 230,
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
                tell_object(me, "你演练完毕，只感气血上涌，看来自己阴阳不调，无法演练九阴神功。\n" NOR);
                return 0;
        }

        if (me->query("character") != "心狠手辣")
        {
                tell_object(me, "你的天性不符，无法习得九阴神功。\n" NOR);
                return 0;
        }

  

        if (me->query("con") < 34)
        {
                tell_object(me, "你演练完毕，发现自己的先天根骨太差，无法将九阴真经内的武功合一。\n");
                return 0;
        }

        if (me->query("str") < 38)
        {
                tell_object(me, "你演练完毕，发现自己的先天膂力孱弱，无法将九阴真经内的武功合一。\n");
                return 0;
        }

        if (me->query_skill("literate", 1) < 250)
        {
                tell_object(me, "你觉得九阴真经内的武功都极其深奥，看来多研究一下学问可能更有帮助。\n");
                return 0;
        }

        if (me->query_skill("martial-cognize", 1) < 250)
        {
                tell_object(me, "你演练完毕，发现自己的武学修养尚待提高，暂且无法将九阴真经内的武功合一。\n");
                return 0;
        }

        if ((int)me->query("max_neili") < 4500)
        {
                tell_object(me, "你觉得自己真气不继，无法继续演练九阴神功。\n");
                return 0;
        }

        if (random(10) < 8)
        {
                tell_object(me, "你觉得有所感悟，或许再演练一次就能融会贯通，将二者合一。\n");
                return 0;
        }

        tell_object(me, HIW "一阵凡尘往事涌上心头，你几欲放声长叹。霎那间，你放眼回首，竟有一股莫名\n"
                        "的悲哀。宗师泰斗那种高出不胜寒、登泰山而小天下之感犹然而生，你只觉得以\n往的"
                        "武学现在看来是多么的渺小可笑。\n" NOR);
        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

string *usage_mapped_skills = ({ "unarmed", "parry", "force" });
string *usage_skills = ({ "unarmed", "strike", "finger", "claw", "hand", 
                          "cuff", "parry", "whip", "force" });
string *usage_skills2 = ({ "unarmed", "parry", "force" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int valid_force(string force) { return 1; }

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
        return weapon ? actionw[random(sizeof(actionw))] :
                        actionf[random(sizeof(actionf))];
}

/*
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
*/

int valid_learn(object me)
{
        int level;
        int i;

     

        if (me->query("character") != "心狠手辣")
                return notify_fail("你的天性不符，无法习得九阴神功。\n");

        if (me->query("str") < 38)
                return notify_fail("你发现自己的膂力不足，无法将九阴神功运用自如。\n");

        if (me->query("con") < 34)
                return notify_fail("你发现自己先天根骨不足，无法运转九阴神功。\n");

        if (me->query("gender") == "无性")
                return notify_fail("你无根无性，阴阳不调，难以领会高深的九阴神功。\n");

        level = me->query_skill("jiuyin-shengong", 1);

        if ((int)me->query_skill("martial-cognize", 1) < 250)
                return notify_fail("你觉得九阴神功过于深奥，以自己的武学修养全然无法明白。\n");

        for (i = 0; i < sizeof(usage_skills2); i++)
                if (me->query_skill(usage_skills2[i], 1) < level)
                        return notify_fail("你对" + to_chinese(usage_skills2[i]) +
                                           "的理解还不够，无法继续领会更高深的九阴神功。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("九阴神功博大精深，无法简单的通过练习进步。\n");
}


mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;
        int cost;

        if ((int)me->query_skill("jiuyin-shengong", 1) < 150 || 
			!me->query("reborn") ||
            ! living(me) || (int)me->query("neili") < 150 ||
            me->query_skill_mapped("parry") != "jiuyin-shengong" ||
            ob->query_temp("weapon"))
                return;

        cost = damage / 2;
        if (cost > 100) cost = 100;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("jiuyin-shengong", 1);

        if (ap / 2 + random(ap) < dp)
        {
                me->add("neili", -cost);
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIR "$n" HIR "默运九阴神诀，护住全身。$N" HIR
                                            "一招击中$n" HIR "小腹，只觉落手处软"
                                            "绵绵的，力道竟消失得无影无踪。 \n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIR "$N" HIR "一招攻出，$n" HIR "怒喝一声，不退"
                                            "反进，竟将$N" HIR "这招逼回。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIR "$n" HIR "面带微笑，轻描淡写间，已将$N" HIR "所"
                                            "有进攻招式全部封死。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIY "$n" HIY "默运九阴神诀，护住全身。但是$N" HIY
                                 "内力深厚无比，长叹一声，一招竟结实地打在$n" HIY
                                 "身上。\n" NOR;
                        break;
                case 1:
                        result = HIY "$n" HIY "不退反进，试图将$N" HIY "的招式逼回。但是"
                                 "$N" HIY "招式陡然一变，$n" HIY "顿时一惊，却已然中招。\n" NOR;
                        break;

                default:
                        result = HIY "$n" HIY "面带微笑，轻描淡写间欲将$N" HIY "的进攻"
                                 "招式封死。但是$N" HIY "早已看去其中玄虚，冷笑一声，$N" HIY
                                 "却已中招。\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
         }
}


mixed hit_ob(object me, object victim, int damage_bonus, int i, int attack_time)
{
        if (me->query_temp("weapon"))return 1;

        if (me->is_busy()
           || ! living(victim)
           || damage_bonus < 150
           || me->query("neili") < 200
           || (me->query_skill_mapped("force") != "shenzhaojing" && me->query_skill_mapped("force") != "jiuyin-shengong")
           || me->query_skill("jiuyin-shengong", 1) < 250)
        	return 0;

	if (me->query_skill_mapped("force") == "shenzhaojing")
		damage_bonus += damage_bonus / 5;

        if (damage_bonus > 150)
        {
                me->add("neili", -50);
                victim->receive_wound("qi", (damage_bonus - 100) / 2, me);
                victim->add("neili", -((damage_bonus - random(100)) / 2), me);

                return random(2) ? HIR "$N" HIR "招式陡然一变，右手成爪，猛然间抓向$n" HIR "周身大穴。\n" NOR:
                                   HIR "$N" HIR "快步上前，全身真气贯于左手食指，猛地刺$n" HIR "胸口大穴！\n" NOR;
        }        
}

int difficult_level()
{
	object me;
	int lvl1,lvl2;
	if (me = this_player())
	{
		lvl1 = me->query_skill("jiuyin-shengong", 1);
		lvl2 = me->query_skill("shenzhaojing", 1);
		if (lvl1 <= lvl2) return 300;
	}
	return 700;
}

string perform_action_file(string action)
{
        return __DIR__"jiuyin-shengong/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"jiuyin-shengong/exert/" + action;
}
