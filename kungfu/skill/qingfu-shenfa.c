// qingfu-shenfa.c 青蝠身法
// by jeeny
// modify by xiner 02/3/2009
 
#include <ansi.h> 
      
inherit SKILL; 
        
string *dodge_msg = ({
	"只见$n一招「福满乾坤」，身形陡然纵起，躲过了$N这一招。\n",
	"$n一式「五蝠献寿」，身形晃动，向一旁飘出，避开了$N这一招。。\n"
	"$n使出「洞天福地」，一个空心筋斗向后翻出，避开了$N的凌厉攻势。\n",
	"$n一招「云龙百蝠」，身随意转，$N只觉眼前一花，$n已绕至$N的身后。\n",
        "$N这一招眼看就要击中，可是$n略一侧身，避过$N的劲力，实属匪夷所思。\n", 
        "$n不退反进，从$N肋下钻过，恰恰避开这一招。\n", 
}); 
       
int valid_enable(string usage)  
{  
        return usage == "dodge"; 
} 
       
int valid_learn(object me) 
{ 
        int lvl; 
       
        lvl = me->query_skill("qingfu-shenfa", 1); 
        if (lvl > 300) lvl = 300;
       
        if (me->query("max_neili") < 2000 + lvl * 10) 
                return notify_fail("你的内力修为还欠火候。\n");
 
        if (me->query("dex") < 26)
		return notify_fail("你资质不佳,学不会如此高深的轻功。\n");

	if ((!me->query("reborn")&&me->query("str") > 25)||
		(me->query("reborn")&&me->query("str") > 35))
               	return notify_fail("你实在太笨重，无法学习如此轻盈的步法。\n");

        if (me->query("static/sadly") > 2)
                return notify_fail("你只觉心中一阵阵忧伤袭来，再难提高青蝠身法的水平。\n"); 

        return 1; 
} 
       
string query_dodge_msg(string limb) 
{ 
        return dodge_msg[random(sizeof(dodge_msg))]; 
} 
       
mixed valid_damage(object ob, object me, int damage, object weapon) 
{ 
        mixed result; 
        int ap, dp; 
       
	if ((int)me->query_skill("qingfu-shenfa", 1) < 100 ||
		me->query_skill_mapped("dodge") != "qingfu-shenfa" ||
		me->query("family/family_name") != "明教" || 
            ! living(me)) 
                return; 
        
        ap = ob->query_skill("dodge"); 
        dp = me->query_skill("dodge", 1) / 2 + 
             me->query_skill("qingfu-shenfa", 1); 

        if (ap / 2 + random(ap) < dp * 4 / 5) 
        { 
                result = ([ "damage": -damage ]); 
       
                switch (random(5)) 
                { 
                case 0: 
                        result += (["msg" : HIB "但见$n" HIB "面露微笑，身形一挫，$N" 
                                            HIB "只觉眼前一花，似乎出现了千百个$n的" 
                                            HIB "幻影。\n" NOR]); 
                        break; 
                case 1: 
                        result += (["msg" : HIB "$N" HIB "只觉眼前一道青影，一闪一晃，"
                                            HIB "顿时不见了$n的踪影。\n" NOR]); 
                        break; 
                case 2: 
                        result += (["msg" : HIB "但见$n" HIB "身子一仰，向后倒飞出去，$N" 
                                            HIB "见机猛攻，却又见$n" HIB "一个刹步，已转" 
                                            "$N身后，当真令人匪夷所思。\n" NOR]); 
                case 3:
                        result += (["msg" : HIB "只见$n" HIB "长啸一声犹如一只蝙"
                                            "蝠一样纵身而起，于半空倒立，$N" HIB 
                                            "这招却扑了个空。\n" NOR]);
                        break;
		default:
                        result += (["msg" : HIB "但见$n" HIB "身法轻盈无比，忽然跃"
                                    "高忽而落下，令$N" HIB "完全无从攻击。\n" NOR]);
                        break;
                        break; 
                } 
                return result; 
        }
 
} 
      
int query_effect_dodge(object attacker, object me)
{
	if (me->query("family/family_name") != "明教")
	{return 10;}
	else
	{
        int lvl;
        lvl = me->query_skill("qingfu-shenfa", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 30;
        if (lvl < 150) return 50;
        if (lvl < 200) return 70;
        if (lvl < 250) return 90;
        if (lvl < 300) return 100;
        return 110;
	}
}
      
int practice_skill(object me) 
{ 
	int cost;
	cost = 60 + (int) me->query_skill("qingfu-shenfa", 1) / 3;

        if (me->query_skill("qingfu-shenfa", 1) > 100
	   && me->query("family/family_name") != "明教")
                return notify_fail("没有韦一笑的指点，你不敢轻易锻炼青蝠身法。\n");

        if ((int)me->query("qi") < 70) 
                return notify_fail("你的体力太差了，难以练习青蝠身法。\n"); 
     
        if ((int)me->query("neili") < cost) 
                return notify_fail("你的内力不够了，无法练习青蝠身法。\n"); 
      
        me->receive_damage("qi", 50); 
        me->add("neili", -cost); 
        return 1; 
} 
      
string perform_action_file(string action) 
{ 
        return __DIR__"qingfu-shenfa/" + action; 
} 

void skill_improved(object me)
{
        int lvl;
        int lvl2;
        lvl = me->query_skill("qingfu-shenfa", 1);
        lvl2 = me->query_skill("jiuyang-shengong", 1);

        if (lvl > 100 && lvl2 < lvl)
        {
                me->apply_condition("bianfu-except", lvl / 2 +
                                    (int)me->query_condition("bianfu-except"));
        }
}