
//春节饺子

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "春节饺子" NOR, ({ "jiaozi" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "春节才能吃到的饺子。\n" NOR);
                set("unit", "粒");
                set("value", 10);
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

        if ( ! arg || (arg != "jiaozi") )
          return 0;
	
	 me = this_player();

        if (me->query("gift2007/eat") >= 5 )
        {
             write("今年的礼物你已经吃太多了,再吃就消化不良了!\n");
             return 1;
        }

        message_vision(HIY "$N将饺子一口吞了，哈喇子顺着嘴角就流了出来，\n" +
				"还一个劲儿连说:味道好极了哟，还有吗？再来一个!\n" NOR, me);


	 me->add("combat_exp", 50000);

	 mapsk = me->query_skill_mapped("force");
        	if (me->can_improve_skill("force"))
                	me->improve_skill("force", 1500000);
      //  	if (stringp(mapsk) && me->can_improve_skill(mapsk))
      //          	me->improve_skill(mapsk, 1500000);

        	mapsk = me->query_skill_mapped("parry");
        	if (me->can_improve_skill("parry"))
                	me->improve_skill("parry", 1500000);
     //   	if (stringp(mapsk) && me->can_improve_skill(mapsk))
     //           	me->improve_skill(mapsk, 1500000);

        	mapsk = me->query_skill_mapped("dodge");
        	if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", 1500000);
    //    	if (stringp(mapsk) && me->can_improve_skill(mapsk))
      //          	me->improve_skill(mapsk, 1500000);
        me->add("gift2007/eat",1);

		destruct(this_object());
      return 1;
}


		


       	