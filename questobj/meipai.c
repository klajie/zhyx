#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(CYN"梅牌"NOR, ({ "meipai" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "块");
            set("material", "stone");
            set("long", "西方神教寒梅先生的信物。\n");
          } 
    ::init_item();
}  
