// by yuchang
inherit ROOM;
#include <ansi.h>
#include <room.h>
int do_press(string arg);
void init();


void create()
{
      set("short", "藏剑庐");
      set("long",
"[1;32m这里就是傲剑山庄的藏剑庐\n"
"在场中间有一块巨大的红木制武器架(shelf)\n"
);
   set("exits",([
           "south" : __DIR__"square",
]));


  set("item_desc", ([
     "shelf" : "这是一只由名贵红木所制，用来存放配剑的架子,似乎可以拿出来(take sword)。\n",

  ]));
  set("aocangtian", 1);

  setup();
}

void init()
{
        add_action("do_press", "press");
      add_action("do_take", "take");
      add_action("do_quit","kill");
      add_action("do_steal","steal");
}
int do_press(string arg)
{
    string p;
            object me,obj;
             object ob;
             me = this_player();
              ob = this_object();
    p = sprintf("%d", this_player()->query("_passwd")); 
    if( !arg || arg == "" )
    {
        write("别瞎按！\n");
        return 1;
    }
    if( arg == p )
    {
        message_vision("只听得一阵隆隆的响声由远及近。\n", this_player());
        message_vision("剑炉缓缓移了开来，露出一个洞。一把宝剑呈现在你面前。\n", this_player());
            obj = new ("/d/zhuanshi/obj/jiushi");
            obj->move(me);
             return 1;
      }
    else
    {
            message_vision("$N一阵乱按，突然石板的缝隙间射出一支毒箭！。\n", this_player());
            this_player()->die();
            return 1;
        }
}

int do_steal(string arg)
{
        write(this_player()->query("name")+"，不要为此不才之事！\n");
        return 1;
}

int do_take(string arg)
{
       object me,obj;
        object ob;
       me = this_player();

        ob = this_object();
       if( !arg || arg!="sword" ) return notify_fail("你要拿什么？\n");
          if (me->query("najian")) {
       tell_object(me,CYN "浪翻云的身影突然出现在一阵烟雾之中。\n\n");
       tell_object(me,HIR "浪翻云一巴掌敲在你手上：小朋友，不要乱动！\n\n");
       tell_object(me,CYN "只见一阵烟雾过後，浪翻云的身影已经不见了。\n" NOR);
       return 1;

}
      obj = new ("/d/ajszhuang/npc/obj/ling");
       obj->move(me);

       // mark the owner who take it
       obj->set("owner", me->query("id"));

       message_vision(HIC"$N不觉得呆了一呆，里面居然有100余把宝剑，到底是哪一把呢？\n"
             "突然你听到：啪“的一声，什么东西掉在你怀里。\n" NOR, this_player());
       me->delete("najian");
       me->set("najian",1);
       me->start_busy(2);
       return 1;
}



