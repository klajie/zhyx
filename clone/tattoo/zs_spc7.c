#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "国士无双图" NOR, ({ "wushuang tu", "wushuang", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "这是一张古旧的图片，上面绘着些纹样。");
                set("unit", "张");
                set("value", 99000);
                set("material", "paper");
                set("tattoo_long", "无双国士，征战四海，平定天下");
                set("can_tattoo", ({ "胸口", "后背", }));
                set("tattoo_type", ({ "悟性", "根骨", "臂力" ,"身法" }));
                set("tattoo_int", 2);
                set("tattoo_con", 2);
                set("tattoo_str", 2);
                set("tattoo_dex", 2);
                set("tattoo_special", "shuang");
                set("tattoo_spcname", "国士无双");
        }
}
