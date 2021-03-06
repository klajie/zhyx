
//神佑果 (可以给指定id获得特殊属性,成功率100%)

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "神佑果" NOR, ({ "shenyou guo", "guo", "shenyou"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "可以给指定id获得特殊属性，成功率100%，"
                                "请先wish再eat。\n" NOR);
                set("unit", "粒");
                set("value", 10);
                set("no_get",1); 
                set("no_beg",1); 
                set("no_steal",1); 
                set("no_drop",1); 
                set("no_put",1); 
                set("no_sell",1); 
                set("no_give",1); 
                set("weight", 10);                
             }
        setup();
}

void init()
{                             
                    if (environment(this_object())->query("id") != "zhuanshib") 
                      {     
                           message("vision", HIY + "神佑果忽然搜的一声飞走了，" 
                              "大概是去寻找他的主人去了吧。\n" NOR, 
                                  environment(this_object())); 
       
                           if (! find_player("zhuanshib"))  
                           {                         
                           destruct(this_object()); 
                           } 
                          else 
                           {  
                                  this_object()->move(find_player("zhuanshib")); 
                                  tell_object(find_player("zhuanshib"),  
                                      HIC"神佑果忽然飞到了你手里。\n"NOR); 
                           } 
                      } 
     add_action("do_wish","wish");
     add_action("do_eat","eat");
}

int query_autoload()
{
        return 1;
}
                
int do_wish( string arg )
{       object me; 
        me = this_player();         
        
        if ( ! arg || (arg != "真命天子" &&
             arg != "九天玄女" && arg != "天煞孤星") )
        {
            write(HIR"格式为wish 真命天子 或 wish 九天玄女 或 " 
                           "wish 天煞孤星\n\n"NOR);
            return 1;
        }  
      
        if (arg == "真命天子" && me->query("gender") != "男性")
        {        
           write(HIR"真命天子的属性只有男性才能获得！\n\n"NOR);
           return 1;
        }

        if (arg == "九天玄女" && me->query("gender") != "女性")  
        {      
           write(HIR"九天玄女的属性只有女性才能获得！\n\n"NOR); 
           return 1;
        }       
        me->set_temp("special_wish", arg);
        write(HIG"你指定了要获得" + arg + "的属性，现在请eat guo。\n\n"NOR); 
        return 1;    
}

int do_eat( string arg )
{    
    object me;
    string special;
    me = this_player();
   
    if ( ! arg || (arg != "shenyou guo" && 
         arg != "guo"&& arg != "shenyou") )
    return 0;

    if (! me->query_temp("special_wish"))
    { 
       write(HIR"请先用wish <特殊属性> 指定你要获得的属性。\n\n");
       return 1;
    }

    if ( me->query("special_skill/emperor") || 
         me->query("special_skill/queen") || 
         me->query("special_skill/lonely") )
    { 
       write(HIR"你已经有了特殊属性，不能再要了。\n\n");
       return 1;
    }    

    special = me->query_temp("special_wish");

    if (special == "真命天子" && me->query("gender") != "男性") 
    {       
       write(HIR"真命天子的属性只有男性才能获得！\n\n"NOR);
       return 1;
    }   
    if (special == "九天玄女" && me->query("gender") != "女性") 
    {       
       write(HIR"九天玄女的属性只有女性才能获得！\n\n"NOR); 
       return 1;
    }

    message_vision(HIY "$N" HIY "哈哈一笑，将神佑果一口吞了。\n" NOR, me);

    if ( special == "真命天子" )
    {
       me->set("special_skill/emperor", 1);
       me->set("special_skill/youth", 1);
       me->set("per",35);
       log_file("static/tianzi", sprintf("%s(%s) 获得天子属性 at %s.\n",
                me->name(1), me->query("id"), ctime(time())));
    }

    if ( special == "九天玄女" )
    {
       me->set("special_skill/queen", 1);
       me->set("special_skill/youth", 1);
       me->set("per",40);
       log_file("static/tianzi", sprintf("%s(%s) 获得玄女属性 at %s.\n",
                me->name(1), me->query("id"), ctime(time())));
    }

    if ( special == "天煞孤星" )
    {
       me->set("special_skill/lonely", 1);
       me->delete("family");
       me->delete("class");
       log_file("static/tianzi", sprintf("%s(%s) 获得孤星属性 at %s.\n",
                me->name(1), me->query("id"), ctime(time())));
    }

    write(HIG"恭喜你获得了" + special + "属性。\n\n"NOR);
    me->delete_temp("special_wish");

    CHANNEL_D->do_channel(this_object(), "rumor",
           "听说江湖中有人获得了" + special + "属性。\n");
    destruct(this_object());
    return 1;
}
                


        
