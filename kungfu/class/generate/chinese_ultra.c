// chan_cler 中国挑战者

inherit NPC;


private void from_wudang_sp();
private void from_shaolin_sp();
private void from_huashan_sp();
private void from_ouyang_sp();
private void from_gaibang_sp();
private void from_taohua_sp();
private void from_gumu_sp();
private void from_xingxiu_sp();
private void from_hu_sp();
private void from_xiaoyao_sp();
private void from_kunlun_sp();
private void from_lingxiao_sp();
private void from_tiezhang_sp();
private void from_mingjiao_sp();
private void from_murong_sp();


function *init_family = ({ 
	(: from_wudang_sp :), (: from_shaolin_sp :),	(: from_huashan_sp :), (: from_ouyang_sp :),(:from_mingjiao_sp():),
			   (: from_gaibang_sp :),(: from_taohua_sp :),	(: from_gumu_sp :),(: from_xingxiu_sp :),(: from_tiezhang_sp :),
			   (: from_hu_sp :),(: from_xiaoyao_sp :),(: from_kunlun_sp :),(: from_murong_sp :),(: from_lingxiao_sp :),});

void create()
{
        NPC_D->generate_cn_name(this_object());
        set("long", "一个人。\n");
        set("gender", "男性");
        set("age", 20);
        set("str", 20);
        set("int", 13);
        set("con", 20);
        set("dex", 20);

        // the follow 5 setting has no use      
        set("max_qi", 100);
        set("max_jing", 100);
        set("neili", 100);
        set("max_neili", 100);
        set("jiali", 100);

        set("combat_exp", 3000000);

        setup();

        evaluate(init_family[random(sizeof(init_family))]);
}



private void from_wudang_sp()
{
        set("scale", 200);
        set("from", ({
                "据说此人出自武当，是武当派的高手，然而修武不修德，可惜啊可惜。",
                "听闻此人本是武当山下一农夫，耳渎目染，居然练就成非凡武功。",
                "据说此人乃武当弃徒，当年犯了杀戒逃至东洋，不想今日返回中原！",
        }));

        set_skill("force", 1);
        set_skill("taiji-shengong", 1);
        set_skill("parry", 1);
        set_skill("dodge", 1);
        set_skill("tiyunzong", 1);
        set_skill("sword", 1);
        set_skill("taiji-jian", 1);
        set_skill("hand", 1);
        set_skill("lonely-sword", 1);
        set_skill("unarmed", 1);
        set_skill("taiji-quan", 1);
        set_skill("literate", 1);
        set_skill("martial-cognize", 1);
        set_skill("taoism", 1);
		set_skill("count", 1);
        set_skill("shexing-lifan", 1);

        map_skill("parry", "taiji-jian");
        map_skill("force", "taiji-shengong");
        map_skill("dodge", "shexing-lifan");
        map_skill("sword", "lonely-sword");
        map_skill("hand", "paiyun-shou");
        map_skill("unarmed", "taiji-quan");

        prepare_skill("hand", "paiyun-shou");
        prepare_skill("unarmed", "taiji-quan");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.luo" :),    
                (: perform_action, "sword.liao" :),     
                (: perform_action, "sword.dang" :),
                (: perform_action, "sword.jie" :),
				(: perform_action, "sword.9in1" :),  
                (: perform_action, "sword.li" :),   				  
                (: exert_function, "recover" :),
        }) );

        set("class", "taoist");

        carry_object("/clone/weapon/green_sword")->wield();
        carry_object("/d/wudang/obj/greyrobe")->wear();
}


