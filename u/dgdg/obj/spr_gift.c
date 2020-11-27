//春节礼包


#include <ansi.h>
inherit ITEM;


void create()
{
        set_name(NOR + HIR "春节礼包" NOR, ({ "giftpack" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "个");
                set("long", "这是中华英雄巫师组发放的春节礼包，"
                            "你可以打开它(open giftpack)。\n");                
                set("no_put", "这样东西不能离开你。\n");
                set("no_sell", "这样东西不能离开你。\n");
        }
        setup();
}

void init()
{
     add_action("do_open","open");    
}

int do_open( string arg )
{
   object gift; 
   int x;
   object me;

   me = this_player();

    if ( !arg || arg != "giftpack")
    return notify_fail("你要打开什么？\n");

    x = me->query("gift2007/x");

   if (x < 1) {x = 1;}

    if(random(1000/x) == 0) 
    {  gift = new("/u/sanben/obj/shenyou");
       tell_object(this_player(), HIY"恭喜你获得了礼物"NOR + 
                               gift->name() + "。\n"NOR); 
       log_file("static/tianzi", sprintf("%s(%s) 获得神佑果 at %s.\n",
                me->name(1), me->query("id"), ctime(time())));
  
    } else  if(random(500/x) == 0) 

    {  gift = new("/u/sanben/obj/weapon_card");
       tell_object(this_player(), HIY"恭喜你获得了礼物"NOR + 
                               gift->name() + "。\n"NOR); 
       log_file("static/tianzi", sprintf("%s(%s) 获得神兵卡 at %s.\n",
                me->name(1), me->query("id"), ctime(time())));
  
    }  
    else   if( random(100/x) == 0) 
    {  gift = new("/d/death/obj/tianjing");
       tell_object(this_player(), HIY"恭喜你获得了礼物"NOR + 
                               gift->name() + "。\n"NOR); 
       log_file("static/tianzi", sprintf("%s(%s) 获得环宇天晶 at %s.\n",
                me->name(1), me->query("id"), ctime(time())));
  
    } 
    else 
    {
      gift = new("/u/sanben/obj/roll");
      gift->move(this_player());
      tell_object(this_player(), HIY"恭喜你获得了礼物"NOR + 
                               gift->name() + "。\n"NOR);   

      gift = new("/u/sanben/obj/fig");
      gift->move(this_player());
      tell_object(this_player(), HIY"恭喜你获得了礼物"NOR + 
                               gift->name() + "。\n"NOR);   

      gift = new("/u/sanben/obj/jiaozi");
      gift->move(this_player());
      tell_object(this_player(), HIY"恭喜你获得了礼物"NOR + 
                               gift->name() + "。\n"NOR);   


      gift = new("/clone/money/cash");
      gift->set_amount(100);

      gift->move(this_player());
      tell_object(this_player(), HIY"恭喜你获得了礼物100张"NOR + 
                               gift->name() + "。\n"NOR);      
   }
    me->delete("gift2007/x");
    destruct(this_object());   
    return 1;
}

