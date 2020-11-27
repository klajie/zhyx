// shufang.c 盘龙居书房

#include <ansi.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
	set("short", "书房");
	set("long", @LONG
这里是盘龙居的主人读书写字的地方，干净明亮。文房四宝整整齐齐
的摆在桌子上面。有时主人也在这里签发一些邀请客人的请柬。
LONG );

	set("default_long", "这里是ROOM_NAME的主人ROOM_OWNER读书写字的"/* EXAMPLE */
                            "地方，干净明亮。文房四宝整整齐齐的摆在桌" /* EXAMPLE */
                            "子上面。有时ROOM_OWNER也在这里签发(sign"/* EXAMPLE */
                            ")一些邀请客人的请柬。");                  /* EXAMPLE */
                                                                       /* EXAMPLE */

	set("exits", ([
		"east" : __DIR__"jusuo",
	]));

        set("sleep_room", 1);
        setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}

