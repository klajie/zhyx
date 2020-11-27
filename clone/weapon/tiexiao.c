#include <ansi.h>
#include <weapon.h>

inherit XSWORD;

void create()
{
        set_name("铁箫", ({ "tie xiao","xiao" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "支");
                set("long", HIW "一支黑黝黝的铁萧。武林中人经常以箫代剑。\n" NOR);
                set("value", 800);
                set("no_sell", 1);
                set("material", "stone");
                set("wield_msg", "$N大袖一挥，手中已多了一支铁箫。\n" NOR);
                set("unwield_msg", "$N手中铁萧一转，眨眼间铁箫已然不见影踪。\n" NOR);
                set("stable", 100);
        }
        init_xsword(30);
        setup();
}
