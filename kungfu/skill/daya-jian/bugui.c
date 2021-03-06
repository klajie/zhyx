
#include <ansi.h>

inherit F_SSERVER;
#define bugui "「" HIW "不归式" NOR "」"

int perform(object me, object target)
{
        string msg,str,force;
        object weapon,weapon2;
        int n,count;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

		if (userp(me) && ! me->query("can_perform/daya-jian/bugui"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        skill = me->query_skill("daya-jian", 1);

        if (! me->is_fighting(target))
                return notify_fail(bugui"只能对战斗中的对手使用。\n");

        if(me->query_skill_mapped("sword") != "daya-jian") 
                return notify_fail("你没有用大雅剑法，无法使用不归式绝招！\n");

        if (skill < 250)
                return notify_fail("你的大雅剑法等级不够，练好了再来！\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if (me->query("neili") < 500)
                return notify_fail("你的内力不够。\n");
		
		if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
        
        ap = me->query_skill("sword") + me->query_skill("force") + me->query_skill("dodge") + me->query_skill("parry") + me->query_skill("tanqin-jifa")/2 + me->query_skill("chess", 1)/2;
        dp = target->query_skill("dodge", 1) + target->query_skill("parry", 1) + target->query_skill("force", 1) + target->query_skill("sword", 1); 
        dp = dp * 3/2 + target->query_skill("tanqin-jifa")/2 + target->query_skill("chess", 1)/2;

        damage = ap + random(ap);         
        

        msg = HIC "\n$N" HIC "先行存念，内劲真气勃发，" NOR YEL "大雅古剑法" HIC "顿时挥洒得淋漓尽致！\n" +
              weapon->name() + HIC "寒光闪烁，幻化为满天剑影，内谙弈道之式，向$n" HIC "洒去！\n" NOR;

        message_combatd(msg, me, target);

        n = 12;
		if (n>12)
			n=12;

                count = ap / 6;
		me->add_temp("apply/attack", count);
		me->add_temp("apply/damage", me->query_skill("tanqin-jifa", 1) / 3);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(2)==1)
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }
		me->add_temp("apply/attack", -count);
		me->add_temp("apply/damage", -me->query_skill("tanqin-jifa", 1) / 3);

		if ((int)target->query("qi")> 0&& me->is_fighting(target))
		{
 
              force = me->query_skill_mapped("force");
              if (!stringp(force)) force = "force";
        
        msg = HIM "\n$N" HIM "一阵狂攻之后，忽然招式一缓，身形急退，须臾已在丈许之外。\n"
              "$N" HIM "仗剑而立，双目凝视$n" HIM "。"
              "$n" HIM "被这犀利的目光吓得一哆嗦，心头一阵迷惘......\n"
              "忽闻$N" HIM "大喝一声:\n"
              HIW "风萧萧兮易水寒，壮士一去兮不复还!\n"
              HIM "歌声中混杂着强劲的" HIR + to_chinese(force)+ HIM"，"
              "只见$N" HIM "人剑合一，刺向$n" HIM "，正是" NOR CYN "大雅古剑法" HIM "的" HIW "『不归式』" HIM"！！\n\n" NOR;

           weapon2 = target->query_temp("weapon");
        
            if (ap * 2/3 + random(ap) > dp || !living(target))
             {

				 if (me->query_skill_mapped("tanqin-jifa") == "tieqin-yin")
				 {
					  msg += HIR "$n" HIR "只觉丹田一寒，内息受阻，浑身酸软无力！\n" NOR;
					   target->add("neili", -damage*3);
					  if (target->query("neili") < 0)
                        target->set("neili", 0);
				 }
				 else if (me->query_skill_mapped("tanqin-jifa") == "qiuyue-lai")
				 {
					 msg += HIR "$n" HIR "只觉一股热流穿心而过，喉头一甜，鲜血狂喷而出！\n" NOR;					 
                     target->receive_wound("qi", damage*2, me);
	                 str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	        	     msg += "($n"+str+")\n";					 
				 }
				 else if (me->query_skill_mapped("tanqin-jifa") == "jian-jia")
				 {
					  msg += HIR "$n" HIR "只觉一股寒流透心而过，脑中嗡嗡乱响，步伐踉跄！\n" NOR;
					  target->receive_wound("jing", damage, me);					 
				 }
               
        } else
        {
                if (weapon2)
                        msg += CYN "$n" CYN "见$N" CYN "来势凶猛，不敢正面抵挡，手中" + weapon2->name() + CYN "一颤侧击" + weapon->name() + CYN "的剑脊\n"
                               CYN "$N" CYN "被缓得一缓，『不归式』已然落空！\n" NOR;
                else
                        msg += CYN "$n" CYN "见$N" CYN "来势凶猛，不敢正面抵挡，侧身进步双掌奋力侧击$N" CYN "\n"
                               CYN "$N" CYN "被缓得一缓，『不归式』已然落空，但$n" CYN "也被$N" CYN "震得气血翻涌！\n" NOR;
        }
		  message_vision(msg, me, target);
		}

        me->start_busy(3 + random(3));
        
        me->add("neili", -400);
        return 1;
}


