inherit NPC;
#include <ansi.h>

void create()
{
        set_name("成昆", ({ "cheng kun", "cheng" }) );
        set("title", "少林叛徒");
        set("nickname", HIR "霹雳手" NOR);
        set("gender", "男性");
        set("shen_type", 0);
        set("age", 65);
        set("long", "人称“霹雳手”成昆。\n");
        set("attitude", "peaceful");
        set("str", 36);
        set("con", 30);
        set("dex", 30);
        set("int", 28);

        set("max_qi", 5200);
        set("max_jing", 2600);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 80);

        set("combat_exp", 2400000);

        set_skill("unarmed", 240);
        set_skill("cuff", 240);
        set_skill("strike", 240);
        set_skill("sword", 260);
        set_skill("force", 260);
        set_skill("parry", 240);
        set_skill("dodge", 240);
        set_skill("hand", 240);
        set_skill("literate", 220);
        set_skill("damo-jian", 260);
        set_skill("hunyuan-yiqi", 260);
        set_skill("qishang-quan", 240);
        set_skill("pili-shou", 240);
        set_skill("shaolin-shenfa", 240);
        set_skill("martial-cognize", 200);

        map_skill("sword", "damo-jian");
        map_skill("parry", "qishang-quan");
        map_skill("force", "hunyuan-yiqi");
        map_skill("cuff", "qishang-quan");
        map_skill("hand", "pili-shou");
        map_skill("dodge", "shaolin-shenfa");

        prepare_skill("cuff", "qishang-quan");

        set_temp("apply/attack", 220);
        set_temp("apply/dodge", 220);
        set_temp("apply/parry", 200);
        set_temp("apply/damage", 150);
        set_temp("apply/unarmed_damage", 150);
        set_temp("apply/armor", 200);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "cuff.shang" :),
        }));             

        setup();
}
void init()
{       
        object ob;

        ::init();

        if (interactive(ob = this_player()) && ! is_fighting())
        {
                remove_call_out("killing");
                call_out("killing", 1, ob);
        }
}

void killing(object ob)
{       
        object me;
        object obj=this_object();

        me = this_player();
        if (! ob || environment(ob) != environment())
                return;
                switch(random(2))
        {
        case 0:
//                say(CYN "玄慈大喝道：你这魔教爪牙，还不速来受死！\n" NOR);    
        set("anti",me);
                me->kill_ob(obj);
                  kill_ob(me);
                break;
        case 1:
 //               say(CYN "玄慈大叹：哎，又一个送死的来了！\n" NOR);
                set("anti",me);
                  kill_ob(me);
                me->kill_ob(obj);
                break;
        }
}


void killed_enemy()
{
        if (objectp(query("anti")))
        {
                shout(HIR "\n【光明顶之战】" HIW "成昆：哎！" HIC + query("anti")->name() + HIW "维护魔教，不自量力，白白送了性命！\n" NOR );

        }
}


void die()
{
        if (objectp(query("anti")))
        {
                
                query("anti")->set_temp("skybook/tulong/guangmingding/chengkun",1);
 
     message_vision(HIR "\n罪大恶疾的成昆终于得到应有的下场！\n" NOR,
                                   this_object(),query("anti"));
if ( query("anti")->query_temp("skybook/tulong/guangmingding/shaolin") > 0  
        &&  query("anti")->query_temp("skybook/tulong/guangmingding/emei") > 0
        &&  query("anti")->query_temp("skybook/tulong/guangmingding/chengkun") > 0 
        &&  query("anti")->query_temp("skybook/tulong/guangmingding/kunlun") > 0 
        &&  query("anti")->query_temp("skybook/tulong/guangmingding/huashan") > 0 
        &&  query("anti")->query_temp("skybook/tulong/guangmingding/wudang") > 0  )
        {      
                shout(HIR "\n【光明顶之战】" HIW "明教弟子：" HIC + query("anti")->name() + HIW "在光明顶技压群雄，独力击退六大门派，救明教万千弟子于危难之中！\n" NOR );
                query("anti")->delete_temp("skybook/tulong/guangmingding");
                query("anti")->set("skybook/tulong/winguangming",1);
                        query("anti")->move(__DIR__"to_ding");

        }
                 destruct(this_object());
        }

::die();
}

