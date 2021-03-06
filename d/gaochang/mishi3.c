// room: well1.c
// BY yuchang

inherit ROOM;
#include <ansi.h>
#define QUAN "/d/zhuanshi/obj/quan"
int do_use(string arg);
int do_search(string arg);

void create()
{
        set("short", "暗室");
        set("long", @LONG
这是在高昌最深处的一个暗室，什么也看不清。
LONG);
        set("exits", ([
                "out":__DIR__ "mishi2",
        ]));
        set("no_clean_up", 0);
        set("item_desc", (["hole":"一个不知深浅的石洞，不知该不该搜一搜看。\n"]));
        set("count", 1);
        setup();
}

void init()
{
        add_action("do_use", "use");
        add_action("do_search", "search");
}

int do_use(string arg)
{
        object me;
        me = this_player();

        if (!arg || arg == "")
                return 0;
        if (!present("fire", me))
                return 0;
        if (arg == "fire")
        {
                message_vision("$N点燃了火折，发现墙壁上有一小洞(hole)，似乎有什么东西在里面。\n", me);
                me->set_temp("marks/fire", 1);
                return 1;
        }
}

int do_search(string arg)
{
        object me, ob;
        object quan;
        object none;
        me = this_player();

        if (!me->query_temp("marks/fire"))
                return 0;
        if (!arg || (arg != "hole" && arg != "小洞"))
                return notify_fail("你要搜哪里？\n");
        if (query("count") < 1)
        {
                return notify_fail("洞里面什么也没有了。\n");
        }
        if (me->query("cor") < 25)
                return notify_fail("你刚想伸手，忽然有点害怕，想了想还是算了。\n");
        add("count", -1);
        quan = new (QUAN);
        if (quan->violate_unique())
        {
                destruct(quan);
                quan = none;
        }
        if (random(4) > 0 && quan)
        {
                message_vision("$N往洞里摸了摸，摸出金刚圈来。\n", me);
                message("channel:chat", MAG "【高昌迷宫】某人：" + me->query("name") + "拿到金刚圈啦。\n" NOR, users());
                quan->move(me);

                return 1;
        }
}
