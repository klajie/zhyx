#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIC "地心噬魂" NOR, ({"shi hun", "shi", "hun"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC "\n一块青色的地心噬魂，拥有集天下万毒及邪能\n"
                            "于一身的至宝——地心噬魂，相传为邪灵之主\n"
                            "罗刹到九幽之底，掘出当年被女娲消灭的异兽\n"
                            "骸骨，以地心毒火精炼而成。\n" NOR);
                set("unit", "块");
                set("value", 10000000);
                set("item_origin", 1);
                set("material_attrib", "shi hun");
                set("material_name", HIC "地心噬魂" NOR);
                set("can_make", "all");
                set("power_point", 160);
        }
}
