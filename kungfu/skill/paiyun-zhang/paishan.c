// paishan.c 排山倒海
 
#include <ansi.h>
 
inherit F_SSERVER;

void paiyun2(object me);
void paiyun3(object me);

int perform(object me)
{
	string msg;
	object weapon, target;
	int ap, dp, damage;

	me->clean_up_enemy();
	target = me->select_opponent();

	if( !me->is_fighting()|| !living(me) )
	    	return notify_fail("「排山倒海」只能在战斗中使用。\n");

	if( (int)me->query("max_neili") < 5000 )
		return notify_fail("你的内力修为连排山倒海都打不出来！\n");

	if( (int)me->query("neili") < 500 )
		return notify_fail("你现在的内力不足。\n");

	if (objectp(weapon = me->query_temp("weapon")))
		return notify_fail("拿着武器怎么使「排山倒海」？\n");

	if(me->query_skill("strike") < 200)
		return notify_fail("你的掌法还不到家，连排山倒海都打不出来！\n");

	if(me->query_skill("force") < 200)
		return notify_fail("你内功的修为不够，连排山倒海都打不出来！\n");

	if( me->query_skill_mapped("strike") != "paiyun-zhang") 
		return notify_fail("你没有激发排云掌，无法使用排山倒海\n");
 
	if( me->query_skill_mapped("force") != "huntian-baojian") 
		return notify_fail("你用的内功并非浑天宝鉴，无法使用排山倒海\n");

	if (me->query_temp("paiyun",1))
		return notify_fail("你已经在运用排山倒海了。\n");

	msg = HIY "$N突然运气于掌，聚起「排山掌力」，右掌带一层淡淡的白雾直直拍向$n的胸前！\n\n"NOR;
	message_vision(msg, me, target);

 	ap = ((me->query("combat_exp"))*(me->query_dex()));
	dp = ((target->query("combat_exp"))*(target->query_dex()))/2;
	if( dp < 1 )
		dp = 1;
        if( random(ap * 4 / 3) < dp )
	{
		msg = HIR "$n心神一慌，一个躲闪不及，被$N的单掌实实在在的印在胸膛，$n的胸膛立刻就塌了下去！\n\n"NOR;
		message_vision(msg, me, target);
		me->add("neili",-500);
		damage = 100 + me->query_skill("strike") + random(me->query_skill("force"));
		target->receive_damage("qi", damage);
		COMBAT_D->report_status(target, 0);
		me->start_busy(3);
	}
	else
	{
		msg = HIG "只见$n神色一凛，不敢硬接，一个翻身及时的退出战圈，躲开了$N凌厉的攻势！\n\n"NOR;
		message_vision(msg, me, target);
		me->add("neili",-300);
		me->start_busy(3);
	}

	call_out("paiyun2", 3, me);

	return 1;
}

void paiyun2(object me)
{
	string msg;
	object weapon, target;
	int ap, dp, damage;

	me->clean_up_enemy();
	target = me->select_opponent();

	if( !me->is_fighting()|| !living(me) )
	    	return;

	if( (int)me->query("max_neili") < 8000 )
		return;

	if( (int)me->query("neili") < 1000 )
		return;

	if (objectp(weapon = me->query_temp("weapon")))
		return;

	if(me->query_skill("strike") < 400)
		return;

	if(me->query_skill("force") < 400)
		return;

	if( me->query_skill_mapped("strike") != "paiyun-zhang") 
		return;

	if( me->query_skill_mapped("force") != "huntian-baojian") 
		return;

	msg = WHT "$N双掌一错，白色劲气已然布满全身，风雷之声渐起，这第二掌「倒海」猛然拍出！\n\n"NOR;
	message_vision(msg, me, target);

	ap = ((me->query("combat_exp"))*(me->query_dex()));
	dp = ((target->query("combat_exp"))*(target->query_dex()))/2;
	if( dp < 1 )
		dp = 1;
        if( random(ap * 4 / 3) < dp )
	{
		msg = HIR "$n正瞠目间，$N双掌已到了胸前，内劲一吐，$n立时口喷鲜血，倒飞出三丈有余！\n\n"NOR;
		message_vision(msg, me, target);
		me->add("neili",-1000);
		damage = 300 + me->query_skill("strike") + 2 * random(me->query_skill("force"));
		target->receive_damage("qi", damage);
		COMBAT_D->report_status(target, 0);
		me->start_busy(3);
	}
	else
	{
		msg = HIG "$n躲无可躲，就地一滚，非常狼狈的堪堪躲开了这第二掌。\n\n"NOR;
		message_vision(msg, me, target);
		me->add("neili",-500);
		me->start_busy(3);
	}

	call_out("paiyun3", 3, me);

	return;
}

void paiyun3(object me)
{
	string msg;
	object weapon, target;
	int ap, dp, damage;

	me->clean_up_enemy();
	target = me->select_opponent();

	if( !me->is_fighting()|| !living(me) )
	    	return;

	if( (int)me->query("max_neili") < 10000 )
		return;

	if( (int)me->query("neili") < 1000 )
		return;

	if (objectp(weapon = me->query_temp("weapon")))
		return;

	if(me->query_skill("strike") < 500)
		return;

	if(me->query_skill("force") < 500)
		return;

	if( me->query_skill_mapped("strike") != "paiyun-zhang") 
		return;
 
	if( me->query_skill_mapped("force") != "huntian-baojian") 
		return;

	msg = HIW "$N神色凝重，周身七尺劲气涌动，突然大喝一生，这冠绝天下的无上掌力终化作「排山倒海」汹涌而出！\n\n"NOR;
	message_vision(msg, me, target);
 	ap = ((me->query("combat_exp"))*(me->query_dex()));
	dp = ((target->query("combat_exp"))*(target->query_dex()))/2;
	if( dp < 1 )
		dp = 1;
        if( random(ap * 4 / 3) < dp )
	{
		msg = HIR "$n似一片枯叶，被排云掌掌力的汹涌劲气包围、卷起、压扁、抛下，重重的摔在地上，眼看是不行了！\n\n"NOR;
		message_vision(msg, me, target);
		me->add("neili",-1200);
		damage = 500 + me->query_skill("strike") + 3 * random(me->query_skill("force"));
		target->receive_damage("qi", damage);
		COMBAT_D->report_status(target, 0);
		me->start_busy(random(10));
                }	else
	{
		msg = HIG "$n一闭眼，朝$N的反方向似一颗流星般急退而出，总算从鬼门关上拣回了一条命。\n\n"NOR;
		message_vision(msg, me, target);
		me->add("neili",-1000);
		me->start_busy(5);
	}

	return;
}
