#include <ansi.h>

inherit ITEM;

inherit F_NOCLONE;

void create()
{
	set_name( HIW "门票" NOR, ({ "men piao" }));
	set_weight(100);
	set("long", NOR + HIW "这是一张由馨儿签发的比武门票，上面写着：\n\n"
		"      “准许进行转世比武！”\n\n\n"
		"把通知书交给［公平子］就可以进行比武了！" NOR);
	set("unit", "张");
	set("value", 0);
	set("no_sell", "这东西你也卖钱！滚一边去！");
	set("material", "paper");
        setup();
//        check_clone();
}