private void from_shaolin_sp()
{
        set("scale", 150);
        set("from", ({
                "据说此人出自少林，是少林的俗家高手，可却没有半点慈悲之心，唉！",
                "听闻此人偷师于少林，练就了一身超凡脱俗的本领。",
                "据说此人乃少林的火工头陀，偷学武艺后被发现，竟然打死"
                + "达摩院长老出逃西域，想不到今日返回中原！",
                "据说此人当年犯了少林的戒律，被迫离寺，想不到隐居多年"
                + "以后居然重出江湖。"
        }));

		set("can_perform/lunhui-jian/chushengdao",1);
		set("can_perform/lunhui-jian/rendao",1);
		set("can_perform/lunhui-jian/tiandao",1);
		set("can_perform/lunhui-jian/eguidao",1);
		set("can_perform/lunhui-jian/xiuluodao",1);
		set("can_perform/lunhui-jian/diyudao",1);

        set_skill("force", 1);
        set_skill("yijinjing", 1);
        set_skill("parry", 1);
        set_skill("dodge", 1);
        set_skill("yiwei-dujiang", 1);
        set_skill("sword", 1);
        set_skill("lunhui-jian", 1);
        set_skill("unarmed", 1);
        set_skill("jingang-buhuaiti", 1);
        set_skill("literate", 1);
        set_skill("martial-cognize", 1);
        set_skill("buddhism", 1);
		set_skill("jiasha-fumogong", 1);
        set_skill("shexing-lifan", 1);

        map_skill("parry", "jingang-buhuaiti");
        map_skill("force", "yijinjing");
        map_skill("dodge", "shexing-lifan");
        map_skill("sword", "lunhui-jian");
        map_skill("unarmed", "jiasha-fumogong");

        prepare_skill("unarmed", "jiasha-fumogong");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.hui" :),
        }) );

        set("class", "bonze");
        carry_object("/clone/weapon/green_sword")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

private void from_huashan_sp()
{
        set("scale", 130);
        set("from", ({
                "据说此人出自华山，无恶不作，后来行迹忽然不见，想不到今日又出头。",
                "听闻此人本是华山长老，因剑气之争远投异地，不知何故返回中原！",
                "据说此人本是别派卧底到华山去的，偷学本领以后没回本派"
                + "反而觅地苦修，今日终于得出江湖。",
        }));

        set_skill("force", 1);
        set_skill("zixia-shengong", 1);
        set_skill("parry", 1);
        set_skill("dodge", 1);
        set_skill("feiyan-huixiang", 1);
        set_skill("sword", 1);
        set_skill("huashan-sword", 1);
        set_skill("dugu-jiujian", 1);
        set_skill("cuff", 1);
        set_skill("poyu-quan", 1);
        set_skill("strike", 1);
        set_skill("lonely-sword", 1);
        set_skill("literate", 1);
        set_skill("martial-cognize", 1);
        set_skill("shexing-lifan", 1);

        map_skill("parry", "dugu-jiujian");
        map_skill("force", "zixia-shengong");
        map_skill("dodge", "shexing-lifan");
        map_skill("sword", "lonely-sword");
        map_skill("cuff", "poyu-quan");
        map_skill("strike", "hunyuan-zhang");

        prepare_skill("cuff", "poyu-quan");
        prepare_skill("strike", "hunyuan-zhang");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.luo" :),    
                (: perform_action, "sword.liao" :),     
                (: perform_action, "sword.dang" :),
                (: perform_action, "sword.jie" :),
				(: perform_action, "sword.9in1" :),  
                (: perform_action, "sword.li" :),   	
                (: exert_function, "recover" :),
        }) );

        set("class", "fighter");

        carry_object("/clone/weapon/green_sword")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

