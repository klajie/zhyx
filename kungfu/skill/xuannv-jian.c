// xuannv-jian.c 玄女剑法 特殊属性九天玄女方可修习
// 可激发为剑法，招架及轻功


inherit SKILL;
#include <ansi.h>

string *dodge_msg = ({
        "$n轻扭蛮腰，顿时避开了$N的全部招数。\n",
        "$n犹如嫦娥飞天，身形变幻不定，$N的招式尽数落空。\n",
        "$n忽的疾闪，$N只觉得眼前无数个$n的幻影，根本无从出招。\n",
        "$n轻踏天女散花步，足不点地，将$N的进攻全部躲过。\n",
});

mapping *action = ({
([      "action":"$N脚步不停，手中的$w犹如一条丝带，缠向$n的$l",
        "force" : 460,
        "attack": 200,
        "dodge" : 150,
        "parry" : 40,
        "damage": 300,
        "damage_type":  "割伤"
]),
([      "action":"$N近前数步，抢得先机，随即剑气乱舞，手中的$w疾刺$n的$l",
        "force" : 490,
        "attack": 185,
        "dodge" : 160,
        "parry" : 45,
        "damage": 300,
        "damage_type":  "刺伤"
]),
([      "action":"$N身形飘忽不定，宛如天女，突然手中$w刺出，直指$n的$l",
        "force" : 465,
        "attack": 210,
        "dodge" : 180,
        "parry" : 45,
        "damage": 300,
        "damage_type":  "刺伤"
]),
([      "action":"$N飘然远去，忽又进前，速度快的不可思议，$w如闪电般刺向$n的$l",
        "force" : 480,
        "attack": 190,
        "dodge" : 195,
        "parry" : 55,
        "damage": 300,
        "damage_type":  "刺伤"
]),
([      "action":"眼见$N舞动手中$w，直刺向$n胸口，然而剑到中途却又突然奔向$n的面门",
        "force" : 500,
        "attack": 220,
        "dodge" : 180,
        "parry" : 57,
        "damage": 300,
        "damage_type":  "刺伤"
]),
([      "action":"$N身形变幻莫测，突然一扬手中$w，以迅雷不及掩耳之势插向$n的$l",
        "force" : 520,
        "attack": 260,
        "dodge" : 195,
        "parry" : 50,
        "damage": 300,
        "damage_type":  "刺伤"
]),
});

