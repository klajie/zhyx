#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + CYN "天山玄铁" NOR, ({ "tianshan xuantie", "tianshan", "xuantie" }));
        set_weight(25000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + CYN "世间极为罕见的玄铁，采至天山，着手极为沉重。\n"
				                      "可以打造刀剑。基础伤害70~95\n" NOR);
                set("unit", "块");
                set("value", 30000);
                set("item_origin", 1);
                set("material_attrib", "xuantie");
                set("material_name", NOR + CYN "天山玄铁" NOR);
                set("can_make", ({ "剑", "刀"}));
                set("power_point", 70);               
        }
}

int query_autoload()
{
        return 1;
}

