#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{     	   
        set_name(HIW "涅槃无形剑" NOR, ({ "emei jianqi", "jianqi", }));
        set_weight(1);
		
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "束");
                set("long", HIW "这是一束由内力化成的剑气。\n" NOR);             
				set("no_give", "这玩意儿无法给别人。");               
                set("material", "air");              
        }
		
        init_sword(100);
        setup();
}


mixed hit_ob(object me, object victim, int damage_bonus)
{
       int ap,dp;
       int n,damage;	
		
		n = (int) (me->query_skill("mahayana", 1)/10);
		damage = (int) me->query_skill("mahayana", 1);
		
		if ( me->query_temp("no_exert") || !me->query_skill("mahayana", 1)|| me->query("family/family_name") != "峨嵋派")
		{
			 destruct(this_object());
			 message_combatd(HIW "一阵微风拂过，涅槃无形剑已随风而去。\n" NOR, me);
		}


		if (random(6)<n)
		{
		     victim->receive_wound("qi", damage / 2 + random(damage / 2), me);
             return HIG "$N" HIG "手中青芒闪动，一道道射向$n" HIG "，震得$n吐血连连！\n" NOR;		
		} 
        
        return ;
}
