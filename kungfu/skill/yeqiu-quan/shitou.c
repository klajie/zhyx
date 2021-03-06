// shitou.c 野球拳 伤精

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
#define SHI  HIM "『石头』" NOR
#define JIAN HIR"『剪刀』" NOR
#define BU HIB"『布』" NOR

int perform(object me, object target)
{

        string msg;

        if (userp(me) && ! me->query("can_perform/yeqiu-quan/shitou"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHI "只能对战斗中的对手使用。\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("你必须空手才能使用"	SHI "！\n");
                
        if ((int)me->query_skill("yeqiu-quan", 1) < 250)
                return notify_fail("你的野球拳还不够娴熟，不能使用" SHI "。\n");

        if (me->query_skill_prepared("unarmed") != "yeqiu-quan"
           && me->query_skill_prepared("finger") != "yeqiu-quan"
           && me->query_skill_prepared("hand") != "yeqiu-quan"
           && me->query_skill_prepared("cuff") != "yeqiu-quan")
                return notify_fail("你没有准备野球拳，无法使用" SHI "。\n");
                                
        if ((int)me->query("neili", 1) < 1000)
                return notify_fail("你现在内力太弱，不能使用" SHI "。\n");

        if (userp(target))
                return notify_fail(HIW "你不能对玩家使用这招！\n" NOR);

	if (! living(target))
		return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIG "$N" HIG "扎一个马步，对着$n"HIG"喝道“就用野球拳来这就一决胜负吧！”。\n\n" NOR;

	me->add("neili", -50);

	if (me->query("jing") > me->query("max_jing")/2 && target->query("jing") > target->query("max_jing")/2)
        {
	        msg += HIG "$n" HIG "立刻回应道“好！咱们开始！”\n\n" NOR;

                me->start_busy(2);
                me->add("neili", -100);
		me->start_busy(2);
		target->start_busy(2);

		msg += HIG "两人同时报数：“一！二！三！”\n\n"
			"$N"HIG"右手握拳往前一伸，赫然是一个" SHI HIG"。\n" NOR;

		switch(random(3))
		{
		case 1:
			msg += HIG"$n"HIG"右手一伸，竟然出了一个" BU HIG"。\n" NOR;
			msg += HIC "$N黯然道，我输了！没想到我居然输了！\n"
				HIC "$N只觉得胸口一疼，竟然呕吐出了一大口鲜血！\n" NOR;
			me->add("neili", -1000);
			me->receive_damage("jing", me->query("max_jing")/2-10);
			break;
		case 2:
			msg += HIG"$n"HIG"右手一伸，出了一个" JIAN HIG"。\n" NOR;
			msg += HIC "$n惨然道，“我竟然输了！我竟然也会输！”\n"
				HIC "$n刚说完，口中竟然不断吐出鲜血！\n" NOR;
			me->add("neili", -1000);
			target->receive_damage("jing", target->query("max_jing")/2-10);
			break;
		default :
			msg += HIG"$n"HIG"右手一伸，竟也出了一个" SHI HIG"。\n" NOR;
			msg += HIC "$N往后退了一步喝道：“这局算平手平了！”\n$n也往后退了一步。\n" NOR;
			me->start_busy(1 + random(3));
			target->start_busy(1 + random(3));
			break;
		}

        } else 
        {
	        msg = HIG "可是$n" HIG "却对野球拳决胜负不感兴趣，对$N"HIG"的邀战不闻不问继续攻击。\n\n" NOR;
		me->start_busy(1);
        }

        message_combatd(msg, me, target);

        return 1;
}