#include <ansi.h>
inherit NPC;
inherit F_GUARDER;

void create()
{
        set_name("铁传甲", ({ "tie chuanjia", "tie", "chuanjia" }) );
        set("nickname", WHT "铁掌" NOR);
        set("title", HIY "伍佰级" NOR);
        set("gender", "男性");
        set("age", 42);
        set("long", "一个身材魁梧的汉子。\n");
        set("attitude", "peaceful");

        set("str", 40);
        set("con", 40);
        set("int", 14);
        set("dex", 40);

        set("max_qi", 20000);
        set("max_jing", 15000);
        set("neili", 20000);
        set("max_neili", 20000);
        set("jiali", 300);

        set("combat_exp", 26000000);
        set("shen_type", 1);
        set("score", 5000);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "dodge.guiyuan" :),
                (: perform_action, "parry.zhao" :),
                (: perform_action, "strike.dao" :),
                (: perform_action, "strike.lei" :),
                (: perform_action, "strike.yin" :),
                (: perform_action, "strike.long" :),
                (: perform_action, "strike.ying" :),
                (: perform_action, "strike.juesha" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :)
        }) );

        set_skill("unarmed", 500);
        set_skill("force", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("strike", 500);
        set_skill("jinzhong-zhao", 500);
        set_skill("yijinjing", 500);
        set_skill("tie-zhang", 500);
        set_skill("shexing-lifan", 500);

        map_skill("parry", "jinzhong-zhao");
        map_skill("force", "yijinjing");
        map_skill("strike", "tie-zhang");        
        map_skill("dodge", "shexing-lifan");
        prepare_skill("strike", "tie-zhang");   

	set_temp("apply/damage", 300);
	set_temp("apply/unarmed_damage", 300);
	set_temp("apply/armor", 300);

	set("apply/dodge", 100);

        setup();

        //carry_object("/kungfu/class/sky/obj/miji1");
        carry_object("/clone/cloth/cloth")->wear();
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

        if (query("qi") < 100 ||
            query("jing") < 500 ||
            query("neili") < 1500)
        {
                message_vision(CYN "$N" CYN "摇摇头对$n" CYN "道：我现"
                               "在太累了，待我歇会儿再说吧。\n" NOR,
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

        revive();
        set("eff_qi", query("max_qi"));
        set("qi", query("max_qi"));
        set("eff_jing", query("max_jing"));
        set("jing", query("max_jing"));
        set("jingli", query("eff_jingli"));
        set("neili", query("max_neili"));
	remove_all_enemy(1);
        ::win();
}


void lost()
{
	command("say 你很厉害哦！");
        ::lost();
}

void unconcious()
{
        say( HIC"铁传甲说道：“想搞我没那么容易。”说完就从怀里拿出一颗天王保命丸塞进嘴里嚼了起来。\n"NOR);
        say( HIC"片刻之间，铁传甲又恢复了精神，“嘿嘿”奸笑了两声。\n"NOR);
        revive();
        set("eff_qi", query("max_qi"));
        set("qi", query("max_qi"));
        set("eff_jing", query("max_jing"));
        set("jing", query("max_jing"));
        set("jingli", query("eff_jingli"));
        set("neili", query("max_neili"));
	remove_all_enemy(1);
	lost();
}

void die()
{
        unconcious();
}

