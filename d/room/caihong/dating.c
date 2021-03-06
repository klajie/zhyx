// dating.c 彩虹居大厅
#include <room.h> 


//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
	set("short", "大厅");             /* EXAMPLE */
//**    set("short", "ROOM_NAME大厅");
	set("long", @LONG
这就是彩虹居主人迎送客人的地方，正中有一些桌椅，侧面是屏风，
厅堂中挂着两个条幅。不过上面居然什么都没有写。东面是主人的房间。
LONG );

	set("default_long", "这就是ROOM_NAME主人ROOM_OWNER迎送客"  /* EXAMPLE */
                            "人的地方。正中有些桌椅，侧面是两扇"   /* EXAMPLE */
                            "屏风。东首是主人ROOM_OWNER的房间，"   /* EXAMPLE */
                            "有一扇木门虚掩着。南边是大门，出去"   /* EXAMPLE */
                            "就是院子。");                         /* EXAMPLE */
                                                                   /* EXAMPLE */
       set("gate", "close");
	setup();

	set("exits", ([
                "east"   : __DIR__"woshi",
		"north"  : __DIR__"houyuan",
                "south"  : __DIR__"xiaoyuan",   /* EXAMPLE */
	]));

        create_door("east", "木门", "west", DOOR_CLOSED);

        set("no_sleep_room", 1);


//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}

void init()
{
//**        add_action("do_push", "push");
//**        add_action("do_close", "close");
}

int do_push(string arg)
{
        object me;
        object room;

        if (query("gate") == "open")
                return notify_fail("大门开着呢，你还推什么？\n");

        me = this_player();
        message_vision("$N用力推了推大门，就听大门“吱呀呀”的打开了。\n",
                           me);
    
        room = get_object(__DIR__"xiaoyuan");
        message("vision", "大门“吱呀呀”的被人推开了。\n", room);
        set("gate", "open");
        set("exits/south", __DIR__"xiaoyuan");
        room->set("exits/north", __FILE__);
        room->set("gate", "open");
        remove_call_out("do_close");
        call_out("do_close", 10, 0, 1);
        return 1;
}

int do_close(string arg, int n)
{
        object me;
        object room;

        if (query("gate") == "close")
                return notify_fail("大门关着呢，你还再关一遍？\n");

        me = this_player();
        if (! n)                       
                message_vision("$N走上前去，用力合上大门。\n", me);
         else
        
                message("vision", "大门“吱呀呀”的被人关上了。\n",
                        this_object());
        

        room = get_object(__DIR__"xiaoyuan");
        message("vision", "大门“吱呀呀”的被人关上了。\n", room);
        set("gate", "close");
        delete("exits/south");
        room->set("gate", "close");
        room->delete("exits/north");
        return 1;
}


