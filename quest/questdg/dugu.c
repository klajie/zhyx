inherit NPC;
#include <ansi.h>
#define QUESTGOODS_D(x)    ("/quest/questdg/quest/questgoods" + x)
#define QUESTDG_D(x)      ("/quest/questdg/quest/questdg" + x)
#define DGMSG_D      ("/quest/questdg/dugu-msg")

void greeting(object);
void init();
int give_quest();
int give_up();
void npc_dest(object);
void destory(object);
string time_period(int);

string* dg_msg = ({
"独孤求败笑呵呵的说：“",
"独孤求败慢慢踱着方步道：“",
"独孤求败低头想了想，说道：“",
"独孤求败满脸期待的说道：“",
"独孤求败微笑着道：“",
});

void create()
{
   set_name(HIW"独孤求败"NOR, ({ "dugu qiubai", "dugu", "qiubai" }));
   set("gender", "男性");
   set("age", 100);
   set("str", 50);
    set("dex", 50);
   set("per",20);
    set("con",3000);

   set("long",
"这是一个普普通通的老者，一袭粗布衣裳，\n"
"颏下一缕白须，神情详和。目光转动之间，\n"
"隐隐流露出一丝王者之气。\n");
set("combat_exp",15000000);

   set("inquiry", ([
          "任务" : "独孤求败叹了口气，道：“如今江湖上危机四伏，我正道人士还有很多事情要去做啊！”\n",
    ]) );

    set("qi",9900000);
    set("max_qi",9900000);
    set("jing",9900000);
    set("max_jing",9900000);
    set("neili",9000000);
    set("max_neili",9000000);
    set("jingli",9000000);
    set("max_jingli",9000000);
   setup();
    carry_object("/clone/weapon/changjian")->wield();
    carry_object("/clone/misc/cloth")->wear();
}

void init()
{
   object ob;

   ::init();

   if( interactive(ob = this_player()) && !is_fighting() )
   {
      remove_call_out("greeting");
      call_out("greeting", 2, ob);
   }        
   add_action("give_quest", "quest");
   add_action("give_up","giveup");
}

void greeting(object ob)
{

   if( !ob || environment(ob) != environment() ) return;
   if( ob->query("quest_dg"))
   {
        write("独孤求败对你微微一笑，道：“你的任务已经完成了吗？”\n");
      return;
   }
}

