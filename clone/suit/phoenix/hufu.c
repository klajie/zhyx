// 成套装备
// update by kasumi
#include <ansi.h>
inherit ITEM;



void create()
{
 
        set_name( HIR"朱雀之舞"NOR, ({ "phoenix hufu","hufu" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "块");
                set("long", HIC"这是一块朱雀之符，能唤醒朱雀套装的潜能。"NOR"
成套装备指令："HIG"huanxing"NOR"
成套装备："HIR"[朱雀之舞]"NOR" "RED"朱雀之羽"NOR" "YEL"朱雀之眼"NOR" "GRN"朱雀之爪"NOR" "HIC"朱雀之翼"NOR"
成套效果："HIG"唤醒体内潜在的力量,临时附加二百级阴阳八卦。"NOR"\n");
                set("value", 100000);
                set("no_steal", 1);
                set("no_beg", 1);
                set("no_sell", 1);   
                set("material", "crystal");
                
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

  object me = this_player();
  object ob = this_object();
  
        if (me->query_temp("phoenixeff"))
           return notify_fail("你已经呼应了朱雀之舞！\n");
       
        if(me->is_busy())
           return notify_fail("你正忙着呢!\n");
        if(!jia = present("phoenix armor",me))
           return notify_fail("你还缺少"RED"朱雀之羽"NOR"\n");   
        if(!head = present("phoenix eye",me))
           return notify_fail("你还缺少"YEL"朱雀之眼"NOR"\n");
        if(!shoe = present("phoenix shoes",me))
           return notify_fail("你还缺少"GRN"朱雀之爪"NOR"\n");
         if(!pifeng = present("phoenix wing",me))
           return notify_fail("你还缺少"HIC"朱雀之翼"NOR"\n");
         if(environment(this_object())!=me)
            return notify_fail("护符必须携带在身上才能发挥作用。\n");

	if(me->query("int") < 35)
		return notify_fail("你的先天悟性不足无法领悟阴阳八卦之术。\n");
            
	if(me->query_skill("zuoyou-hubo")>1)
		return notify_fail("你学有左右互搏之术，无法唤醒朱雀之舞的灵力。\n");

	if(me->query_skill("count")>1)
		return notify_fail("你本身学有阴阳八卦之术，无法唤醒朱雀之舞的灵力。\n");

	if ((int)me->query("jingli") < 400)
		return notify_fail("你现在精力不够，难以唤醒朱雀之舞的灵力。\n");

	if ((jia->query("equipped")!="worn") || (head->query("equipped")!="worn")||(pifeng->query("equipped")!="worn")  || (shoe->query("equipped")!="worn") )   
           return notify_fail("你必须要穿上整套朱雀套装。\n"NOR);
        
	message_vision(HIG"$N"HIG"轻轻拂过"HIR"朱雀之舞"HIG"顿时感到头脑无比清晰，不再为世间阴阳八卦所困！\n"NOR,me);
	me->set_temp("phoenixeff",1);
	me->set_skill("count", 150);
	me->add("jingli", -300);
	call_out("phoenix_ok",me->query_int(),me);
	return 1;
}


void phoenix_ok(object me)
{ 
	if (!me) return;
	me->delete_skill("count", 150);
	me->delete_temp("phoenixeff");
	message_vision(HIG"$N"HIG"精神所懈，微微一愣，顿时为凡尘所困！\n"NOR,me);
}