private void from_ouyang_sp()
{
        set("scale", 130);
        set("from", ({
                "据说此人原是当今武林宗师欧阳锋的兄长，不知何故失踪，今"
                + "日居然又出现了。",
                "听闻此人偷学了西域白驼山庄欧阳世家的武功，后来被欧阳"
                + "锋发现打成重伤，此人带伤而走，竟然活到今日，不可思议！",
        }));

        set_skill("force", 1);
        set_skill("jiuyin-shengong", 1);
        set_skill("parry", 1);
        set_skill("dodge", 1);
        set_skill("qiankun-danuoyi", 1);
        set_skill("staff", 1);
        set_skill("lingshe-zhangfa", 1);
        set_skill("cuff", 1);
        set_skill("lingshe-quan", 1);
        set_skill("unarmed", 1);
        set_skill("dafumo-quan", 1);
        set_skill("literate", 1);
        set_skill("martial-cognize", 1);
        set_skill("shexing-lifan", 1);
		set_skill("zuoyou-hubo", 1);

        map_skill("force", "jiuyin-shengong");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("dodge", "shexing-lifan");
        map_skill("unarmed", "jiuyin-shengong");


        prepare_skill("unarmed", "jiuyin-shengong");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
			    (: command("perform unarmed.quan twice") :),
                (: exert_function, "recover" :),
        }) );

        carry_object("/clone/cloth/cloth")->wear();
}

private void from_gaibang_sp()
{
        set("scale", 120);
        set("from", ({
                "据说此人原是丐帮长老，武功高绝，后因欺辱良家女子而被"
                + "逐出帮外，今日重现江湖比如又起血雨腥风。"
        }));

        set_skill("force", 1);
        set_skill("huntian-qigong", 1);
        set_skill("parry", 1);
        set_skill("dodge", 1);
        set_skill("feiyan-zoubi", 1);
        set_skill("staff", 1);
        set_skill("qiankun-danuoyi", 1);
        set_skill("strike", 1);
        set_skill("xianglong-zhang", 1);
        set_skill("literate", 1);
        set_skill("martial-cognize", 1);
        set_skill("shexing-lifan", 1);
		set_skill("count", 1);

        map_skill("force", "huntian-qigong");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("dodge", "shexing-lifan");
        map_skill("staff", "dagou-bang");
        map_skill("strike", "xianglong-zhang");

        prepare_skill("strike", "xianglong-zhang");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "strike.tian" :),
        }) );

        set("class", "begger");
   
        carry_object("/clone/cloth/cloth")->wear();
}


private void from_taohua_sp()
{
        object ob;

        set("scale", 135);
        set("from", ({
                "据说此人和桃花岛主黄药师有些关系。",
        }));

        set_skill("force", 1);
        set_skill("bibo-shengong", 1);
		set_skill("bihai-chaosheng", 1);
		set_skill("dodge", 1);
        set_skill("anying-fuxiang", 1);
        set_skill("finger", 1);
        set_skill("throwing", 1);
        set_skill("tanzhi-shentong", 1);
        set_skill("parry", 1);
        set_skill("sword", 1);
        set_skill("never-defeated", 1);
        set_skill("qimen-wuxing", 1);
        set_skill("count", 1);
        set_skill("jingluo-xue", 1);
        set_skill("mathematics", 1);
        set_skill("literate", 1);
        set_skill("martial-cognize", 1);
        set_skill("shexing-lifan", 1);

        map_skill("force", "never-defeated");
        map_skill("finger", "tanzhi-shentong");
        map_skill("dodge", "shexing-lifan");
        map_skill("parry", "never-defeated");
        map_skill("sword", "never-defeated");
        map_skill("throwing", "tanzhi-shentong");

        prepare_skill("finger" , "tanzhi-shentong");

        set("chat_chance_combat", 180);
	    set("chat_msg_combat", ({
		(: perform_action, "sword.juemie" :),
		(: perform_action, "sword.wanli" :),
	    (: perform_action, "sword.lei" :),
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
	}));
        carry_object("/clone/weapon/green_sword")->wield();
        carry_object("/clone/misc/cloth")->wear();
        ob = carry_object("/d/taohua/obj/huaban");
        ob->set_amount(80);
        set_temp("handing", ob);
}


