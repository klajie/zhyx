// wuyue-shenjian.c 五岳神剑
// 需学会华山，衡山和嵩山的pfm才能悟得。
// By Kasumi 2009


#include <ansi.h>
inherit SKILL;

string *msg = ({
"$N使一招华山剑法「有凤来仪」，手中$w剑光暴长，向$n的$l刺去",
"$N剑随身转，一招华山剑法「无边落木」罩向$n的$l",
"$N舞动$w，一招华山剑法「鸿飞冥冥」挟著无数剑光刺向$n的$l",
"$N手中$w龙吟一声，祭出华山剑法「平沙落雁」往$n的$l刺出数剑",
"$N手中$w剑光暴长，一招华山剑法「金玉满堂」往$n$l刺去",
"$N手中$w化成一道光弧，直指$n$l，一招华山剑法「白虹贯日」发出虎哮龙吟刺去",
"$N右手$w一立，举剑过顶，弯腰躬身，使一招「万岳朝宗」正是嫡系正宗的嵩山剑法",
"$N手中$w突然间剑光一吐，化作一道白虹，端严雄伟，端丽飘逸，正是嵩山剑法的精要所在，一招「千古人龙」向$n$l直刺过来",
"$N手中$w突然间剑光一吐，一招嵩山剑法「叠翠浮青」化成一道青光，气壮雄浑，向$n$l直刺过来",
"$N手中$w剑光一吐，一招嵩山剑法「玉进天池」威仪整肃，端严雄伟，向$n$l直刺过来",
"$N左手向外一分，右手$w向右掠出，使的是嵩山派剑法「开门见山」",
"$N手中$w自上而下的向$n直劈下去，一招「独劈华山」，真有石破天惊的气势，将嵩山剑法之所长发挥得淋漓尽致",
"$N手中$w刷的一剑自左而右急削过去，正是一招嵩山派正宗剑法「天外玉龙」。但见$w自半空中横过，剑身似曲似直，长剑便如一件活物一般",
"$N手中$w一晃，向右滑出三步，一招泰山剑法「朗月无云」，转过身来，身子微矮，$w向$n斜斜刺去",
"$N手中$w圈转，一招泰山剑法「峻岭横空」去势奇疾，无数剑光刺向$n的$l",
"$N展开剑势，身随剑走，左边一拐，右边一弯，越转越急。猛地$w剑光暴长，一招泰山剑法「泰山十八盘」往$n$l刺去",
"$N手中$w倏地刺出，一连五剑，每一剑的剑招皆苍然有古意。招数古朴，内藏奇变，正是泰山剑法「五大夫剑」",
"$N手中$w寒光陡闪，手中的$w，猛地反刺，直指$n胸口。这一下出招快极，抑且如梦如幻，正是「百变千幻衡山云雾十三式」中的绝招",
"$N不理会对方攻势来路，手中$w刷的一剑衡山剑法「泉鸣芙蓉」，向$n小腹刺去",
"$N不理会对方攻势来路，手中$w刷的一剑衡山剑法「鹤翔紫盖」，向$n额头刺去",
"$N手中$w倏地刺出，剑势穿插迂回，如梦如幻，正是一招衡山剑法「石廪书声」，向$n$l刺去",
"$N手中$w倏地刺出，极尽诡奇之能事，动向无定，不可捉摸。正是一招衡山剑法「天柱云气」，指向$n$l",
"$N飞身跃起，使出衡山剑法「雁回祝融」！，$w发出一声龙吟从半空中洒向$n的$l",
"$N意带神闲，一式恒山剑法「苍松迎客」，$w轻轻飞动，幻起一片剑光，围掠$n全身",
"$N使一招恒山剑法「拨云见日」，身形向上飘起，手中$w虚虚实实幻出点点寒光射向$n$l",
"$N仰天长笑，身形飘然而起，在半空中身子一旋，一式恒山剑法「轻云蔽月」狂风般地击向$n",
"$N左手捏着剑诀，右足踏开一招恒山剑法「星划长空」向上斜刺，长剑锵然跃出倏的化作几点星光射向$n的$l",
"$N向前迈去一大步，使出恒山剑法「织女穿梭」，手中$w舞成一个光球，迅若奔雷击向$n的$l",
"$N大喝一声，一招恒山剑法「曲径通幽」，$w闪电般划出一道大圆弧劈向$n的$l",
"$N忽然身形高高跃起，使出恒山剑法「云里乾坤」，$w幻出漫天花瓣，迅如雷霆射向$n的$l",
});

