#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "戏台");
	set("long", @LONG
这里是戏台，虽然有些小，但是很干净。一个戏子正在表演。
你一踏上戏台，情不自禁地就唱起歌来。
LONG );
	set("exits", ([
		"down" : __DIR__"xiyuan",
	        "southdown":__DIR__"houtai",
	]));
	set("objects", ([
		"/d/city2/npc/xizi": 1,
	]));
	setup();
}

int valid_leave(object me, string dir)
{
        int i;

        if (! userp(me) || me->query_temp("hastryup"))
                return ::valid_leave(me, dir);

        if (dir=="down")
        {
                message_vision("\n$N一曲唱罢，一揖作礼，身子平飞，从台"
                               "上跃出，双手兀自\n抱拳向观众行礼，姿态"
                               "美妙，众人齐声喝采。\n", me);
                i = this_player()->query("meili");
                if (i<20)
                {
                        i += 10;
                        me->set("meili", i);
                        message_vision(HIC "\n$N的魅力值提高了。\n" NOR,
                                       me);
                }
        }

        return ::valid_leave(me, dir);
}
