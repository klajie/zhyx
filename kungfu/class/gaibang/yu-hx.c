// gaibang npc code

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("余洪兴", ({"yu hongxing", "yu", "hongxing"}));
        set("title", "丐帮八袋弟子");
        set("gender", "男性");
        set("age", 30);
        set("long", 
                "这是位笑眯眯的丐帮八袋弟子，生性多智，外号小吴用。\n");
        set("attitude", "peaceful");
         set("rank", 8);
        set("str", 22);
        set("int", 30);
        set("con", 24);
        set("dex", 22);

        set("qi", 1000);
        set("max_qi", 1000);
        set("jing", 530);
        set("max_jing", 530);
        set("neili", 1800);
        set("max_neili", 1800);
        set("jiali", 45);
        
        set("combat_exp", 550000);
        
        set_skill("force", 150); 
        set_skill("jiaohua-neigong", 150); 
        set_skill("unarmed", 140); 
        set_skill("changquan", 140); 
        set_skill("dodge", 140); 
        set_skill("feiyan-zoubi", 140); 
        set_skill("parry", 140); 
        set_skill("begging", 100); 
        set_skill("stealing", 30); 
        set_skill("checking", 80); 
        
        map_skill("force", "jiaohua-neigong");
        map_skill("unarmed", "changquan");
        map_skill("dodge", "feiyan-zoubi");
        
        create_family("丐帮", 19, "弟子");
        setup();

        carry_object("/d/gaibang/obj/budai")->set_amount(7);
        carry_object("/d/gaibang/obj/budai")->wear();
//      carry_object("/clone/weapon/gangdao")->wield();
}

void attempt_apprentice(object ob)
{
        if (ob->query("class")=="bonze") {
                if (ob->query("gender")=="女性")
                        command ("say 师太是是出家人，怎么能在本帮做叫化子呢？");
                return;
        }

        if( ob->query("int") < 25 ) return;

        if( ob->query("family/family_name") != "丐帮" )
        {
                if( ob->query("rank") > 1 ) {
                        command("say 本帮以忠义为先，可容不下你这种无信无义的家伙！\n");
                        return;
                }

                command("say 唉，本帮诚信为本，只有七公他老人家和我才特别收些聪明徒儿，");
                command("say 大家都要为长远着想啊！");
                ob->set("rank", 1); 
                command("recruit " + ob->query("id"));
                ob->set("title", "丐帮一袋弟子");
        } 
        else
        {
                ob->set_temp("title", ob->query("title"));
                command("recruit " + ob->query("id"));
                ob->set("title", ob->query_temp("title"));
                ob->delete_temp("title");
        }
}

#include "/kungfu/class/gaibang/promote.h"

