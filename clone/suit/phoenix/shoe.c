
// 成套装备
// update by kasumi
#include <ansi.h>
#include <armor.h>
inherit BOOTS;

void create()
{
        set_name(HIG"朱雀之爪"NOR, ({ "phoenix shoes","shoes", "xie" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
		  set("long", GRN"这是一双布满诡异鳞片的鞋子。"NOR"
防御指数：20~40
特殊效果：提高有效轻功60~80级。
成套装备："HIR"[朱雀之舞]"NOR" "RED"朱雀之羽"NOR" "YEL"朱雀之眼"NOR" "GRN"朱雀之爪"NOR" "HIC"朱雀之翼"NOR"
套装效果："HIG"临时附加二百级阴阳八卦。"NOR"\n");

                set("unit", "双");
                set("value",5000);		
                set("material", "boots");                
                set("armor_prop/armor",20+random(20));
                set("armor_prop/dodge", 60+random(20));
                set("no_sell", 1 );
                set("no_steal", 1 ); 

        }
        setup();
}
int query_autoload()
{
        return 1;
}