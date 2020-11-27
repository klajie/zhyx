// By yuchang 
inherit ROOM;
#include <ansi.h> 
void create()
{
        set("short", "宝库");
        set("long", @LONG  
这是一个宽阔的房间，室顶四角均有通气口，两边 
平排放置共几百个该是装载奇珍异宝的箱子(xiang)，贴
墙有几百个放黄金的箱子(xiangzi)!
LONG
        ); 
        set("item_desc", ([       
"xiang" : "箱子里刻着一些字符，好象是一样武功，你不由想仔细看(think)一下!\n",          
   "xiangzi" : "箱子里有很多黄金,你要拿出来吗??\n",      

                          ]));
        set("exits", ([
                "east" : __DIR__"baokudt",
                      ]));
       set("no_clean_up", 1);
        set("no_stab", 1);
        setup();
}
void init()
{
  object me = this_player(); 
    add_action("do_pick", "pick");  
    add_action("do_push", "push");     } 

int do_pick(string arg)
{
        object money, me=this_player();

        if( !arg || arg=="" ) return 0;

 if(me->query_temp("ygbz_money"))
return notify_fail("你已经拿过钱了,不要意思再拿了!\n");
      if( arg=="xiangzi" )
                             {  
if(query_temp("nasword")){ 
   message_vision("$N想去拿黄金,发现已经被人拿了\n", this_player());
     return 1;
 }
                                message_vision(
HIY"$N在箱子里拿出黄金!\n"NOR, this_player());
                        money = new("/clone/money/cash"); 
                            money->move(me);    
set_temp("nasword",1); 
me->set_temp("ygbz_money",1);
 message("channel:chat", HBRED HIB"【宝藏】"+me->query("name")+"在杨公宝库里发现了大量的黄金了!\n"NOR,users()); 
return 1;
                }
        return 1;
}
int do_push(string arg)
{
  object me = this_player();
        if(!arg || arg!="door")
                return notify_fail("你要推什么？\n");
   if(query("exits/west"))
           return notify_fail("门已经开了,你推个头？\n");
  message_vision(HIG"$N轻轻推开墙壁，发现有道暗门!\n"NOR,me);
   set("exits/west", "/d/changan/xi-chengmen"); 
  call_out("on_guanmen", 5);
return 1;
}
void on_guanmen(object room)
{
      message_vision(HIG"突然出现咔咔的响声,墙壁又合上了!\n"NOR, this_player());
delete("exits/west");
}

