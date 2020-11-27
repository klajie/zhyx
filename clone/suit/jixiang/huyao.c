// huyao.c

#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
	set_name( HIW"云盘护腰"NOR, ({ "yunpan huyao", "huyao" }) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "条");
                set("long", HIW"这是一件银线和蚕丝织成的护腰，形状恰似一片盘云。"NOR"
防御指数：二十
成套装备："HIC"[天祥防具]"NOR" "HIR"龙凤战甲"NOR" "YEL"锦云护心"NOR" "HIG"天灵护腕"NOR" "HIY"金锦披风"NOR" "HIW"云盘护腰"NOR"
特殊效果："HIG"无"NOR"\n");           
		set("value", 6000);
		set("material", "waist");
		set("armor_prop/armor", 20);
		set("shaolin",1);
	}
	setup();
}