int give_quest()
{
    mapping questtemp,questgoods,questdg,skills;
    object ob,npc,thing;
    int exp,time,bonus,level,i,lev,lev1;
    string msg,dest,error,dgmsg,place;
        
    ob = this_player();
    exp = (int)ob->query("combat_exp");

    if( (ob->query("character") != "光明磊落") && (ob->query("character") != "狡黠多变"))  
    {
        write("独孤求败看了你一眼，道：“你本性杀气太重，跟我等相处日久必然格格不入，你还是另找他人去吧！”\n");
        return 1;
    }
    if( ob->query("shen") < 0)  
    {
        write("独孤求败对你冷冷道：“道不同，不相为谋，你还是请便罢！”\n");
        return 1;
    }
    if(exp < 1000)
    {
       write("独孤求败看了看你，轻抚白须，道：“江湖险恶，你还是先练好基本功吧。”\n");
        return 1;
    }
 
    if (mapp(ob->query("quest_dg")))
    {
        write("独孤求败拍了拍你的肩膀，呵呵笑道：“不要急，先将手头的做完再说。”\n");
        return 0;
    }
    if (mapp(ob->query("quest_hs")))
    {
        ob->delete("quest_hs");
        ob->delete_temp("quesths_times");
    }
   
    if((time()-ob->query_temp("questdg_giveup_time")) < 2)
    {
        write("不要急，慢一点嘛。\n");
        return 1;
    }
    if(random(4)+1)
    {
        if(exp <= 5000)         level = 0;
        else if(exp <= 22000)   level = 1;
        else if(exp <= 72000)   level = 2;
        else if(exp <= 170000)  level = 3;
        else if(exp <= 410000)  level = 4-random(2);
        else if(exp <= 800000)  level = 5-random(3);
        else if(exp <= 1500000) level = 6-random(3);
        else
        {
        if(random(6)==0||(exp>10000000&&random(3)==0))
               level = 8;                  //8就是专门杀clone NPC的任务
            else
                level = 7-random(3);
        }
if(wizardp(ob)) level = 0;
        questtemp = QUESTDG_D(level)->query_questdg(ob);
        if(level==8)
        {
            npc = new(CLASS_D("generate") + "/killed.c");
            NPC_D->place_npc(npc, ob->query("combat_exp") < 500000  ? ({ "大理一带", "终南山", "关外", "西域" }) :
                                  ob->query("combat_exp") < 800000 ? ({ "大理一带", "终南山", "西域" }) : ({"西域"}));
            NPC_D->set_from_me(npc, ob, 100);
            npc->add_temp("apply/attack", npc->query_skill("force") * (level - 1) / 15);
            npc->add_temp("apply/dodge", npc->query_skill("force") * (level - 1) / 15);
            npc->add_temp("apply/parry", npc->query_skill("force") * (level - 1) / 15);
            npc->add_temp("apply/damage", 5 + level * 7);
            npc->add_temp("apply/unarmed_damage", 5 + level * 7);
            npc->add_temp("apply/armor", 10 + level * 15);
            npc->set_temp("quester", ob->query("id"));
            NPC_D->random_move(npc);
            NPC_D->random_move(npc);
            NPC_D->random_move(npc);
            place = npc->query("place");
            npc->set("shen", -npc->query("combat_exp") / 2000);
            
            msg="独孤求败面色凝重道：“"+npc->name(1)+
                "居然又重现江湖，你速去除了这一害，\n此人可能会在"+
                place+"附近，慢了就找不到了。”\n",

            questtemp = ([
                "name" : npc->name(1),
                "id"   : npc->query("id"),
                "bonus": (100+random(41)),
                "type" :"杀",
                "level":level,
                "chinese_w":place,
                "where":npc->query("startroom"),
                "dgmsg":msg,
            ]);
            tell_object(ob,questtemp["dgmsg"]+"\n");
            ob->set("quest_dg",questtemp);

            return 1;
        }
        else
        {
                switch(questtemp["type"])
                {
                case "杀":
                        if(undefinedp(msg = questtemp["msg1"])||msg==""||random(2))
                        {
                                if(questtemp["race"])
                                        msg=DGMSG_D->query_dgmsg("宰",questtemp["name"]);
                                else
                                        msg=DGMSG_D->query_dgmsg("杀",questtemp["name"]);
                        }
                        break;
                case "寻":
                        if(undefinedp(msg = questtemp["msg"])||msg==""||random(2))
                                msg=DGMSG_D->query_dgmsg("寻",questtemp["name"]);
                        break;
                case "擒":
                        if(undefinedp(msg = questtemp["msg2"])||msg==""||random(2))
                        {
                                if(questtemp["race"])
                                        msg=DGMSG_D->query_dgmsg("捉",questtemp["name"]);
                                else
                                        msg=DGMSG_D->query_dgmsg("擒",questtemp["name"]);
                        }
                        break;
                case "送":
                        npc = new(CLASS_D("generate") + "/dg_receiver.c");
                        NPC_D->place_npc(npc, ob->query("combat_exp") < 500000  ? ({ "大理一带", "终南山", "关外", "西域" }) :
                                              ob->query("combat_exp") < 800000 ? ({ "大理一带", "终南山", "西域" }) : ({"西域"}));
                        NPC_D->set_from_me(npc, ob, 100);
                        npc->set_temp("quester", ob->query("id"));
                        NPC_D->random_move(npc);
                        NPC_D->random_move(npc);
                        NPC_D->random_move(npc);
                        place = npc->query("place");
                        thing = new(questtemp["object"]);
                        thing->set("send_to",npc->query("id"));
                        thing->set("send_from",query("id"));
                        thing->set("send_from_name",query("name"));
                        msg = dg_msg[random(5)]+"麻烦你帮我将"+thing->name(1)+"送至"+npc->name(1)+"处，"
                                                "他现在正在"+place+"，误了时间他可能就离开了。";
                        if (!thing->move(ob))
                        {
                                thing->move(environment());
                                message_vision("独孤求败将$N轻轻放在地上。\n",thing);
                         } else message_vision("独孤求败将$N交给$n。\n",thing,ob);
                         break;
                }
                questdg=([
                         "name":questtemp["name"],
                         "type":questtemp["type"],
                         "bonus":questtemp["bonus"],
                         "dgmsg":msg,
                ]);
        }
    }  
    tell_object(ob,questdg["dgmsg"]+"\n");
    questdg["level"]=level;
    ob->set("quest_dg",questdg);
    return 1;
}

