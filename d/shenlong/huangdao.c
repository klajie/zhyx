// huangdao.c
// Modified by haiyan

inherit ROOM;
 
void create()
{
        set("short", "荒岛");
        set("long",@LONG
这里是大海中的一个孤岛。你极目远望，似乎能看到一个黑点，大概
就是神龙岛了。看来只能跳下水游过去了。
LONG);   
        set("no_clean_up", 0);
        set("exits", ([ 
             "south"     : __DIR__"milin", 
        ])); 

        setup();
}

void init()
{
      add_action("do_jump", "jump");
}

int do_jump(string arg)
{
    object me = this_player();

    if( !arg || (arg != "sea" && arg != "dahai" && arg != "hai"))
         return notify_fail("你要往哪里跳？\n");

    tell_object(me, "你“扑通”一声跳入海中。\n");
    me->move("/d/shenlong/sea");
    return 1;
}