mapping query_action(object me, object weapon)
{
	int lvl = me->query_skill("wuyue-shenjian", 1);
	if (lvl > 600) lvl = 600;

	if (lvl > 400)
	{
		return ([
			"action" : msg[random(sizeof(msg))],
			"attack" : 200+random(lvl/2),
			"force"  : 350+random(lvl/2),
			"dodge"  : 200,
			"parry"  : 200,
			"damage" : 200+random(lvl/2),
			"damage_type" : "刺伤",
			]);
	}else
	{
		return ([
			"action" : msg[random(sizeof(msg))],
			"attack" : 100+random(lvl/4),
			"force"  : 150+random(lvl/4),
			"dodge"  : 100,
			"parry"  : 100,
			"damage" : 100+random(lvl/4),
			"damage_type" : "刺伤",
			]);
	}

}


int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        object ob;

	if (me->query("family/family_name") != "华山派"
		&& me->query("family/family_name") != "嵩山派"
		&& me->query("family/family_name") != "衡山派")
		return notify_fail("你非五岳剑派中人哪里能领悟其中精妙的招式。\n");;

        if (! (ob = me->query_temp("weapon"))
           || (string)ob->query("skill_type") != "sword")
                return notify_fail("你必须先找一柄剑才能够练习。\n");      

		if (!me->query("can_perform/huashan-jian/xian"))
			    return notify_fail("你没有领悟到华山剑法的绝招：夺命连环三仙剑，没有办法领悟五岳神剑。\n");

		if (!me->query("can_perform/wushen-jian/shen"))
			    return notify_fail("你没有领悟到衡山五神剑的绝招：五神朝元势，没有办法领悟五岳神剑。\n");

		if (!me->query("can_perform/poyang-jian/long"))
			    return notify_fail("你没有领悟到嵩山破阳冷光剑的绝招：天外玉龙，没有办法领悟五岳神剑。\n");


        if (me->query_skill("martial-cognize", 1) < 300)
                return notify_fail("你觉得五岳神剑极其深奥，依照自己的武学修养"
                                   "难以理解。\n");

        if ((int)me->query("max_neili") < 5000)
                return notify_fail("你的内力修为不够，没有办法练五岳神剑。\n");

        if ((int)me->query_skill("sword", 1) < 300)
                return notify_fail("你的基本剑法太差，没有办法练五岳神剑。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("wuyue-shenjian", 1))
                return notify_fail("你的基本剑法火候有限，无法领会更高深的五岳神剑。\n");

        return 1;
}


mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp,level,backdamage;
        object m_weapon;

        if (! (int)me->query_temp("wysj_mian") ||
            ! (m_weapon = me->query_temp("weapon")) ||
            ! living(me) || m_weapon->query("skill_type") != "sword")
                return;
		level=(int)me->query_skill("wuyue-shenjian", 1);
		if (level<200) backdamage=0;
		else if (level<400) backdamage=(int)damage/3 ;
		else if (level<600) backdamage=(int)damage/2 ;
		else backdamage=damage;
      
        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force", 1) + mp;
        dp = me->query_skill("wuyue-shenjian", 1);

        if (ap / 2 + random(ap) < dp * 3 / 4)
        {
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIR "$n" HIR "反转手中的" + m_weapon->name() +
                                            HIR "直刺$N" + HIR "的破绽，“扑哧”一声穿了个血窟窿。\n" NOR]);
						ob->receive_wound("qi", backdamage);
                        break;

                default:
                        result += (["msg" : HIC "$n" HIC "挥动手中的" + m_weapon->name() +
                                            HIC "，不住的变幻剑势，让$N"
                                            HIC "被迫回防自守！\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIY "$n" HIY "不住变动守式，企图防住$N" HIY "的"
                                 "招数，霎那间却见$N" HIY "撤手回转，再攻出"
                                 "一招。\n" NOR;
                        break;

                case 1:
                        result = HIY "$n" HIY "持剑轻轻撩起，欲以内劲阻挡$N"
                                 HIY "的攻势，可$N" HIY "蓦的变招，从另一方"
                                 "位攻入。\n" NOR;
                        break;

                default:
                        result = HIY "$n" HIY "剑出如风，飘然护住全身，可$N"
                                 HIY "理也不理，只管运足内劲，中破攻入。\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int practice_skill(object me)
{
        int cost;
        me = this_player(); 		
	if ((int) me->query_skill("wuyue-shenjian", 1) < 300)
	        return notify_fail("你对五岳神剑的领悟不够三百级尚不足已自行练习。\n");

        cost = me->query_skill("wuyue-shenjian", 1);
        if (me->query("family/family_name") == "衡山派")
	cost = cost/2 + random(cost)/2;
        else
	cost = cost + random(cost);

        if ((int)me->query("neili") < cost)
                return notify_fail("你的内力不够练五岳神剑。\n");

        if ((int)me->query("qi") < cost / 2)
                return notify_fail("你的体力不够练五岳神剑。\n");

        me->receive_damage("qi", cost / 2);
        me->add("neili", -cost);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"wuyue-shenjian/" + action;
}
