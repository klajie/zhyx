
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
        set_name(HIC "青天甲" NOR, ({ "qingtian" }));
        set_weight(15000);        
        set("special", 1);
        set("unit", "张");        
        set("long", "LONG_DESCRIPTION");   
        set("owner_id","ID");   
        set("point", 560);
        set("no_sell", 1 ); 
        set("value",1);  
        set("no_steal", 1);    
        set("material", "tian jing");
        set("wear_msg", HIC "青天甲破空而响，阵阵雾气随之而出，却早已与$N" HIC "合而为一。\n" NOR);
        set("remove_msg", HIC "$N" HIC "仰天长啸，青天甲叮呤做响，刹那间周围雾气渐散，但青天甲早已"
                          "消失于天际。\n" NOR);
        if (! check_clone()) return;
        restore();
        set("armor_prop/dodge", 100);
        set("armor_prop/parry", 100);
        set("armor_prop/armor", 200);
        setup();
}
string long() { return query("long") + item_long(); }
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int cost;  

        if ((int)me->query_skill("force", 1) < 260
           || (int)me->query("neili") < 500
           || ! living(me) || random(4) != 1)
                return;

        cost = damage / 2;

        if (cost > 300) cost = 300;

        ap = ob->query_skill("force") * 12 + ob->query("max_neili");
        dp = me->query_skill("force") * 12 + me->query("neili");

        if (ap / 2 + random(ap) < dp)
        {
                me->add("neili", -cost);
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIR "$n" HIR "轻轻一叹，身上" HIC "青天甲" HIR "叮呤"
                                            "做响，$N" HIR "只觉心头一阵凄苦。这一招居然打不下去。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIM "只见$n" HIM "身上" HIC "青天甲" HIM "一颤，有"
                                            "若龙吟。" HIM "$N" HIM "你只感头晕目眩，居然一招打在空处。\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$N" HIW "一招打中$n" HIW "，顿觉毫不受力。定睛一看，原来是"
                                            "的" HIC "青天甲" HIW "幻化出来的幻象。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIY "$n" HIY "身上" HIC "青天甲" HIY "一阵金光闪过，$N" HIY "这一"
                                            "招被金光牢牢挡住，伤不了$n" HIY "分毫。\n" NOR]);
                        break;
                }
                return result;
        }
}
void owner_is_killed()
{
        destruct(this_object());
} 
