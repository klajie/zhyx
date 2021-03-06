#include <ansi.h>
inherit ROOM;

#define REBORND   "/adm/daemons/rebornd"

void create()
{
        set("short", WHT"惊雁宫大门"NOR);
        set("long", @LONG
突然你眼前一亮，一座巨大的宫殿呈现在你面前，
这正是传说中的惊雁宫,惊雁宫占地极广，殿阁亭
台，气象森然，全宫依山而建，背靠惊雁峰，亦是
行宫的名之来由，惊雁宫除了由千里峰攀山而下，
唯一途径是一条直通正门的大石桥，石桥宽广，可
容四马并驰，鬼斧神工，气势磅礴，使人生起一夫
当关万夫莫敌的感叹。
LONG
        );
        set("outdoors", "qianhuigu");
             
        set("exits", ([ 
                "north" : __DIR__"migong2",
        ]));
        setup();       
}

void init()
{
     string id, out;
     object ob, room;
     object me = this_player();   

     out = REBORND->query("jingyan/out");

     if ( ! stringp(out) ) return; 

     if ( ! objectp(room = find_object(out)) )
        room = load_object(out); 

     if ( me->is_character() && ! userp(me) )
     {
        me->move(room);
        return;
     }

     if ( ! me->query("reborn_start"))
     {
        tell_object(me, 
           BLINK HIR"惊雁宫可不是谁都能进的，你还是速速离去吧!\n\n"NOR);

        message_vision(HIY"一股巨大的力量将$N推了出去。\n\n"NOR, me);
        me->move(room);
        return;
     }
  
     id = REBORND->query("jingyan/id");
     
     if ( stringp(id) && id != me->query("id") )
        ob = find_player(id);

     if (objectp(ob) && 
         base_name(environment(ob))[0..18] == "/d/zhuanshi/jingyan")
     {             
         message_vision(HIY"一股巨大的力量将$N推了出去。\n\n"NOR, me);         
         tell_object(me, 
            HIY"现在有人正在惊雁宫里，你迟点再来吧。\n\n"NOR);
         me->move(room);
         return;
     }         
     REBORND->set("jingyan/id", me->query("id"));
     
}