int accept_object(object who, object ob)
{
   int exp, pot,level,bonus,time,times,i,quest_count,mar,score,weiwang;
   mapping questdg;
   string dest,msg;
   object gold;
   mixed special = 0;
        
   if(!(questdg =  who->query("quest_dg")) ||
      (questdg["type"] != "寻" && questdg["type"] != "擒" && questdg["type"] != "送"))
   {
      tell_object(who,"独孤求败看了看你，似乎不知道你是什么意思。\n");
      return notify_fail("独孤求败淡淡一笑，道：“我可不缺什么东西。”\n");
   }

   if( ob->name(1) != questdg["name"] || userp(ob))
   {
      tell_object(who,"独孤求败叹了口气，道：这并不是我想要的。\n");
      return notify_fail("独孤求败看着你，道：“你是不是再去找找看啊？”\n");
   }

   if(questdg["type"]=="送")
   {
      if (!ob->is_receipt() || ob->query("reply_to") != this_object()->query("id"))
      {
          write("独孤求败接过来一看，惊讶的说：“我不是叫你帮我送东西了么，你是不是记错了？”\n");
          return 0;
      }
   } 

   message_vision("$N将$n交给独孤求败。\n",who,ob);
   tell_object(who,"独孤求败点头微笑，其意颇为嘉许，道：“不错！不错！”\n");
   who->delete("quest_dg");
   destruct(ob);

   level = questdg["level"]+1;
   if((i=who->query_temp("questdg_times")) < 2)   i =10-i;
   else i = 1;
   if(who->query_temp("questdg_times")< 2)   
       exp=level*5+random((9-level)*(9-level))/2;
   else
       exp = level*questdg["bonus"]*156/(10*i*(10+random(5)));
   
   pot = exp/(3+random(3));
   score = random(exp/20);
   weiwang = random(exp/15);

   if (who->query_temp("questkh_times") + 1 > 200)
	mar = exp/5 + random(who->query_temp("questkh_times"));
   else mar = random(20);
   
   if(wizardp(who)||!random(10))
   {
      i=(exp/100+1);
      if(i>20) i=20;
       gold=new("/clone/money/gold");
       gold->set_amount(i);
       tell_object(who,"接着说道：“整日行走江湖，手头有点紧吧？！喏，拿点黄金做盘缠吧！”\n"
          HIW"\n你被奖励了 "+i+" 两黄金。\n");
       if(!gold->move(who))
       {
           message_vision("但是$N身上东西太重，黄金一下子掉到了地上。\n",who);
           gold->move(environment());
       }
       QUEST_D->bonus(who, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                             "weiwang" : weiwang, "score" : score, "percent" : 50 ]), 1);
   }
   else QUEST_D->bonus(who, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                              "weiwang" : weiwang, "score" : score ]), 1);

   who->add_temp("questdg_times",1);

   quest_count = who->query_temp("questdg_times");
   if (quest_count == 100)
   {
       msg = "$N高兴的放声长笑：“孺子可教，连着上百"
       "次任务都完成的平平稳稳，继续努力！”\n";
	special = 1;
	   } else
       if (quest_count == 200)
   { 
       msg = "$N笑的合不拢嘴，拍着你的头道：“真争气！两百"
       "次任务干得漂漂亮亮！”\n";
       special = "/d/shaolin/obj/puti-zi";
   } else
       if (quest_count == 500)
   {
       msg = "$N长身而已：“不简单，真是不简单！你接连五百"
       "次任务都无一疏漏，奇才，奇才啊！”\n";
       special = "/clone/misc/tianxiang";
   } else
       if (quest_count == 1000)
   {
       msg = "$N看了你半天才说道：“竟然连着上千次"
       "任务无一失手，真是百年难遇的天才啊！”\n";
       special = "/clone/gift/jiuzhuan";
   } else
       if ((quest_count % 10) == 0)
   {
       msg = "$N呵呵笑着：“你表现很不错啊，居然连着" +
       chinese_number(quest_count) +
       "次都没有失手，别忙着练，慢慢来。”\n";
   }
   if (special) {
       message_vision(msg, this_object(), who);
       QUEST_D->special_bonus(this_object(), who, special);
   }
   return 1;
}

