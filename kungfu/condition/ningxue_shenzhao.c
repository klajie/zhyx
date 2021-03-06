#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "ningxue_shenzhao"; }

string chinese_name() { return "凝血之毒"; }

string update_msg_others()
{
       return HIR "$N" HIR "只感内息顿滞，“哇”的一声喷出一大口鲜血。\n" NOR;
}

string update_msg_self()
{
        return HIR "你只感内息顿滞，全身血液竟渐渐的开始凝固起来！\n" NOR;
}

string die_msg_others()
{
        return HIW "$N" HIW "只觉全身血液瞬间停止了流动，"
               "从头到脚慢慢的结成了冰，直挺挺的倒了下去。\n" NOR;
}

int jing_damage(object me, mapping cnd)
{
        return cnd["level"] * 1;
}

int qi_damage(object me, mapping cnd)
{
        return cnd["level"] * 2;
}

string die_reason()
{
        return "凝血之毒发作，受尽折磨而死";
}

int dispel(object me, object ob, mapping cnd)
{
        if ((me->query_skill("xixing-dafa", 1) > 1000 && 
             me->query_skill_mapped("force") == "xixing-dafa") ||
             (me->query_skill("huagong-dafa", 1) > 1000 &&
              me->query_skill_mapped("force") == "huagong-dafa") || 
             (me->query_skill("beiming-shengong", 1) > 1000 &&
              me->query_skill_mapped("force") == "beiming-shengong"))
        {
               me->add_temp("apply/dispel-poison", 1000);
               me->set_temp("add_dispel", 1); 
               call_out("clear_dispel", 2, me);
        }

        return ::dispel(me, ob, cnd);

}

void clear_dispel(object me)
{
       if (me->query_temp("apply/dispel-poison") && 
           me->query_temp("add_dispel"))
       {
                me->delete_temp("add_dispel");
                me->add_temp("apply/dispel-poison", -1000);
                return;
       }
               
}
