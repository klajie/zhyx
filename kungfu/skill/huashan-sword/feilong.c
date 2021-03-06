// Code of HuaXia
// feilong.c 天外飞龙
/************************************************************************************
修改时间：2003-11-28
修改人：  smallfish
修改说明：1、几个杀伤力计算方程式中，变更最厉害的那个杀伤力方程式（第一个方程式）
          旧方程式：
          damage = target->query("max_qi")/2;
          damage += random(damage);
          新方程式：
          damage = target->query("max_qi")/2;
          damage += random(damage-10);
          2、如果未击中对方，则使用者将受到天外飞龙的反噬
          3、由于天外飞龙伤害方程式计算的是百分比，因此需要考虑天魔解体对杀伤力的影响
************************************************************************************/

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
        mapping prepare_status;
        string weapon, op_weapon, op_skill, *pname;
        int my_power, op_power, my_li, op_li, my_jing, my_nei, op_jing, op_nei, damage, jieti;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("天外飞龙只能对战斗中的对手使用。\n");

        if (userp(me) && ! me->query("can_perform/huashan-sword/feilong"))
                return notify_fail("天外飞龙乃是华山剑宗不传之密，你还没有学到！\n");

        if( me->query_skill_mapped("force") != "zixia-shengong" )
                return notify_fail("你所用的并非紫霞功，无法运劲施展天外飞龙！\n");

        if(me->query_skill_mapped("sword") != "huashan-sword") 
                return notify_fail("你并未使用华山剑法，无法使出天外飞龙！\n");

        if( me->query_skill("force") < 100 )
                return notify_fail("你的紫霞功火候未到，无法运劲施展天外飞龙！\n");

        if( me->query_skill("sword") < 150 )
                return notify_fail("你华山剑法修为不足，还不会使用天外飞龙！\n");

        if( me->query("neili") <= 400 )
                return notify_fail("你的内力不够使用天外飞龙！\n");
        if( me->query("jingli") <= 200 )
                return notify_fail("你的精力不够使用天外飞龙！\n");

        weapon = me->query_temp("weapon");

        if ( !objectp(op_weapon = target->query_temp("weapon")) ) {
                 if ( mapp(prepare_status = target->query_skill_prepare()) && sizeof(prepare_status)) {
                        pname  = keys(prepare_status);
                        op_skill = pname[0];
                }
                else op_skill = "unarmed";
        }
        else {
                op_skill = op_weapon->query("skill_type");
        }

        my_jing = me->query("jingli") * 8 / 10;
        my_nei = me->query("neili") * 8 / 10;

        if ( target->query("neili") < me->query("neili") ) {
                op_nei = target->query("neili")*9/10;
        }
        else op_nei = my_nei;

        if ( target->query("jingli") < me->query("jingli") ) {
                op_jing = target->query("jingli")*9/10;
        }
        else op_jing = my_jing;

        message_vision(HIG "\n$N剑走龙蛇，紫气如电，凝重处如山岳巍峙，轻灵处若清风无迹，变幻莫测。\n"
                           "舞到急处，$N一声大喝，"+weapon->name()+"脱手飞出，化作一道惊虹射向$n！\n\n" NOR, me, target);
        tell_object(target, HIR "你只觉得敌招来势猛恶无伦，压得你透不过气来！\n" NOR);

        my_power = me->query_skill("sword") + me->query_skill("dodge") + me->query_skill("force")
                   + me->query_skill("parry") + me->query("combat_exp") / 10000;
                
        my_li = me->query("jingli") + me->query("neili");

        if (living(target))
        {
           op_power = target->query_skill(op_skill) + target->query_skill("dodge") + target->query_skill("force")
                      + target->query_skill("parry") + target->query("combat_exp") / 10000;
           op_li = target->query("jingli") + target->query("neili");
        }  else
        {
           op_power = 1;
           op_li = 1;
        }

        if ( random(my_power) > op_power/2 ) 
        {
           if ( random(my_li) > random(op_li) ) 
           {
                if ( objectp(op_weapon) ) 
                {
                        message_vision(HIR "$N闪避不及，只好咬牙举起"+op_weapon->name()+"奋起全力强接攻势。\n" NOR, target);
                        message_vision(HIR "硬碰之下，"+op_weapon->name()+"竟断为几截，但仍阻不了飞剑来势！\n" NOR, target);
                        op_weapon->unequip();
                        op_weapon->move(environment(me));
                        op_weapon->set("name", "断掉的" + op_weapon->name());
                        op_weapon->set("value", 0);
                        op_weapon->set("weapon_prop", 0);
                }
                message_vision(HIR "$N避无可避，发出一声凄历的惨嚎，"+weapon->name()+"穿身而过！\n" NOR, target);
                weapon->move(target);
                damage = (int)target->query("max_qi")/2;
                damage += random(damage-10);                     //SMALLFISH修改，防止满血状态一招夺命
           }
           else if ( me->query_str() > target->query_str() ) 
           {
                if ( objectp(op_weapon) ) 
                {
                        message_vision(HIR "硬砰之下，"+op_weapon->name()+"竟断为几截，终於抵消了飞剑来势！\n" NOR, target);
                        message_vision("飞剑攻势受阻，力尽跌落。$N虽挡过一击，却也因精力内力钜耗，摇摇欲坠！\n", target);
                        weapon->move(environment(me));
                        op_weapon->unequip();
                        op_weapon->move(environment(me));
                        op_weapon->set("name", "断掉的" + op_weapon->name());
                        op_weapon->set("value", 0);
                        op_weapon->set("weapon_prop", 0);
                        damage = (int)target->query("max_qi")/4;
                        damage += random(damage);
                } else {
                        message_vision(HIR "$N奋力闪躲，但却力有不逮，发出一声凄历的惨嚎，中剑重伤！\n" NOR, target);
                        damage = (int)target->query("max_qi")/3;
                        damage += random(damage);
                }
           }
           else if ( random(2) == 1 && objectp(op_weapon) ) 
           {
                message_vision(HIR "硬砰之下，$N的"+weapon->name()+"及$n的"+op_weapon->name()+"双双跌下！\n" NOR, me, target);
                weapon->move(environment(me));
                op_weapon->move(environment(me));
                damage = (int)target->query("max_qi")/5;
           }
           else if ( objectp(op_weapon) ) 
           {
                message_vision(HIR "硬砰之下，$N的"+weapon->name()+"及$n的"+op_weapon->name()+"双双损毁！\n" NOR, me, target);
                op_weapon->unequip();
                op_weapon->move(environment(me));
                op_weapon->set("name", "断掉的" + op_weapon->name());
                op_weapon->set("value", 0);
                op_weapon->set("weapon_prop", 0);
                weapon->unequip();
                weapon->move(environment(me));
                weapon->set("name", "断掉的" + weapon->name());
                weapon->set("value", 0);
                weapon->set("weapon_prop", 0);
                damage = (int)target->query("max_qi")/5;
           }
           else 
           {
                message_vision(HIR "$N奋力闪躲，但却力有不逮，发出一声凄历的惨嚎，中剑受伤！\n" NOR, target);
                damage = (int)target->query("max_qi")/5;
           }

           //Add By Smallfish:修正天魔解体对杀伤力的变化
           jieti = me->query("tianmo_jieti/times");
           if (jieti>5) jieti = 5;
           damage -= damage*jieti/(5+jieti);
           //修改结束
           
           target->receive_wound("qi", damage, me);
           target->add("jingli", -op_jing);
           target->add("neili", -op_nei);
           target->start_busy(1+random(2));
           me->start_busy(3+random(2));
        }
        else 
        {
                message_vision(HIY "$N身形连闪，只守不攻，好不容易将此招避过，已吓得亡魂直冒！\n" NOR, target);
                message_vision(HIY "一击未中，"+weapon->name()+"嗖的一声又飞回$N手中。\n" NOR, me);
                tell_object(me, HIR "你只觉得气血一阵翻腾，极为难受，不由暗暗心惊！\n" NOR);
                
                //Add By Smallfish：天外飞龙太过霸道，如果击不中对方，自己则会受到反噬
                damage = (int)me->query("max_qi")/6;
                damage += random(damage);
                my_li = (int)me->query("qi");
                if (damage>=my_li && my_li>0) damage = my_li - 1;
                
                jieti = target->query("tianmo_jieti/times");
                if (jieti>5) jieti = 5;
                damage -= damage*jieti/(5+jieti);

                me->receive_wound("qi", damage, target);
                me->start_busy(4 + random(3));
        }

        me->setup();
        me->add("neili", -my_nei);
        me->add("jingli", -my_jing);
        target->kill_ob(me);

        return 1;
}

