
//大补丹(加20万潜能)

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "大补丹" NOR, ({ "da budan", "dan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "六狼的大补丹,味道一级棒，可惜每人只能吃三颗。\n" NOR);
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
{
	string mapsk;	 
        object me; 
        me = this_player();         
        
        if ( ! arg || (arg != "da budan" &&
             arg != "dan") )
        return 0;
        
        if (me->query("gift2009/newyear/eat") >= 3 )
        {
            write(HIR"你已经获得充足的滋补，再吃下去恐怕会浑身爆炸而死!\n"NOR);
            return 1;
        }

        message_vision(HIW "$N" HIW "盘坐吐纳，拿出大补丹含在嘴里，一股白气缓缓从头上升起。\n" NOR, me);
        me->add("combat_exp", 200000);
        me->add("potential",200000);

        	mapsk = me->query_skill_mapped("parry");
        	if (me->can_improve_skill("parry"))
                	me->improve_skill("parry", 1500000);
        	if (me->can_improve_skill("parry"))
                	me->improve_skill("parry", 1500000);
          if (me->can_improve_skill("parry"))
                	me->improve_skill("parry", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("parry"))
                	me->improve_skill("parry", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("parry"))
                	me->improve_skill("parry", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("parry"))
                	me->improve_skill("parry", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);

        	mapsk = me->query_skill_mapped("dodge");
        	if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", 1500000);
        	if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", 1500000);
          if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);	
	    

        tell_object(me, HIG"恭喜你增加了二十万点经验和潜能。"
                    "你觉得自身的轻功招架水平有了大幅提高！\n"NOR);
        me->add("gift2009/newyear/eat", 1);
        destruct(this_object());
        return 1;    
}