private void from_gumu_sp()
{
        object ob;

        set("scale", 130);
        set("from", ({
                "据说此人是林朝英的弟子，被她逐出师门了。",
                "这人据说是古墓传人，和李莫愁颇有渊源。",
        }));

        set_skill("force", 1);
        set_skill("surge-force", 1);
        set_skill("parry", 1);
        set_skill("dodge", 1);
        set_skill("zhuangzi-wu", 1);
        set_skill("unarmed", 1);
        set_skill("sad-strike", 1);
        set_skill("strike", 1);
        set_skill("qiankun-danuoyi", 1);
        set_skill("tianluo-diwang", 1);
        set_skill("throwing", 1);
        set_skill("yufeng-zhen", 1);
        set_skill("sword", 1);
        set_skill("yunv-jian", 1);
        set_skill("quanzhen-jian", 1);
        set_skill("literate", 1);
        set_skill("martial-cognize", 1);
		set_skill("zuoyou-hubo", 1);

        map_skill("force", "surge-force");
        map_skill("sword", "yunv-jian");
        map_skill("dodge", "zhuangzi-wu");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("unarmed", "sad-strike");
        map_skill("strike", "tianluo-diwang");
        map_skill("throwing", "yufeng-zhen");

        prepare_skill("unarmed", "sad-strike");
        prepare_skill("strike", "tianluo-diwang");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({    
                  (: command("perform unarmed.tuo twice") :),
        }) );

        carry_object("/clone/misc/cloth")->wear();
        ob = carry_object("/d/gumu/obj/yufeng-zhen");
        ob->set_amount(30);
        set_temp("handing", ob);
}

private void from_xingxiu_sp()
{
        set("scale", 130);
		set("reburn", 1);
        set("from", ({
                "据说此人是星宿派弟子，因为得罪了老仙，只好逃出星宿派。",
        }));

        set_skill("force", 1);
        set_skill("kuihua-mogong", 1);
        set_skill("dodge", 1);
        set_skill("zhaixinggong", 1);
        set_skill("strike", 1);
        set_skill("chousui-zhang", 1);
        set_skill("claw", 1);
        set_skill("sanyin-wugongzhao", 1);
        set_skill("whip", 1);
        set_skill("chanhun-suo", 1);
        set_skill("parry", 1);
        set_skill("staff", 1);
        set_skill("tianshan-zhang", 1);
        set_skill("throwing", 1);
        set_skill("feixing-shu", 1);
        set_skill("unarmed", 1);
        set_skill("xingxiu-qishu", 1);
        set_skill("literate", 1);
        set_skill("martial-cognize", 1);

        map_skill("force", "kuihua-mogong");
        map_skill("dodge", "kuihua-mogong");
        map_skill("unarmed", "kuihua-mogong");
		map_skill("sword", "kuihua-mogong");
        map_skill("claw", "sanyin-wugongzhao");
        map_skill("whip", "chanhun-suo");
        map_skill("parry", "kuihua-mogong");
        map_skill("staff", "tianshan-zhang");
        map_skill("poison", "xingxiu-qishu");

        prepare_skill("unarmed", "kuihua-mogong");


        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.bian" :),
                (: perform_action, "sword.wswd" :),
                (: perform_action, "sword.dongfang" :),
        }));

        carry_object("/clone/weapon/green_sword")->wield();
        carry_object("/clone/misc/cloth")->wear();
}


