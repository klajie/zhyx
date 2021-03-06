#include <weapon.h>
#include <ansi.h>

inherit SWORD;

string do_wield();
string do_unwield();

void create()
{

        set_name(HIY "残阳宝剑" NOR, ({ "canyang baojian", "canyang",  
                                        "sword" })); 
        set_weight(2500);
        if (clonep())
                set_default_object(__FILE__);
        else {

                set("long", HIY " 
此剑长五尺，细而长，通体泛出金光。剑柄弯曲，上刻残阳图 
纹，剑脊之上还铸有无数密密麻麻的古篆，似乎与武学有关。\n" NOR); 
                set("unit", "把");
                set("value", 800000);
                set("no_sell", "这你也敢卖？我都不敢买啊!");
                set("no_put", "这东西你装不进去!");
                set("material", "steel");
                set("wield_msg", (: do_wield :));
                set("unwield_msg", CYN "$N" CYN "一声轻哼，将手中的" 
                                       "残阳宝剑插入剑鞘。\n" NOR); 
                set("stable", 100);
        }
        init_sword(140);
        setup();
}

string do_wield()
{
        object me = this_player();

        // 得授乌老大的碧烟刀法(biyan-dao)者不受刀身毒害。
        if (me->query_skill("biyan-dao") < 1000 && me->query_skill("poison") < 1200)
        {
                me->affect_by("ningxue_shenzhao", ([
                        "level" : 150,
                        "id"    : "wu laoda",
                        "duration" : 5 + random(5)
                ]));
        	remove_call_out("poison");
        	call_out("poison", 6, me);
                return CYN "$N" CYN "蓦地纵声长啸，霎时寒" 
                                       "芒一闪，一道金光破空划过，落于$N" 
                                       CYN "掌间。\n\n" NOR;
        } else
        if (me->query_skill("biyan-dao") < 1000 && me->query_skill("poison") > 1800)
        {
                return CYN "$N" CYN "蓦地纵声长啸，霎时寒" 
                                       "芒一闪，一道金光破空划过，落于$N" 
                                       CYN "掌间。\n\n" NOR;
        } else
        if (me->query_skill("biyan-dao") < 1000 && me->query_skill("poison") > 1200)
        {
                me->affect_by("ningxue_shenzhao", ([
                        "level" : 100,
                        "id"    : "wu laoda",
                        "duration" : 3 + random(3)
                ]));
        	remove_call_out("poison");
        	call_out("poison", 18, me);
                return CYN "$N" CYN "蓦地纵声长啸，霎时寒" 
                                       "芒一闪，一道金光破空划过，落于$N" 
                                       CYN "掌间。\n\n" NOR;
        } else
        {
                return CYN "$N" CYN "蓦地纵声长啸，霎时寒" 
                                       "芒一闪，一道金光破空划过，落于$N" 
                                       CYN "掌间。\n" NOR;
        }
}

void poison(object me)
{
        object weapon;

        if (objectp(weapon = me->query_temp("weapon"))
           && weapon->query("id") == "canyang baojian"
           && me->query_skill("poison") < 1800)
	{
	        message_vision(HIB "\n$N" HIB "右手不由得一颤，原来残阳宝剑剑"
                               "身剧毒已沁入肌肤。\n" NOR, me);
                me->affect_by("ningxue_shenzhao", ([
                        "level" : 300,
                        "id"    : "wu laoda",
                        "duration" : 10 + random(10)
                ]));
	       	remove_call_out("poison");
       		call_out("poison", 12, me);
	}
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->query_skill("blade") < 150)
                return damage_bonus / 2;

        switch (random(10))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("blade") / 10 + 2);
                return GRN "$N" GRN "残阳宝剑连连挥斩，化作一道道绿芒，$n"
                       GRN "只觉一股香气扑鼻而来，不敢大意，当\n即凝神闭气，"
                       "招架顿时散乱。\n" NOR;
        case 1:
                n = me->query_skill("blade");
                victim->affect_by("ningxue_shenzhao", ([
                        "level" : me->query("jiali") + random(me->query("jiali")),
                        "id"    : me->query("id"),
                        "duration" : n / 70 + random(n / 30)
                ]));
                return GRN "$N" GRN "残阳宝剑连连挥斩，化作一道道绿芒，$n"
                       GRN "只觉一股香气扑鼻而来，微一诧异，顿\n时已吸入数口"
                       "毒气。\n" NOR;
        }
        return damage_bonus;
}
