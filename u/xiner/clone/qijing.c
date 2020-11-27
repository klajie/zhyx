#include <weapon.h>
#include <ansi.h>

inherit THROWING;
 
void create()
{
	set_name(HIR "气劲" NOR, ({ "qi jing", "qi", "jing" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIW "无数闪烁不定的光芒，汇成的一束" HIR "四象气劲" HIW "。\n" NOR);
		set("unit", "团");
		set("value", 0);
		set("base_unit", "束");
		set("base_weight", 1);
		set("base_value", 0);
	}
	set_amount(1);
	init_throwing(200);
	setup();
}
