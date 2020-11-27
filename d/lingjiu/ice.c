//ROOM ice.c

#include <ansi.h>




inherit ROOM;

void init();

int do_xia(object me);

        
void create()
{
        set("short","玄冰");
        set("long",@LONG
这是一块采自天山之巅的千年玄冰,据说在那上面打坐事半功倍。
LONG );
        
        
        set("item_desc", ([
            "ice" : "这是一块采自天山之巅的千年玄冰,据说在那上面打坐事半功倍.\n你可以试着爬(climb)上去.\n",
        ]));
        set("no_clean_up", 0);
        setup();
}


void init()
{
        add_action("do_xia", "xia");
        
        
}

int do_xia(object me)
{
        
        me=this_player();
        
        if(!me->query_temp("ice"))
        return notify_fail("你又没爬上玄冰，下到哪去呀？。\n");
        
        message_vision("$N练完功，精神焕发地跳下地来。\n",me);
        me->set_temp("ice", 0);

        me->move("d/lingjiu/xuanbing");
        return 1;
}


