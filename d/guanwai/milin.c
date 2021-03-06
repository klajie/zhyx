// /guanwai/milin.c

#include <ansi.h>

inherit ROOM;


void create()
{
        set("short", "密林");
        set("long", @LONG
这里是鹿鸣峰西坡下的一片森林，这里地处深山老林，时常
有凶猛的野兽出没。
LONG);
        set("exits", ([
                "northup" : __DIR__"luming",
        ]));
        set("outdoors", "guanwai");
        setup();
}

void init()
{
        
        if (find_call_out("call_beast") == -1)
                call_out("call_beast", random(60) + 20);
}

void call_beast()
{
        object ob;
        string beast;
        int n;

        remove_call_out("call_beast");

        if (sizeof(filter_array(all_inventory(), (: interactive :))) < 1)
                return;

        // Call out wovles when player is here
        call_out("call_beast", random(200) + 30);

        if (present("he xiong", this_object()) ||
            present("ye lang", this_object()))
                return;

        switch (random(10))
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
                n = 1 + random(4);
                beast = "/clone/quarry/lang2";
                break;
        case 8:
                n = 1;
                beast = "/clone/quarry/xiong";
                break;
        case 9:
                n = 1;
                beast = "/clone/quarry/xiong2";
                break;
        }

        message("vision", "山坳里面突然串出" + chinese_number(n) +
                beast->query("unit") + beast->name() +
                "\n", this_object());
        while (n--)
        {
                ob = new(beast);
                ob->move(this_object());
        }
}

