#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", NOR + CYN "\n\n                畜        生        道" NOR);
        set("long", CYN "\n"
"飞禽走兽，弱肉强食。因学习邪见、邪法而生慢心的众生，喜\n"
"欢以邪见与人争论，因为怀着怨憎心，就会投生喜欢互相残害\n"
"的畜生道。性情怯弱，常怀惊恐的动物，也是因过去生惊吓他\n"
"人在先，而得出这样的果报。你可以在这里参悟(canwu)。\n\n" NOR);

 set("exits", ([ 
            "out"   : "/d/special/taixu",            
        ]));
        setup();
}

void init()
{
        add_action("do_canwu", "canwu");
}


int do_canwu()
{
        object ob;
        int c_skill;

        ob = this_player();

        c_skill = (int)ob->query_skill("lunhui-jian", 1);     

        if (ob->query("can_perform/lunhui-jian/chushengdao"))
        {
                write("你已经参悟透了畜生道。\n");
                return 1;
        }

/*         if (!ob->query("reborn"))
        {
                write("你未修前世，无法参透畜生道。\n");
                return 1; 
        } */

        if (c_skill < 200)
        {
                write("你至少要二百级轮回剑，才能参透畜生道。\n");
                return 1; 
        }

        if (ob->query("jing") < 80)
        {
                write("你精力不能集中，现在无法参悟。\n",ob);
                return 1; 
        }
      
        if (random(15) != 1)
        {
        
                write("你趺坐静思良久，还是无法参透生死之道。\n", ob);              
                return 1;
        }
		
		if (random(3) == 1)
		{
        message_sort(HIW"\n$N" HIW"趺坐静思，猛然间一声长叹，诸"
                     "多凡尘旧事已涌上心头，$N" HIW "终于将「畜生道」"
                     "参悟出来，从此再无疑虑。\n", ob);       
    
          write(HIC "你学会了「畜生道」。\n" NOR);
          ob->set("can_perform/lunhui-jian/chushengdao", 1);
		}
		else 
		{
		 message_sort(HIR"\n$N只觉得人生如梦，生死无意，气血翻涌，一头栽倒在地!\n", ob);    
		 ob->die();
		 return 1;
		}
		
        ob->receive_damage("jing", 75);
        ob->start_busy(2);
        return 1;
}