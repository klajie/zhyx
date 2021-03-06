
//擂台npc5

#include <ansi.h> 
inherit  __DIR__"leitai_npc";

void create()
{               
        set("level", 5); 
        set_name("王重阳", ({ "wang chongyang", "wang", "chongyang" }));
        set("long", @LONG
他就是全真教的开山祖师、首代掌教王重阳王
真人。他白须飘飘，宽袍缓袖，眉目清癯，颇
有些仙风道骨的味道。他本来一腔热血欲报效
国家力抗金兵，可惜朝廷腐败，于是便心灰意
冷，兼此时又从道德经中悟得了天地万物滋生
的大道，从而手创全真教。
LONG);
        set("title", "全真派开山祖师");
        set("nickname", HIW "中神通" NOR);
        set("age", 76);
        set("gender", "男性");
        set("class", "taoist");
        set("attitude", "peaceful");
        set("shen_type", 1);

        set("str", 33);
        set("int", 35);
        set("con", 38);
        set("dex", 33);
        set("max_qi", 8000);
        set("max_jing", 8000);
        set("neili", 10000);
        set("jingli", 8000);
        set("max_neili", 10000);
        set("max_jingli", 8000);
        set("jiali", 250);
        set("combat_exp", 5000000);
        set("score", 500000);

        set_skill("force", 400);
        set_skill("quanzhen-xinfa", 380);
        set_skill("xuanmen-neigong", 380);
        set_skill("unarmed", 380);
        set_skill("xiantian-gong", 400);
        set_skill("dodge", 380);
        set_skill("tianshan-feidu", 360);
        set_skill("jinyan-gong", 380);
        set_skill("parry", 380);
        set_skill("jinguan-yusuo", 380);
        set_skill("strike", 380);
        set_skill("chongyang-shenzhang", 360);
        set_skill("haotian-zhang", 380);
        set_skill("finger", 380);
        set_skill("zhongnan-zhi", 360);
        set_skill("yiyang-zhi", 380);
        set_skill("hand", 380);
        set_skill("qixing-shou", 380);
        set_skill("sword", 380);
        set_skill("qixing-jian", 360);
        set_skill("tonggui-jian", 360);
        set_skill("quanzhen-jian", 380);
        set_skill("whip", 340);
        set_skill("tiangang-chenfa", 340);
        set_skill("jingluo-xue", 300);
        set_skill("taoism", 400);
        set_skill("literate", 340);
        set_skill("martial-cognize", 400);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jian");
        map_skill("whip", "tiangang-chenfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "jinguan-yusuo");
        map_skill("unarmed", "xiantian-gong");
        map_skill("finger", "yiyang-zhi");
        map_skill("strike", "haotian-zhang");
        map_skill("hand", "qixing-shou");

        prepare_skill("unarmed", "xiantian-gong");      

        create_family("全真教", 1, "掌教");

        set("chat_chance_combat", 120);       
       
        // npc的pfm
        set("pfm", ({
             "sword.bihai", 
             "sword.qing",
             "finger.ding",           
         }));
        //npc的兵器
        set("weapon","/clone/weapon/changjian");       

     //   if (! clonep()) return; 
        setup(); 
        restore();
        carry_object("/d/city/npc/obj/jinsijia")->wear();
   /*     if ( ! restore() )
        {
              carry_object("/d/city/npc/obj/jinsijia")->wear();
              if ( query("weapon") )
              carry_object(query("weapon"))->wield();  
        } */
}


