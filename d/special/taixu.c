#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "\n\n      太        虚        幻        境\n" NOR);
        set("long", WHT "\n"
"白茫茫的一片，分不出哪是天哪是地，周围一片寂静。\n"
"这就是传说中的太虚幻境。\n" NOR);
 set("exits", ([ 
            "chushengdao"   : "/d/special/liudaolunhui/chushengdao",   
            "diyudao"   : "/d/special/liudaolunhui/diyudao",   
            "eguidao"   : "/d/special/liudaolunhui/eguidao",  
            "rendao"   : "/d/special/liudaolunhui/rendao",     	  
            "tiandao"   : "/d/special/liudaolunhui/tiandao",   
            "xiuluodao"   : "/d/special/liudaolunhui/xiuluodao",     	 
        ]));
        setup();
}

