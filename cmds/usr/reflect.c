// reflect.c
// 冥思指令获取少量经验和潜能
// 会员专用指令 Create by Rcwiz for HERO.CD

#include <ansi.h>
#define MEMBER_D     "/adm/daemons/memberd"

inherit F_CLEAN_UP;

void end_reflect(object me)
{
         int exp, pot;

         if (me->query_temp("reflect"))
         {
               message_vision(HIY "$N" HIY "冥思完毕，缓缓地睁开眼睛，似乎若有所悟！\n" NOR, me);
 
               me->delete_temp("reflect");

               exp = me->query("combat_exp");               
               exp /= 50000;
               pot = exp / 5;

               exp = exp + random(exp / 2);
               pot = pot + random(pot / 2);

               me->add("combat_exp", exp);
               me->add("potential", pot);

               write(HIG "通过这次冥思，你获得了" HIC + chinese_number(exp) + HIG 
                     "点实战经验和" HIC + chinese_number(pot) + HIG "点潜能。\n");

         }

         if (me->is_busy())me->start_busy(1);
         return;
}

int main(object me)
{
         object ob;


         if (me->is_busy() || me->is_fighting())
                 return notify_fail("等你忙完再说吧！\n");

         if (me->query_temp("reflect"))
                 return notify_fail("你正在冥思。\n");

         if (! wizardp(me) && ! MEMBER_D->is_valib_member(me->query("id")))
                 return 0;

         if (! me->query("doing"))
                 return notify_fail("只有计划时才能冥思。\n");

         if (me->query("combat_exp") < 1000000)
                  return notify_fail("你实战经验，无法冥思。\n");

         if (me->query_skill("martial-cognize", 1) < 160)
                  return notify_fail("你武学修养不足，无法冥思。\n");
 

         me->set_temp("reflect", 1);

         me->start_busy(30);

         me->start_call_out((: call_other, __FILE__,
                             "end_reflect", me:), 28 + random(6));

         message_vision(HIY "$N" HIY "盘膝而坐，闭目冥思 ……\n" NOR, me);

         return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : reflect

该指令可以在计划时使用以提高少量经验和潜能。
该指令只限会员使用。

HELP
);
    return 1;
}
 
