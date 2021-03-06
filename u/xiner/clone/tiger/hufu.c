//update by xiner
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIW"白虎之力"NOR,({"tiger hufu","hufu"}));
	set_weight(3000);
	if(clonep())
	set_default_object(__FILE__);
	else{
		set("unit","块");
		set("long",HIC"这是一块白虎之符，能唤醒白虎套装的潜能。"NOR"
成套装备指令："HIG"huanxing"NOR"
成套装备："HIR"[白虎之力]"NOR" "HIW"白虎战甲"NOR" "HIW"白虎战盔"NOR" "HIW"白虎战靴"NOR" "HIW"白虎披风"NOR"
成套效果："HIG"唤醒体内潜在的力量，临时附加空手伤害和有效等级。"NOR"\n");
		set("value",100000);
		set("no_steal",1);
		set("no_beg",1);
		set("no_sell",1);
		set("material","crystal");
	}
	setup();
}
int query_autoload()
{
	return 1;
}

void init()
{
	add_action("do_hx","huanxing");
}

int do_hx()
{
	object jia,head,shoe,pifeng;
	object me=this_player();
	object ob=this_object();

	if(me->query_temp("tigereff"))
		return notify_fail("你已经呼应了白虎之力！\n");

	if(me->is_busy())
		return notify_fail("你正忙着呢!\n");

	if(!jia=present("tiger armor",me))
		return notify_fail("你还缺少"HIW"白虎战甲"NOR"\n");
	if(!head=present("tiger helmet",me))
		return notify_fail("你还缺少"HIW"白虎战盔"NOR"\n");
	if(!shoe=present("tiger shoes",me))
		return notify_fail("你还缺少"HIW"白虎战靴"NOR"\n");
	if(!pifeng=present("tiger coat",me))
		return notify_fail("你还缺少"HIW"白虎披风"NOR"\n");

	if(environment(this_object())!=me)
		return notify_fail("护符必须携带在身上才能发挥作用。\n");

	if(me->query("str")<35)
		return notify_fail("你的先天臂力不足无法施展白虎之力。\n");

//	if(me->query_skill("zuoyou-hubo")>1)
//		return notify_fail("你学有左右互搏之术，无法唤醒白虎之力的灵力。\n");

	if((int)me->query("jingli")<500)
		return notify_fail("你现在精力不够，难以唤醒白虎之力的灵力。\n");

	if((jia->query("equipped")!="worn")||(head->query("equipped")!="worn")||(pifeng->query("equipped")!="worn")||(shoe->query("equipped")!="worn"))
		return notify_fail("你必须要穿上整套白虎套装。\n"NOR);

	message_vision(HIG"$N"HIG"轻轻拂过"HIW"白虎之力"HIG"顿时一股热流从护符中流入$N"HIG"的双臂！\n"NOR,me);
	me->set_temp("tigereff",1);
	me->add_temp("apply/cuff", (int)me->query_str()/5);
	me->add_temp("apply/claw", (int)me->query_str()/5);
	me->add_temp("apply/hand", (int)me->query_str()/5);
	me->add_temp("apply/finger", (int)me->query_str()/5);
	me->add_temp("apply/strike", (int)me->query_str()/5);
	me->add_temp("apply/unarmed", (int)me->query_str()/5);
	me->add_temp("apply/unarmed_damage", 200);
	me->add("jingli",-300);
	call_out("tiger_ok",me->query_str(),me);

	return 1;
}


void tiger_ok(object me)
{
	if(!me)return;
	me->add_temp("apply/cuff", - (int)me->query_str()/5);
	me->add_temp("apply/claw", - (int)me->query_str()/5);
	me->add_temp("apply/hand", - (int)me->query_str()/5);
	me->add_temp("apply/finger", - (int)me->query_str()/5);
	me->add_temp("apply/strike", - (int)me->query_str()/5);
	me->add_temp("apply/unarmed", - (int)me->query_str()/5);
	me->add_temp("apply/unarmed_damage", - 200);
	me->delete_temp("tigereff");
	message_vision(HIG"$N"HIG"精神一懈，双臂中的白虎之力渐渐消失！\n"NOR,me);
}