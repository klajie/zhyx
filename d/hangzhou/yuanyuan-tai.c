// yuanyuantai
inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "圆缘台");
	set("long", @LONG
山道蜿蜒而上，面前出现了一块不大的平地，北边便是著名的月老祠。留
心祠前石碑，忽才知道身处的这片空地原来叫做“圆缘台”，所谓千里姻缘一
线牵，圆缘台正是意指圆满这姻缘的地方。环顾四周，只见雾迷林麓，月照崖
峰，风卷松浪，景色怡人，别饶佳趣。
LONG );
	set("exits", ([
		"north" : __DIR__"yuelao-ci",
        "east" : __DIR__"qixi-tai",
        "south" : __DIR__"shandao2",
	]));
	set("objects", ([
		__DIR__"npc/shusheng": 1,
	]));
//	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
