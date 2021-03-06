//zsh_szdamen.c

#include <room.h>

inherit ROOM;

void create()
{ 
        set("short", "紫衫会前门");
        set("long",@LONG
这里是紫衫会总部所在地。紫衫会在江湖上行动神秘，屡行侠义
之举，许多江湖好汉均慕名而来。
LONG );
        set("outdoors", "suzhou");
        set("exits", ([
                "south"  :  __DIR__"hehuating",
                "north"  :  __DIR__"zsh_szzb",
        ])); 
        set("objects", ([   
             __DIR__"npc/zsh_guard" : 2,   
            ]));
               
        setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "north") 
        {
           if (! me->query_temp("good_zsh") && me->query("bang_good/name") != "紫衫会")
               return notify_fail("守卫一把拦住你：“我紫衫会不欢迎外人，请回吧！”\n"); 
           else
           {
              me->delete_temp("good_zsh");
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 

