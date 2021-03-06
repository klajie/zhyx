// zhuangyu.c

inherit NPC;

#include <ansi.h>

int ask_weiwang();

void create()
{
	set_name("庄允城", ({ "zhuang yuncheng", "zhuang","yuncheng" }) );
	set("gender", "男性" );
	set("age", 40);
	set("int", 28);
	set("long",
		"这是个饱读诗书，却手无搏鸡之力的书生。\n"
             +"因编辑‘明史辑略’，被吴之荣告发，全家逮入京中。\n" );

	set("attitude", "peaceful");
	set_skill("literate", 100);
	set("noget", "庄允城叹道：我不行了，你走吧。唉，我担心我家里人啊。\n");
	set("chat_chance", 5);
	set("chat_msg", ({
	        "庄允城说道：只怪我当初好心，在书中夹了金叶送与他，\n"
	        "谁想这狼心狗肺的家伙竟然就去告发了我。唉...\n",
	        "庄允城说道：谁要把吴之荣抓到庄府就好了。\n",
	        "庄允城突然说道: 江湖威望很重要，威望高大有好处啊。\n",
	        "庄允城叹了口气，说道：我知道鳌拜书房的秘密，只可惜我出不去啊。\n",
	        "庄允城说道：谁要救了我，我一定把我知道的都告诉他。\n",
	}));
        set("inquiry", ([
		"鳌拜" : "鳌拜的书房里有宝贝。",
		"书房" : "书房里那幅画儿有学问。",
		"画" :  "移动那幅画时可是有方向的。",
		"画卷" :  "移动那幅画时可是有方向的。",
		"方向" :  "先左移一下，后右移一下就行了。",
		"暗门" :  "那可不能随便进，画里可是有学问的。",
		"吴之荣" :  "把他送到庄府去有好处。",
                "威望" :  (: ask_weiwang :),
	]) );
	setup();
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	object ob; 
	int i;

        if (! query("startroom") ||
            find_object(query("startroom")) != environment())
                return;

	ob = this_player();
	if (interactive(ob) && ! is_fighting())
        {
	        say("庄允城哈哈笑道：终于有人来救我了！这位" +
                    RANK_D->query_respect(ob) + "，鳌府的宝贝\n"
                    "可不少啊，你不仔细找找？\n");
        }

	i = ob->query("weiwang");
        if (i < 20)
	{
	        i += 10;
                ob->set("weiwang",i);
	        message_vision(HIC "$N" HIC "的江湖威望提高了！\n" NOR,
                               this_player());
	}
	command("tell " + ob->query("id") +
                " 你现在的江湖威望是 " + i + "。");
}

int accept_object(object me, object ob)
{
	if (! present(ob, me))
                return notify_fail("你没有这件东西。");

	if ((string)ob->query("id") != "book ming")
                return 0;

        message_vision("庄允城喘了口气，又说：庄府在京城东北边。\n", me);
        destruct(ob);
        return 1;
}
