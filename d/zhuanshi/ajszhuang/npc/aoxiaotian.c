// by yuchang

#include <ansi.h>

inherit NPC;
void create()
{
        set_name("傲啸天", ({ "ao xiaotian", "ao", "xiaotian"}));
        set("title", HIY "傲剑山庄右圣" NOR);
        set("long",
"傲啸天长得并不帅气，团团的一张圆脸，皮肤稍微有点发黑，但是骨架很大，身上的威风很足，
一对眼睛极其有神，时雍容华贵，自有一副端严之致，令人肃然起敬，不敢逼视。\n");
        set("gender", "男性");
        set("age", 45);
        set("attitude", "peaceful");
        set("shen", -200000);
        set("per", 30);
        set("str", 35);
        set("int", 25);
        set("con", 25);
        set("dex", 30);

        set("max_qi", 10000);
        set("max_jing", 10000);
        set("max_neili", 20000);
        set("neili", 20000);
        set("jiali", 500);
        set("combat_exp", 5000000+random(10000));
        set("score", 20000);

        set_skill("dodge", 600);
        set_skill("unarmed", 600);
        set_skill("force", 600);
        set_skill("parry", 600);
        set_skill("sword", 600);
        set_skill("poison", 600);
        set_skill("medical", 600);
        set_skill("hand", 600);
        set_skill("strike", 600);
        set_skill("staff", 600);
        set_skill("finger", 600);
        set_skill("claw", 600);
        set_skill("blade", 600);
        set_skill("pixie-jian", 600);
        set_skill("literate", 600);
        set_skill("taoism", 600);
        set_skill("buddhism", 600);
        set_skill("jiuyang-shengong", 600);
        set_skill("lingbo-weibu", 600);
        set_skill("qiankun-danuoyi", 600);
        set_skill("xuanming-zhang", 600);
        set_skill("jiuyin-baiguzhao", 600);
        set_skill("dugu-jiujian", 600);
        set_skill("liumai-shenjian", 600);
        set_skill("qianzhu-wandushou", 600);
        set_skill("ranmu-daofa", 600);
        set_skill("dagou-bang", 600);
        set_skill("shaolin-yishu", 600);
        set_skill("wudu-qishu", 600);
        set_skill("throwing", 600);
        set_skill("mantian-xing", 600);
        set_skill("idle-force", 600);

        map_skill("unarmed", "pixie-jian");
        map_skill("force", "jiuyang-shengong");
        map_skill("dodge", "lingbo-weibu");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("hand", "qianzhu-wandushou");
        map_skill("strike", "xuanming-zhang");
        map_skill("claw", "jiuyin-baiguzhao");
        map_skill("finger", "six-finger");
        map_skill("sword", "dugu-jiujian");
        map_skill("blade", "ranmu-daofa");
        map_skill("staff", "dagou-bang");
        map_skill("throwing", "mantian-xing");
        map_skill("poison", "wudu-qishu");
        map_skill("medical", "shaolin-yishu");

        prepare_skill("finger", "liumai-shenjian");  

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.po" :),
                (: perform_action, "blade.zhenyan" :),
                (: perform_action, "blade.huo" :),
                (: perform_action, "staff.wugou" :),
                (: perform_action, "staff.chan" :),
                (: perform_action, "staff.ban" :),
                (: perform_action, "unarmed.cimu" :),
                (: perform_action, "parry.nuoyi" :),
                (: perform_action, "dodge.lingbo" :),
                (: perform_action, "throwing.shan" :),
                (: perform_action, "hand.zhugu" :),
                (: perform_action, "strike.wuji" :),
                (: perform_action, "finger.six" :),
                (: perform_action, "finger.zhongheng" :),
                (: perform_action, "claw.zhua" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),
        }));        

        setup();
        carry_object(__DIR__"obj/changjian")->wield();
        carry_object(__DIR__"obj/female2-cloth")->wear();
}
void init()
{       
        object me;
        string id;
        me = this_player();      

        command("chat 大胆，谁人胆敢擅闯本庄禁地!");
        command("say 居然能过了我兄弟那一关，看来你有几下子。"); 
        command("say 接招吧！");   
        kill_ob(me);
        this_object()->set("now_killing", me);
      
}

void unconcious() 
{ 
        object ob, killer;
        ob = this_object();
        killer = ob->query("now_killing");
        
        command("chat 想不到我们兄弟二人尽皆败于你手！");
        command("chat 罢了罢了，看来绝世好剑是注定要落入你手了！");
        tell_room(environment(ob), "\n傲啸天一晃，变为一缕轻烟消失了。\n\n"); 
        killer->set_temp("reborn_start/ao2",1);  
        destruct(ob);  
} 



