
//巧克力(加2万潜能)

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "巧克力" NOR, ({ "qiao keli", "chocolate" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "圣诞礼物巧克力,每个加2万潜能。\n" NOR);
                set("unit", "个");
                set("value", 10);
                set("no_sell",1);
                set("weight", 10);                
             }
        setup();
}

void init()
{       
     add_action("do_eat","eat");     
}
                
int do_eat( string arg )
{       object me; 
        me = this_player();         
        
        if ( ! arg || (arg != "qiao keli" &&
             arg != "chocolate") )
        return 0;

        message_vision(HIW "$N" HIW "将巧克力一口吞了。\n" NOR, me);

        me->add("potential",20000);

        tell_object(me, HIG"恭喜你增加了两万点潜能。"
                    "祝你圣诞快乐！\n"NOR);
        destruct(this_object());
        return 1;    
}

