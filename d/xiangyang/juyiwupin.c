inherit ROOM;

void create()
{
	set("short", "物品房");
	set("long", @LONG
这是聚义馆的堆放各种各样物品的房间。
LONG );
	set("exits", ([
		"northwest" : __DIR__"juyihuayuan",
	]));
	set("coor/x",-495);
	set("coor/y",-412);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