private void from_hu_sp()
{
        object ob;
        set("scale", 135);
		set("reburn", 1);
        set("from", ({
                "据说此人和西域雪山飞狐有说不清的关系。",
        }));

        set_skill("force", 1);
        set_skill("lengyue-shengong", 1);
        set_skill("blade", 1);
        set_skill("dodge", 1);
        set_skill("sword", 1);
        set_skill("qiankun-danuoyi", 1);
        set_skill("zhuangzi-wu", 1);
        set_skill("cuff", 1);
        set_skill("daojian-guizhen", 1);
        set_skill("parry", 1);
        set_skill("lamaism", 1);
        set_skill("literate", 1);
        set_skill("martial-cognize", 1);

        map_skill("force", "lengyue-shengong");
        map_skill("dodge", "zhuangzi-wu");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("blade", "daojian-guizhen");
	    map_skill("sword", "daojian-guizhen");


        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "blade.tian" :),
                (: exert_function, "recover" :),
        }));

        set("class", "bonze");

        carry_object("/clone/weapon/tudao")->wield();
        carry_object("/clone/misc/cloth")->wear();		      
		ob = carry_object("/clone/weapon/green_sword");       
        set_temp("handing", ob);
}


private void from_xiaoyao_sp()
{
        set("scale", 135);
        set("from", ({
                "据说此人和逍遥派无崖子本是同门弟子，后来不知何故翻脸成仇。",
        }));

        set_skill("force", 1);
        set_skill("beiming-shengong", 1);
        set_skill("dodge", 1);
        set_skill("lingbo-weibu", 1);
        set_skill("liuyang-zhang", 1);
        set_skill("parry", 1);
        set_skill("sword", 1);
        set_skill("liuyue-jian", 1);
        set_skill("zhemei-shou", 1);
        set_skill("hand", 1);
		set_skill("finger", 1);
		set_skill("liumai-shenjian", 1);
        set_skill("strike", 1);
        set_skill("literate", 1);
		set_skill("count", 1);
        set_skill("martial-cognize", 1);
	    set_skill("jinzhong-zhao", 1);

        map_skill("force", "beiming-shengong");
        map_skill("dodge", "lingbo-weibu");
        map_skill("finger", "liumai-shenjian");
        map_skill("strike", "liuyang-zhang");
        map_skill("parry", "jinzhong-zhao");

        prepare_skill("finger","liumai-shenjian");


        set("class", "taoist");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "finger.six" :),
                (: perform_action, "finger.zong" :),

        }));

        carry_object("/clone/misc/cloth")->wear();
}


private void from_kunlun_sp()
{
        set("scale", 135);
        set("from", ({
                "此人衣着奇异，不同于一般中土人氏，据说他与昆仑派甚有渊源。",
        }));

        set_skill("force", 1);
        set_skill("liangyi-shengong", 1);
        set_skill("dodge", 1);
        set_skill("zhuangzi-wu", 1);
        set_skill("strike", 1);
        set_skill("tanqin-jifa", 1);
	    set_skill("chess", 1);
        set_skill("cuff", 1);
        set_skill("zhentian-quan", 1);
        set_skill("parry", 1);
        set_skill("sword", 1);
        set_skill("daya-jian", 1);
        set_skill("qiankun-jian", 1);
        set_skill("qiuyue-lai", 1);
        set_skill("martial-cognize", 1);
        set_skill("jinzhong-zhao", 1);

        map_skill("force", "liangyi-shengong");
        map_skill("dodge", "zhuangzi-wu");
        map_skill("parry", "jinzhong-zhao");
        map_skill("sword", "daya-jian");
        map_skill("tanqin-jifa", "jian-jia");

        prepare_skill("cuff", "zhentian-quan");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.bugui" :),

        }));

        carry_object("/clone/weapon/green_sword")->wield();
        carry_object("/clone/misc/cloth")->wear();
}



