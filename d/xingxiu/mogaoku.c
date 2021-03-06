inherit ROOM;

void create()
{
        set("short", "莫高窟");
        set("long", @LONG
这里墙壁上绘制着与佛教相关的画面，有仙女飞天，还有
反弹琵琶。洞中还有很多佛像和经书。你被这些瑰丽的文化之
宝惊呆了。
LONG );
        set("exits", ([
                "out" : __DIR__"yueerquan",
        ]));
        set("no_clean_up", 0);
        setup();
}

void init()
{
        add_action("do_think", "think");
}

int do_think()
{
        object ob;
        int c_skill;
        ob = this_player();

        c_skill = (int)ob->query_skill("training", 1);
        if (ob->query_skill("literate", 1) < 100)
        {
                write("你的文化知识太低，无法领悟石壁内容。\n", ob);
                return 1;
        }

        if (! ob->can_improve_skill("training"))
        {
                write("你的实战经验不足，无法领悟石壁内容。\n");
                return 1;
        }

        if (ob->query("jing") < 40)
        {
                write("你精力不能集中，现在无法领悟石壁内容。\n");
                return 1;
        }

        if (c_skill > 229)
        {
                write("你觉得石壁内容太肤浅了。\n");
                return 1;
        }

        message_vision("$N面对着石壁趺坐静思，良久，对「驭兽术」"
                        "似有所悟。\n", ob);
        ob->improve_skill("training", 1 + random(ob->query("int")));
        ob->receive_damage("jing", 35);
        return 1;
}

