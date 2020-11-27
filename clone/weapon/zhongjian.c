// heavysword.c 重剑

#include <weapon.h>
inherit SWORD;

void create()
{
        set_name("玄铁剑", ({ "heavy sword", "sword", "jian" }));
        set_weight(30000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "这是一柄玄铁打造的重剑，入手十分沉重。\n");
                set("value", 200);
                set("material", "xuantie");
                set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回剑鞘。\n");
        }
        init_sword(80);
        setup();
}
