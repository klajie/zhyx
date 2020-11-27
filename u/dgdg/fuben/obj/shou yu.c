


#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIC "手谕" NOR, ({ "shou yu","shou","yu" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "\n这是一张巫师手谕，上面写着“准许打造”四字，凭此手谕可以出入远古炼造室。\n" NOR);
                set("unit", "张");
                set("value", 1);
                set("no_sell", 1);
                set("no_steal",1);
                set("no_put", 1); 
                set("weight", 10);
                set("no_light", "这东西你也想烧？小心出事哦！"); 
                set("material", "paper");                 
             }
        setup();
}
      void init() 
      { 
              if( this_player() == environment() ) 
              { 
                      remove_call_out("destroy");  
                      call_out("destroy", 300);  
              } 
      } 
      int destroy()  
      {  
          tell_room(environment(this_object()),   
                     "你手中的手谕慢慢的化成灰被一阵风吹走了!\n");  
          destruct(this_object());  
          return 1;  
      } 