string *usage_skills = ({ "sword", "dodge", "parry" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
       return action[random(sizeof(action))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        if (me->query("gender") != "女性")
                return notify_fail("你练来练去觉得这个剑法还是适合女性练习！\n");

        if ( ! me->query("special_skill/queen"))
                return notify_fail("你不是九天玄女，无法修习玄女剑法。\n");
  
        if ((int)me->query_skill("dodge", 1) < 200)
                  return notify_fail("你的基本轻功火候不到，无法学习玄女剑法。\n");

        if ((int)me->query_skill("sword", 1) < 200)
                return notify_fail("你的剑术功底不行，难以领会玄女剑法。\n");

        if ((int)me->query("max_neili") < 2000)
                return notify_fail("你的内力太差，无法学习玄女剑法。\n");

	if ((int)me->query_skill("sword", 1) < (int)me->query_skill("xuannv-jian", 1))
		return notify_fail("你的基本剑法水平有限，无法领会更高深的玄女剑法。\n");

	if ((int)me->query_skill("dodge", 1) < (int)me->query_skill("xuannv-jian", 1))
		return notify_fail("你的基本轻功水平有限，无法领会更高深的玄女剑法。\n");

	//if ((int)me->query_skill("parry", 1) < (int)me->query_skill("xuannv-jian", 1))
	//	return notify_fail("你的基本招架水平有限，无法领会更高深的玄女剑法。\n");

       if (me->query_skill("martial-cognize", 1) < me->query_skill("xuannv-jian", 1))
                return notify_fail("你的武学修养不够，无法继续领会更"
                                   "高深的玄女剑法。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("玄女剑法博大精深，无法简单的通过练习进步。\n");
}

int difficult_level()
{       
       if ( this_player()->query_skill("xuannv-jian", 1) > 300)
       return 1100;
       else   return 900;
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("xuannv-jian", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 30;
        if (lvl < 150) return 50;
        if (lvl < 200) return 80;
        if (lvl < 250) return 100;    
         return 120;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;
        object m_weapon;

        if ((int) me->query_skill("xuannv-jian", 1) < 150 ||
            ! (m_weapon = me->query_temp("weapon")) ||
            me->query_skill_mapped("dodge") != "xuannv-jian" ||
            ! living(me) || m_weapon->query("skill_type") != "sword")
                return;
       
        ap = ob->query_skill("dodge") ;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("xuannv-jian", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIM "$n" HIM "脚踏天女散花步，$N" HIM
                                            "眼前顿时出现了无数个$n" HIM "的倩影，令$N"
                                            HIM "根本无从进击。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIM "$n" HIM "轻摆蛮腰，恰"
                                            "好令$N" HIM "的攻击偏离数寸。\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIM "$N" HIM "一招疾疾攻出，然而$n"
                                            HIM "轻轻一闪，不带一丝尘世俗气，已将$N"
                                            HIM "这一招刚好避开。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIM "$n" HIM "飞身一跃，突然不见了踪影，$N"
                                            HIM "心中大骇，却又见$n" HIM "又突然回到面前，"
                                            "速度之快当真令人匪夷所思。\n" NOR]);
                        break;
                }
                return result;
        } 
        /*
        else
        if (mp >= 100)
        {
                switch (random(4))
                {
                case 0:
                        result = HIM "只见$n" HIM "脚踏天女散花步，"
                                 "顿时出现了无数个$n" HIM "的倩影，可是$N"
                                 HIM "精通易理，将其中虚实辨得清清楚楚。\n" NOR;
                        break;
                case 1:
                        result = HIM "$n" HIM "轻摆蛮腰，然而$N"
                                 HIM "错步跟随，方位毫厘不差。\n" NOR;
                        break;
                case 2:
                        result = HIM "$n" HIM "轻轻一闪，不带一丝尘世俗气，已将$N"
                                 HIM "这一招刚好避开，可是$N"
                                 HIM "招中有招，进攻却是不止。\n" NOR;
                        break;
                default:
                        result = HIM "但见$n" HIM "飞身一跃，已不见了踪影，然而$N"
                                 HIM "反身出招，招数却更是巧妙。\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
        */
}

mixed hit_ob(object me, object victim, int damage_bonus, int i, int attack_time)
{
        object weapon;
        string name;

        weapon = me->query_temp("weapon");       
	      name = "手中" + weapon->name();       

        attack_time = (int)(me->query_skill("xuannv-jian", 1) / 40);

        if (attack_time > 9)
                attack_time = 9;
        
        if (me->is_busy()
        	 || random(2) == 0
           || ! living(victim)           
           || damage_bonus < 120
           || me->query("neili") < 300
           || me->query_temp("is_attacking") 
           || me->query_skill("xuannv-jian", 1) < 200
           || me->query_skill_mapped("sword") != "xuannv-jian")
        	return 0;

        
	        message_vision(HIG "\n霎时间只见$N腰肢微摆，宛如飞天般迎风起舞，" + 
                         name + HIG"好似一条玉带刺向$n！\n"
                	       NOR, me, victim);                	       
                	       
        me->set_temp("is_attacking", 1);
        me->start_busy(1 + random(attack_time / 2));
        me->add("neili", -attack_time * 20);
        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(victim))
                        break;

                if (! victim->is_busy() && random(2))
                        victim->start_busy(1);

                COMBAT_D->do_attack(me, victim, weapon, 0);
        }
        me->delete_temp("is_attacking");

	

        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"xuannv-jian/" + action;
}

