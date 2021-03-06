#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", NOR + HIB "\n\n                饿        鬼        道" NOR);
        set("long", HIB "\n"
"哀嚎四起，环顾周围，遍是咽细如针，口大如炬，腹鼓如山的\n"
"饿鬼。前世造作的善恶业不同，在饿鬼道所受的果报也会不同。\n"
"饿鬼多是汲汲于饮食，但却四处奔走求食不能，所见池水却都\n"
"变成脓血而不能饮用，不是遇水成火就是喉细无法咽食。你可\n"
"以在这里参悟(canwu)。\n\n" NOR);

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

        if (ob->query("can_perform/lunhui-jian/eguidao"))
        {
                write("你已经参悟透了饿鬼道。\n");
                return 1;
        }

/*         if (!ob->query("reborn"))
        {
                write("你未修前世，无法参透饿鬼道。\n");
                return 1; 
        } */

        if (c_skill < 400)
        {
                write("你至少要四百级轮回剑，才能参透饿鬼道。\n");
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
		
		if (random(4) == 1)
		{
        message_sort(HIW"\n$N" HIW"趺坐静思，猛然间一声长叹，诸"
                     "多凡尘旧事已涌上心头，$N" HIW "终于将「饿鬼道」"
                     "参悟出来，从此再无疑虑。\n", ob);       
    
          write(HIC "你学会了「饿鬼道」。\n" NOR);
          ob->set("can_perform/lunhui-jian/eguidao", 1);
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