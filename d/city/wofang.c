inherit ROOM;
void create()
{
         set("short","铁匠卧房");
         set("long",@LONG
这里是铁匠的卧房，如果你累了，也可以在这里休息一下。
LONG);
         set("exits",([
         "north":__DIR__"datiepu",
]));
       set("sleep_room", 1);
       setup();
}