private void from_lingxiao_sp()
{
        set("scale", 140);
		set("reburn", 1);
		set("can_perform/xueshan-jian/times", 1000000);
        set("from", ({
                "此人乃大雪山凌宵城高手，后因派中事变，故离派而去。",
        }));

        set_skill("force", 1);
        set_skill("taixuan-gong", 1);
        set_skill("dodge", 1);
        set_skill("qiankun-danuoyi", 1);
        set_skill("unarmed", 1);
        set_skill("lingxiao-quan", 1);
        set_skill("zhuangzi-wu", 1);
        set_skill("piaoxu-zhang", 1);
        set_skill("sword", 1);
        set_skill("shangqing-jian", 1);
        set_skill("parry", 1);
        set_skill("literate", 1);
		set_skill("xueshan-jian", 1);
		set_skill("shangqing-jian", 1);
        set_skill("martial-cognize", 1);

        map_skill("force", "taixuan-gong");
        map_skill("dodge", "qiankun-danuoyi");
        map_skill("unarmed", "taixuan-gong");
        map_skill("strike", "piaoxu-zhang");
        map_skill("sword", "xueshan-jian");
        map_skill("parry", "qiankun-danuoyi");

        prepare_skill("unarmed", "taixuan-gong");


        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.chu" :),
			    (: perform_action, "sword.feng" :),
        }));

        carry_object("/clone/weapon/green_sword")->wield();
        carry_object("/clone/misc/cloth")->wear();
}

private void from_tiezhang_sp()
{
        set("scale", 120);
        set("from", ({
                "此人乃铁掌帮麻衣长老，受裘千仞之托下山滋事。",
        }));

        set_skill("force", 1);
        set_skill("tianlei-shengong", 1);
        set_skill("dodge", 1);
        set_skill("dengping-dushui", 1);
        set_skill("strike", 1);
        set_skill("parry", 1);
        set_skill("tie-zhang", 1);
        set_skill("feilong-zhang", 1);
        set_skill("hand", 1);
	    set_skill("qiankun-danuoyi", 1);		
        set_skill("literate", 1);
        set_skill("martial-cognize", 1);

        map_skill("force", "tianlei-shengong");
        map_skill("strike", "tie-zhang");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("dodge", "dengping-dushui");
        map_skill("staff", "feilong-zhang");

        prepare_skill("strike", "tie-zhang");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "strike.juesha" :),
                (: perform_action, "strike.yin" :),

        }));

        carry_object("/clone/misc/cloth")->wear();
}


private void from_mingjiao_sp()
{
        set("scale", 120);
        set("from", ({
                "此人跟明教教主阳顶天有说不清道不明的关系。",
        }));

        set_skill("force", 1);
        set_skill("jiuyang-shengong", 1);
        set_skill("dodge", 1);
        set_skill("qingfu-shenfa", 1);
		set_skill("qiankun-danuoyi", 1);
        set_skill("unarmed", 1);
        set_skill("parry", 1);
        set_skill("literate", 1);
        set_skill("martial-cognize", 1);

        map_skill("force", "jiuyang-shengong");
        map_skill("unarmed", "jiuyang-shengong");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("dodge", "qingfu-shenfa");


        prepare_skill("unarmed", "jiuyang-shengong");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "unarmed.ri" :),

        }));

        carry_object("/clone/misc/cloth")->wear();
}



private void from_murong_sp()
{
        set("scale", 120);
        set("from", ({
                "此人跟慕容世家有说不清道不明的关系。",
        }));

        set_skill("force", 1);
        set_skill("zihui-xinfa", 1);
        set_skill("dodge", 1);
        set_skill("shexing-lifan", 1);
		set_skill("douzhuan-xingyi", 1);
        set_skill("finger", 1);
        set_skill("parry", 1);
        set_skill("literate", 1);
        set_skill("martial-cognize", 1);
		set_skill("liumai-shenjian", 1);
		set_skill("jingluo-xue", 1);
		set_skill("yiyang-zhi", 1);
		set_skill("lamaism", 1);
		set_skill("buddhism", 1);

        map_skill("force", "zihui-xinfa");
        map_skill("finger", "liumai-shenjian");
        map_skill("parry", "douzhuan-xingyi");
        map_skill("dodge", "shexing-lifan");


        prepare_skill("finger", "liumai-shenjian");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "finger.zong" :),
			    (: perform_action, "finger.six" :),

        }));

        carry_object("/clone/misc/cloth")->wear();
}