// poshan-dao.c 翻云刀法

#include <ansi.h>
inherit SKILL;

string *xue_name = ({ 
"劳宫穴", "膻中穴", "曲池穴", "关元穴", "曲骨穴", "中极穴", "承浆穴", "天突穴", "百会穴",
"幽门穴", "章门穴", "大横穴", "紫宫穴", "冷渊穴", "天井穴", "极泉穴", "清灵穴", "至阳穴", });

string *attack_name = ({
"翻云刀气", "覆雨刀气", "翻江倒海玄劲", "天翻地覆无上玄功", });

string *parry_msg = ({
       "$n以"+MAG"「翻云刀气」"NOR+"护体，身边竟旋起一阵旋风，让$N目瞪口呆。\n",
      "$n在这刹那间，身体变得柔弱无骨，给在人一种奇异的感觉，这正是来自外域的"+HIM"「瑜珈奇术」\n",
       "$n运起"+CYN"「天翻地覆无上玄功」"NOR+"犹如天神临世,$N的招式再也不使不下去了。\n",
        "$n大喝一声，以"+RED"「翻江倒海玄劲」"NOR+"之威，震慑在场众人。竟无人敢出手了。\n",
});

mapping *action = ({
([      "action" : "$N握紧手中$w一招「翻云一刀」点向$n的$l",
        "force" : 650,
        "attack": 300,
        "dodge" : 400,
        "parry" : 400,
        "damage": 500,
        "weapon": HIW "翻云刀气" NOR,
        "damage_type" : "割伤"
]),
([      "action" : "$N向前跨上一步，手中$w使出「翻云覆雨」砍向$n的喉部",
        "force" : 750,
        "attack": 400,
        "dodge" : 300,
        "parry" : 300,
        "damage": 200,
        "weapon": HIR "覆雨刀气" NOR,
        "damage_type" : "割伤"
]),
([      "action" : "只见$N抡起手中的$w，使出「翻江倒海」万点金光直劈$n",
        "force" : 750,
        "attack": 400,
        "dodge" : 300,
        "parry" : 300,
        "damage": 200,
        "weapon": HIY "翻江倒海玄劲" NOR,
        "damage_type" : "劈伤"
]),
([      "action" : "$N使出「搅海翻江」，手中$w如刮起狂风一般闪烁不定，割向$n",
        "force" : 950,
        "attack": 450,
        "dodge" : 200,
        "parry" : 200,
        "damage": 200,
        "weapon": WHT "覆雨刀气" NOR,
        "damage_type" : "割伤"
]),
([      "action" : "$N随手使出刀法之奥义「翻手为云」，手中$w如鬼魅一般铺天盖地的砍向$n",
        "force" : 850,
        "attack": 300,
        "dodge" : 400,
        "parry" : 400,
        "damage": 500,
        "weapon": HIW "翻江倒海玄劲" NOR,
        "damage_type" : "割伤"
]),
([      "action" : HIY"$N使出翻云刀法之最终绝技[1;36m「天翻地覆」[0m,[1;33m手中$w犹如蛟龙一般劈向$n[0m"NOR,
        "force" : 1000,
        "attack": 300,
        "dodge" : 250,
        "parry" : 250,
        "damage": 500,
        "weapon": WHT "天翻地覆无上玄功" NOR,
        "damage_type" : "割伤"
]),
});


string *usage_skills = ({ "blade", "parry" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
       return action[random(sizeof(action))];
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}
int practice_skill(object me)
{
      return notify_fail("翻云刀法博大精深，无法简单的通过练习进步。\n");
}

int valid_learn(object me)
{
        int level;

     
        level = me->query_skill("fanyun-daofa", 1);

        if (me->query_skill("blade", 1) < level)
                return notify_fail("你对基本刀法的理解还不够，无法继续领会更"
                                   "高深的翻云刀法。\n");

        if (me->query_skill("parry", 1) < level)
                return notify_fail("你对基本招架的理解还不够，无法继续领会更"
                                   "高深的翻云刀法。\n");

       if (me->query_skill("martial-cognize", 1) < level)
                return notify_fail("你的武学修养不够，无法继续领会更"
                                   "高深的翻云刀法。\n");

        return ::valid_learn(me);
}

int get_ready(object me)
{
        return 1;
}

int difficult_level()
{
       if ( this_player()->query_skill("fanyun-daofa", 1) > 300)
       return 1200;
       else   return 1000;
}


mixed hit_ob(object me, object victim, int damage_bonus)
{
        string name1, name2, weapon;
        name1 = xue_name[random(sizeof(xue_name))];
        name2 = attack_name[random(sizeof(attack_name))];

        victim->receive_wound("qi", damage_bonus * 3, me);
        me->add("neili", me->query("jiali") / 3);

        if (victim->query("neili") < 500)
                victim->set("neili", 0);
        else
                victim->add("neili", -300);

        return NOR + HIR "$n" HIR "接下$N" HIR "一招，" + name2 + "顿时破体而"
               "入，全身真气由" + name1 + "狂泻而出。\n" NOR;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;

        ap = ob->query_skill("parry");
        dp = me->query_skill("fanyun-daofa", 1);

        if (random(ap * 2 / 3) < dp * 3 / 2)
        {
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIW "$n" "以"HIR"「翻云刀气」护体，身边竟旋起一,"
                                                  "阵旋风，让$N目瞪口呆。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIW "$n" "在这刹那间，身体变得柔弱无骨，给"
                                                  "人一种奇异的感觉，这正是来自外域的"HIM"「瑜珈奇术」。\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$n" "运起"CYN"「天翻地覆无上玄功」，犹如天神临世,"
                                                   "$N的招式再也不敢出手。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIW "$n" "大喝一声，以"RED"「翻江倒海玄劲」之威，"
                                                     "震慑在场众人。竟吾人敢出手了。\n" NOR]);
                        break;
                }
                return result;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("fanyun-daofa", 1);
        if (lvl < 200) return 100;
        if (lvl < 250) return 150;
        if (lvl < 350) return 180;
        return 200;
}

string perform_action_file(string action)
{
        return __DIR__"fanyun-daofa/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"fanyun-daofa/exert/" + action;
}


