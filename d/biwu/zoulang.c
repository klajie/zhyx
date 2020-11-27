// 山猫(adx) by snow 2000-05-15

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
你走在一条条石铺成的小路上，小路的北面就是比武场的中看台，南面是
比武场的大门。你可以(enter)进入比武场。
LONG);
        set("no_fight",1);
        set("exits", ([
                "south" : __DIR__"gate",
        ]));
        setup();
}

void init()
{
        add_action ("do_enter","enter");
}

int do_enter(string arg)
{
        object me=this_player();
        string mout=YEL ""+me->query("name")+"走进了比武场。\n" NOR;
        string min=YEL ""+me->query("name")+"场外走了进来。\n" NOR;

        message( "vision", mout, environment(me), ({me}) );
        me->move(__DIR__"kantai2");
        message( "vision", min, environment(me), ({me}) );
        return 1;
}

