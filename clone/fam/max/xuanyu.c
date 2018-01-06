#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "九地玄玉" NOR, ({"xuan yu", "xuan", "yu"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "\n一块绿色的九地玄玉，拥有能医重病，又能毒\n"
                            "杀人于一身的至宝——九地玄玉，相传神农氏\n"
                            "所用神农尺就是用这枚九地玄玉精炼而成。\n" NOR);
                set("unit", "块");
                set("value", 10000000);
                set("item_origin", 1);
                set("material_attrib", "xuan yu");
                set("material_name", HIG "九地玄玉" NOR);
                set("can_make", "all");
                set("power_point", 160);
        }
}