int give_up()
{
    object ob,obj,room;
    mapping questdg;

    ob = this_player();

    if(mapp(questdg =  ob->query("quest_dg")))
    {
        write("你满脸羞惭，请求独孤求败取消自己的任务。\n");
        write("独孤求败和颜悦色地拍拍你的脑袋，道：“没关系，要继续努力啊！”\n");
        if(questdg["type"] == "送")
        {
            if(objectp(obj = questdg["obj"]))
            {
                if(obj->is_character())
                    message_vision("$N一跃而起，跑得无影无踪了。\n",obj);
                obj->move(environment(ob));
                destruct(obj);
                if(ob->query_temp("questdg_times") > 0)
                    ob->add_temp("questdg_times",-1);
            }
        }
        else if(questdg["type"] == "杀"&&questdg["level"] == 8)    //by llm
        {
            if(!(room = find_object(questdg["where"])) )
                room = load_object(questdg["where"]);

            if(objectp(obj = present(questdg["id"],room))
                &&obj->is_character()
                &&!userp(obj))
            {
                message_vision("$N哼了一声，转身走开了。\n",obj);
                obj->move("/d/wizard/prison");
                destruct(obj);
            }
            ob->set_temp("questdg_times",0);
        }
        else
            ob->set_temp("questdg_times",0);
    }
    else
        write("独孤求败和颜悦色地看着你，道：“没关系，你现在根本就没有任务啊！”\n");
    ob->delete("quest_dg");
    ob->set_temp("questdg_giveup_time",time());
    return 1;
}

string time_period(int timep)
{
   int t, d, h, m, s;
   string time;
   t = timep;
   s = t % 60;             t /= 60;
   m = t % 60;             t /= 60;
   h = t % 24;             t /= 24;
   d = t;
 
   if(d) time = chinese_number(d) + "天";
   else time = "";
 
   if(h) time += chinese_number(h) + "小时";
   if(m) time += chinese_number(m) + "分";
   time += chinese_number(s) + "秒";
   return time;
}

void destory(object ob)
{
   if(!ob)
      return;
   if(ob->is_character())
      message_vision("$N一跃而起，跑得无影无踪了。\n",ob);
   ob->move("/d/wizard/prison");
   destruct(ob);
   return ;
}
 
void npc_dest(object npc)
{
    if(!npc) return;
    if(npc->is_fighting()&&npc->query_temp("wait_times")<4)
    {
        npc->add_temp("wait_times",1);   //4次机会
        call_out("npc_dest",60,npc);     //再等一分钟
        return;
    }
    if(npc->is_character())
        message_vision("$N重重地哼了一声：“看来都是胆小鬼”，转身一晃，已不见了身影。\n",npc);
    npc->move("/d/wizard/prison");
    destruct(npc);
    return ;
}
