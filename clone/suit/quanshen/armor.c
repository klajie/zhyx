// quanshen armor.c
// 拳神战甲 [拳神]
// 成套装备
// by yuchang
#include <ansi.h>
#include <armor.h>

inherit CLOTH;


void create()
{
	set_name( HIG"拳神战甲"NOR, ({ "quanshen zhanjia", "zhanjia" }) );
	set_weight(3000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "件");
		set("long", HIR"这是一件通体透红的战甲。上面绘着一龙一凤。"NOR"
防御指数：一百四十
成套装备："HIG"[拳神装备]"NOR" "HIG"拳神战甲"NOR" "YEL"锦云护心"NOR" "HIG"天灵护腕"NOR" "HIY"金锦披风"NOR" "HIW"云盘护腰"NOR"
特殊效果："HIG"超强防御(parry)"NOR"\n");
		set("value", 100000);
		set("material", "cloth");
		set("wear_msg", RED"只见$N斗出一件"HIR"龙凤战甲"RED"穿在身上，一龙一凤的图案翼翼生辉。\n" NOR);
		set("armor_prop/parry", 6);
		set("armor_prop/armor", 140);
		set("power",10);
	}
	setup();
}

