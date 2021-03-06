#include "/kungfu/class/emei/emei.h"
#include <ansi.h>

inherit NPC;
inherit F_MASTER;

string ask_ml();
string ask_meinv();
string ask_gf09tangyuan();
string ask_childgift();
string ask_ydgift();



void create()
{
        set_name("狼纤纤", ({ "wolfmm","wolf","mm"}));
        set("nickname", HIG "儿童节大使" NOR);
        set("long", HIR "她是狼族的圣女，杨六狼的徒弟。哪个泡上她就傍上大巫师啦\n");
        set("gender", "女性");
        set("age", 20);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "fighter");

        set("str", 100);
        set("int", 22);
        set("con", 21);
        set("dex", 19);
        set("per",40);
        
        set("vendor_goods", ({
                "/u/dgdg/book/secretbook.c",      
        }));

        set("max_qi", 1200);
        set("max_jing", 600);
        set("neili", 1500);
        set("max_neili", 1500);
        set("combat_exp", 70000);

        set_skill("force", 120);
        set_skill("emei-xinfa", 120);
        set_skill("dodge", 100);
        set_skill("zhutian-bu", 100);
        set_skill("strike", 100);
        set_skill("sixiang-zhang", 100);
        set_skill("jinding-zhang", 100);
        set_skill("parry", 100);
        set_skill("blade", 100);
        set_skill("yanxing-dao", 100);
        set_skill("literate", 100);
        set_skill("mahayana", 100);
        set_skill("buddhism", 100);
        set_skill("martial-cognize", 20);

        map_skill("force","emei-xinfa");
        map_skill("dodge","zhutian-bu");
        map_skill("strike", "jinding-zhang");
        map_skill("blade", "yanxing-dao");
        map_skill("parry","yanxing-dao");

        prepare_skill("strike", "jinding-zhang");

        create_family("狼族", 2, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.huan" :),
                (: perform_action, "strike.bashi" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));


set("inquiry", ([ 
                //    "美女" : (: ask_meinv :),                   
                  //  "汤圆" : (: ask_gf09tangyuan :),
                      "节日礼物" :(: ask_childgift :), 
               //     "makelove"  : (: ask_ml :),
                  //  "make love" : (: ask_ml :), 
                  //    "元旦礼物"  : (: ask_ydgift() :),                                
                ]));    

        setup();

        carry_object("/d/city/obj/gangdao")->wield();
        carry_object("/d/city/obj/cloth.c")->wear();
}

void init()
{
     object me;
     ::init();

        add_action("do_list", "list");
        add_action("do_buy", "buy");
        
       

}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("say 好吧，我就收下你了。");
        command("recruit " + ob->query("id"));
}


                
                
string ask_ydgift()
{
        object me;
        object ob;

        me = this_player();
        if (me->query("gift2010_yd/get") >= 2 )
      
        {
            return "吃这么多了还要,想死啊!要了还想要啊？真贪心，没有啦！！\n";
        }      
                
        message_vision(HIY "$N拿出一个冒着香气的汉堡递给$n。\n" NOR, this_object(), me);

        ob = new("/u/dgdg/obj/hanbao2.c");
        ob->move(me, 1);
        me->add("gift2010_yd/get", 1);

        return "好吧，这个汉堡你拿去吃吧。祝你元旦快乐!\n";
      }
           
                
                
                
                
                
                
                
string ask_gf09tangyuan()
{
        object me;
        object ob;

        me = this_player();
        if (me->query("gf09tangyuan/get") >= 3 )
      
        {
            return "吃这么多了还要,想死啊!要了还想要啊？真贪心，没有啦！！\n";
        }      
                
        message_vision(HIY "$N拿出一个又圆又大的汤圆递给$n。\n" NOR, this_object(), me);

        ob = new("/u/dgdg/obj/tangyuan");
        ob->move(me, 1);
        me->add("gf09tangyuan/get", 1);

        return "好吧，这个汤圆你拿去吃吧。\n";
      }
      
      string ask_childgift()
{
        object me;
        object ob;

        me = this_player();
       /*  me->add("childgift/yao",1);
        if (me->query("childgift/yao") >= 1 )
      
        {
            return "要了还想要啊？真贪心，没有啦！！小孩子要诚实哦。\n";
      }      
                
        message_vision(HIY "$N拿出一个又圆又大的蛋递给$n。\n" NOR, this_object(), me);

        ob = new("/u/dgdg/obj/childgift");
        ob->move(me, 1);
        me->add("gf09tangyuan/get", 1);

        return "好吧，这个礼物你就拿去吧。\n";
            }
      
string ask_ml()
{
//object me;
//me = this_player();
return "非礼啊!你这个大色狼,我会告诉狼神大人的,你等着瞧!\n";

}

string ask_meinv()
{
//object me;
//me = this_player();
return "好吧,看你这么乖,赏你一个大汤圆吃\n";
}


void unconcious()
{
        say( HIC"狼纤纤说道：“想搞我没那么容易。”说完就从怀里拿出一颗天王保命丸塞进嘴里嚼了起来。\n"NOR);
        say( HIC"片刻之间，狼纤纤又恢复了精神，“嘿嘿”奸笑了两声。\n"NOR);
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

varargs int receive_damage(string type, int n, object who)
{
        if (! objectp(who) || ! interactive(who) || who == this_object())
                return 0;

        tell_object(who, HIR "你发现" + name() +
                    HIR "诡秘一笑，忽然觉得一阵心悸，神智一阵恍惚。\n" NOR);
        return who->receive_damage(type, n, this_object());
}

varargs int receive_wound(string type, int n, object who)
{
        if (! objectp(who) || ! interactive(who) || who == this_object())
                return 0;

        tell_object(who, RED "你忽见" + name() +
                    RED "桀桀怪笑，只觉得浑身都是一痛，直入骨髓深处。\n" NOR);
        return who->receive_wound(type, n, this_object());
}
}