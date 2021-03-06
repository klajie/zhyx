#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
#define TONGZHI "/clone/lonely/book/tongzhi"

void create()
{
        set_name("小双儿", ({ "xiner's shuanger" }));
        set("long", "她是一个十分清秀的少女,大约十四五岁年纪。\n一张雪白的脸庞,眉弯嘴小,笑靥如花,正笑嘻嘻地看着你。\n"); 
        set("title", HIW "馨儿的丫环" NOR);
	set("nickname", HIM "天下无双" NOR);
	set("gender", "女性");
	set("age", 15);
	set("attitude", "peaceful");
	set("shen_type", 1);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("per", 35);

        set("max_qi", 30000);
        set("max_jing", 30000);
        set("max_neili", 25000);
	set("jiali",10);
        set("neili", 25000);
        set("combat_exp", 100000000);

        set("chat_chance_combat", 150);
        set("chat_msg_combat", ({
                (: perform_action, "hand.jie" :),
                (: perform_action, "hand.jiuzi" :),
                (: perform_action, "unarmed.zhi" :),
                (: perform_action, "unarmed.zhua" :),
                (: perform_action, "unarmed.zhang" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        set_skill("force", 550);
        set_skill("jiuyin-shengong", 500);
        set_skill("dodge", 550);
        set_skill("zhuangzi-wu", 550);
        set_skill("parry", 500);
        set_skill("unarmed", 550);
        set_skill("hand", 550);
        set_skill("jiuzi-zhenyan", 500);
        set_skill("qiankun-danuoyi", 500);
        set_skill("literate", 200);
        set_skill("buddhism", 260);
        set_skill("lamaism", 260);
        set_skill("count", 100);

        map_skill("force", "jiuyin-shengong");
        map_skill("dodge", "zhuangzi-wu");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("hand", "jiuzi-zhenyan");
        map_skill("unarmed", "jiuyin-shengong");
		
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 500);

        prepare_skill("hand", "jiuzi-zhenyan");
        prepare_skill("unarmed", "jiuyin-shengong");

        setup();

	carry_object("/d/city/npc/cloth/feature")->wear(); 

        if (clonep(this_object()))
        {
                set("chat_chance", 30);
                set("chat_msg", ({(: random_move :)}));
                set("born_time", time());
                keep_heart_beat();
        }
}

void random_move()
{
	if (time() - query("born_time") > 300)
	{
		message_vision("$N嘻嘻一笑，飘然而去。\n", this_object());
	//	CHANNEL_D->do_channel( this_object(), "chat", "我走啦！下次再来玩！\n");
		destruct(this_object());
		return;
	}
        NPC_D->random_move(this_object());
}

int accept_fight(object ob)
{
        if (is_fighting())
        {
                message_vision(CYN "$N" CYN "对$n" CYN "叫道：你先别急"
                               "，我打完这架就来领教你的。\n" NOR,
                               this_object(), ob);
                return -1;
        }       

        if (query("qi") < 10000 ||
            query("jing") < 10000 ||
            query("neili") < 10000)
        {
                message_vision(CYN "$N" CYN "摇摇头对$n" CYN "道：我现"
                               "在太累了，待我歇会儿再说吧。\n" NOR,
                               this_object(), ob);
                return -1;
        }

	if (ob->query_temp("tzs"))
        {
                message_vision(CYN "$N" CYN "摇摇头对$n" CYN "道："
                               "你已经拿了通知书又来干嘛？\n" NOR,
                               this_object(), ob);
                return -1;
        }

	if (ob->query("reborn"))
        {
                message_vision(CYN "$N" CYN "摇摇头对$n" CYN "道："
                               "你不是已经转过世了么！\n" NOR,
                               this_object(), ob);
                return -1;
        }

        message_vision(HIW "$N" HIW "大喜道：好好好！我正手痒痒，咱们"
                       "来比划比划！\n" NOR, this_object(), ob);

        competition_with(ob);
        return -1;
}


void win()
{
        object ob;
        if (! objectp(ob = query_competitor()))
                return;

        message_vision(CYN "$N" CYN "看了看$n" CYN "，嘿嘿笑道：你的水"
                       "平太菜了，要好好练功，好好练功。\n" NOR,
                       this_object(), ob);
        ::win();
}


void lost()
{
        object me;
        object ob;
	object owner;

        if (! objectp(me = query_competitor()))
                return;

/*	if (me->query("shen") < 0)
	{
		tell_object(me, HIC "\n双儿说道：“今日我虽不是你的对手，来日定当为武林除害！\n" NOR);
		return;
	}
*/

        ob = find_object(TONGZHI);
        if (! ob) ob = load_object(TONGZHI);

        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (!environment(ob))
	{
        	command("say 好吧，看你的本事还算可以啦！这份“转世通知书”就给你了！");
	        command("say 带着在身上不要掉了哦！不然～～～");
		ob->move(me);
		me->set_temp("tzs",1);
		::lost();
        }else
	{
		if (objectp(owner))
			tell_object(me, HIC "\n我刚刚才给"HIR + owner->query("name") + HIC "弄了一份通知书，你等会再来吧！”\n\n" NOR);
		else
		        tell_object(me, HIC "\n双儿说道：“你功夫不错，人品也还可以。可惜通知书现在还没弄好，你还得等一会儿。”\n\n" NOR);
        	::lost();
	}
}

void unconcious()
{
        say( HIC"双儿从怀里拿出一颗天王保命丸塞进嘴里嚼了起来。\n"NOR);
        say( HIC"片刻之间，双儿又恢复了精神。\n"NOR);
        revive();
        set("eff_qi", query("max_qi"));
        set("qi", query("max_qi"));
        set("eff_jing", query("max_jing"));
        set("jing", query("max_jing"));
        set("jingli", query("eff_jingli"));
	remove_all_enemy(1);
}

void die()
{
        unconcious();
}