// jinyun huxin.c
// 锦云护心 [吉祥]
// 成套装备
// by yuchang                                                                   

#include <ansi.h>
#include <armor.h>

inherit ARMOR;

void create()
{
	set_name( YEL"锦云护心"NOR, ({ "jinyun huxin", "huxin" }) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "块");
                set("long", YEL"这是一块金丝织成的护心，价值连城。"NOR"
防御指数：三十
成套装备："HIC"[天祥防具]"NOR" "HIR"龙凤战甲"NOR" "YEL"锦云护心"NOR" "HIG"天灵护腕"NOR" "HIY"金锦披风"NOR" "HIW"云盘护腰"NOR"
特殊效果："HIG"加快经脉运行(force)"NOR"\n");
		set("value", 60000);
		set("material", "gold");
		set("armor_prop/force", 5);
		set("armor_prop/armor", 30);
		
	}
	setup();
}
