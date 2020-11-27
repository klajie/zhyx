//彩票登记员

#include <ansi.h>

inherit NPC;

int accept_ask(object me,string arg);

void create()

{
    set_name(HIC"瞎大笨"NOR, ({"xia daben", "daben", "dumb" }));
    set("title", HIW"［"HIG"彩票发放员"HIW"］"NOR);
    set("gender", "男性");
    setup();
}

void init()
{
     object me;
     ::init();

        if( interactive(me = this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }

}

void greeting(object ob)

{
     object me;
     me=this_player();
     if (!ob || !present(ob, environment())) return;

     command("say 请ask xia daben about 彩票");
   //  command("say 或者ask xia daben about 春节礼物");
       command("say 你是来捐献物品的吗?");
   
     return ;
}

int accept_ask(object me,string arg)
{
   object ob;
   int i;
   

    if ( me->query("age") < 20 ) 
   {
       write("对不起,年龄未到20岁的不能领取圣诞彩票！\n");
       return 1;
   }

   if ( arg == "彩票" || arg == "奖票") 
{
   if ( me->query_skill("martial-cognize") < 125 && me->query("age") < 30 ) 
   {
       write("武学修养不足250级且年龄不足30岁的不能参加本次抽奖！\n");
       return 1;
   }

   if ( me->query("gift2007/spring/get") ) 
   {
       write("你已经领过今年的春节彩票了呀！\n");
       return 1;
   }
  // me->delete("gift2005");
   me->set("gift2007/spring/get",1);  
   
   command("say 祝你新年进步节节高升！");
   ob = new("/u/sanben/yuanxiao/lot_card");
   ob->move(me);
   message_vision(HIC "$N" HIC "拿出一张抽奖彩票给$n。\n"NOR, this_object(), me);
   return 1;
}

    return 0;
}


int accept_object(object me, object ob) 
{ 
   
   if (base_name(ob) == ("/u/sanben/obj/fig"))
  {
      me->add("gift2007/x",2);
      if (me->query("gift2007/x") > 10)
      { me->set("gift2007/x", 10);} 
      tell_object(me, HIG"你现在的捐献积分已达" + me->query("gift2007/x") +
       "分,最高可达10分.\n"NOR);
      destruct(ob);
      return 1;
  }

   if ( base_name(ob) == ("/clone/fam/gift/str3") ||
        base_name(ob) == ("/clone/fam/gift/int3") ||
        base_name(ob) == ("/clone/fam/gift/dex3") ||
        base_name(ob) == ("/clone/fam/gift/con3") )
  {
      me->add("gift2007/x",1);
      if (me->query("gift2007/x") > 10)
      { me->set("gift2007/x", 10);} 
      tell_object(me, HIG"你现在的捐献积分已达" + me->query("gift2007/x") +
       "分,最高可达10分.\n"NOR);
      destruct(ob);
      return 1;
  }

   return 0;
}