#include <ansi.h>

inherit F_CLEAN_UP;

void dest_sword(object me);

int exert(object me, object target)
{
        object weapon;
		int damage;

        if (target != me)
                return notify_fail("涅槃无形剑只能通过自己使用。\n");

        if ((int)me->query("neili") < me->query("max_neili") / 2 )
                return notify_fail("你的内力不够，难以施展涅槃无形剑。\n");

		if ((int)me->query("jingli") < 500)
                return notify_fail("你的精力不够，难以施展涅槃无形剑。\n");
		
		if ((int)me->query_skill("linji-zhuang", 1) < 300)
                return notify_fail("你的临济十二庄火候不够，难以施展涅槃无形剑。\n");

		if ((int)me->query_skill("mahayana", 1) < 200)
                return notify_fail("你的大乘涅槃功火候不够，难以施展涅槃无形剑。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("你手中已经有武器了。\n");

        if (present("emei jianqi", me))
                return notify_fail("你身上已经有一束剑气了。\n");
				
	    if (me->query("family/family_name") != "峨嵋派")     
                return notify_fail("你已非峨嵋派弟子，无缘再用此绝学了。\n");
				
        me->add("neili", -100);
		me->add("jingli", -100);

        message_combatd(HIW "$N" HIW "食指虚点，指尖顿时生出半尺吞吐不定的"
                        "青芒，宛若一束无形剑气。\n" NOR, me);

        weapon = new("/clone/weapon/em_jianqi");
		damage=(int) me->query_skill("mahayana", 1);
		weapon->set("weapon_prop/damage",damage);
        weapon->move(me);
        //weapon->wield();
		

        me->start_call_out((: call_other, __FILE__, "dest_sword",
                              me :), 120);

        if (me->is_fighting())
        me->start_busy(1);

        return 1;
}

void dest_sword(object me)
{
        object weapon;      
		   
		if (present("emei jianqi",me))   
        {
		        weapon = present("emei jianqi",me);
                if (me->is_fighting())
                        me->start_call_out((: call_other, __FILE__, "dest_sword",
                                              me :), 2);
                else
				message_combatd(HIW "一阵微风拂过，$N" HIW "身上的涅槃无形剑随风而去。\n" NOR, me);
                destruct(weapon);
        }
}
