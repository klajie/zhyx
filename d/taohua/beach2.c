// Code of ShenZhou
//Chaos, Ryu, 3/10/97
#include <ansi.h>
inherit ROOM;

string long_desc();

void create()
{
        set("short", "海滨");

        set("long", (: long_desc :));

        set("exits", ([
                "north" : __DIR__"beach",
        ]));

        set("objects", ([
                __DIR__"obj/shizi" : 3,
        ]));

        set("cost", 2);
        set("outdoors", "taohua");

        setup();
}

void init()
{
        add_action("do_lingwu", "lingwu");
}

string long_desc()
{
        string desc;

        desc  = "这是一片银白的沙滩，踩上去，柔柔的银沙裟裟的响，混合阵阵海浪的声音，让人心旷神怡。\n";

        if (NATURE_D->outdoor_room_event() == "event_dawn" ||
            NATURE_D->outdoor_room_event() == "event_evening")
        {
               desc += HIG "远远望去大海浩淼，万里无波，海天一线处一道白线滚滚而来，渐近渐快，稍后\n" NOR;
               desc += HIG "洪涛汹涌，白浪连山，倾刻之间已至台下，惊涛骇浪狠狠打在台基上。你顿时感觉\n" NOR;
               desc += HIG "立足不稳，摇摇欲坠，不禁脸上变色，为这天地之威所深深撼动。\n" NOR;

        }
        else {
                desc += HIC "你登高远望，但见长天一碧，万里无波，当真是“海阔凭鱼跃，天高\n" NOR;
                    desc += HIC "任鸟飞”。当此景象，你深吸一口气，只觉胸腹之间清气充盈，轻飘\n" NOR;
                desc += HIC "飘的似乎就要乘风而去。\n" NOR;

        }

        return desc;
}

int do_lingwu()
{
        object me = this_player();
        int level, check;

        if ((int)me->query_skill("bibo-shengong",1) < 30)
                return notify_fail("你的碧波神功还没入门呢，不过在这里听听碧波的声音也好。\n");

        if ((int)me->query_skill("bibo-shengong",1) > 99)
                return notify_fail("你对着浩瀚的大海，挺身玉立，心情舒畅。\n");

        if (me->query("jing") < 30)
                return notify_fail("你的精神太差了。\n");

        if ( me->can_improve_skill("bibo-shengong") )
        {
                me->receive_damage("jing", 40);
                me->improve_skill("bibo-shengong", me->query("int")/3);
                write("你于惊涛骇浪声中领悟碧波神功其中奥秘!\n");
        }
        else
        {
                write("你实战经验不足，无法领悟碧波神功。\n");
        }
        return 1;
}
