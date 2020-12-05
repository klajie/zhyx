// beg.c

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string what, who;
        object ob, victim;
        int sp, dp;

        object where = environment(me);

        seteuid(getuid());

        if (me->query("family/family_name") != "丐帮")
                  return notify_fail("只有乞丐才能乞讨。\n");
/*
       if (environment(me)->query("no_steal"))
//           || environment(me)->query("no_steal"))
                return notify_fail("这里不是你叫化子能来讨饭的地方。\n");
*/
        if (me->query_temp("begging"))
                return notify_fail("你已经在向人家乞讨了。\n");

        if (! arg || sscanf(arg, "%s from %s", what, who) != 2)
                return notify_fail("指令格式：beg <物品> from <人物>\n");

        victim = present(who, environment(me));

        if (! victim || victim == me)
                return notify_fail("你想乞讨的对象不在这里。\n");

        if (! living(victim) || ! objectp(victim))
                return notify_fail("你要向谁乞讨？\n");
        if (playerp(victim))
                return notify_fail("你要向谁乞讨？\n");

       // if( playerp(me) && userp(victim)&& victim->query("combat_exp")/50 > me->query("combat_exp") )
       //         return notify_fail(victim->name()+"不会施舍给你任何东西的。\n");
        if (victim->query("family/family_name") == "丐帮")
                return notify_fail("那家伙是乞丐，乞讨不出什么。\n");

        if (! wizardp(me) && wizardp(victim))
                return notify_fail("你掂量了一下，觉得还是别惹那家伙为妙。\n");

        if (me->is_busy())
                return notify_fail("你现在正忙着呢。\n");

        if (me->is_fighting())
                return notify_fail("你还是先把你面前的家伙放倒再说吧。\n");

        if (victim->is_fighting())
                return notify_fail(victim->name() + "正在打架，没空理你。\n");

        ob = present(what, victim);
        //if (! ob) ob = present("cash", victim);
        //if (! ob) ob = present("gold", victim);
        //if (! ob) ob = present("silver", victim);
        //if (! ob) ob = present("coin", victim);
        if (! ob)
                return notify_fail("看起来" + victim->name() + "身上没有什"
                                   "麽让你感兴趣的东西。\n");

        if (ob->query("equipped") || ob->query("no_drop"))
                return notify_fail("这是那人的随身家伙，肯定不会给你。\n");
        //	if (!ob->query("dynamic_quest")&&!ob->query("money_id"))
        //	return notify_fail("该物品你不能乞讨到的。\n");
        sp = (int)me->query_skill("begging");
        sp = sp * sp * sp / 10;

        if (sp < 1) sp = 1;
        dp = (int)victim->query("jing")/ 5;

        message_vision(WHT "只见$N" WHT "可怜巴巴地向$n"
                       WHT "伸手说道：这位" + RANK_D->query_respect(victim) +
                       WHT "，行行好，能把"+ob->query("name")+NOR+WHT"给我吗。\n" NOR, me, victim);

        me->set_temp("begging", 1);
        call_out( "compelete_beg", 2, me, victim, ob, sp, dp);
        return 1;
}

private void compelete_beg(object me, object victim, object ob, int sp, int dp)
{
        int amount;
        int bcount;
        object ob1;
        object where;

        if (! objectp(me))
                return;

        me->delete_temp("begging");

        where = environment(me);

        if (! objectp(ob) || ! living(me) || me->is_fighting())
                return;

        if (! victim || environment(victim) != environment(me))
        {
                tell_object(me, "太可惜了，你要乞讨的人已经走了。\n");
                return;
        }

        if (environment(ob) != victim)
        {
                tell_object(me, "太可惜了，人家好像已经没有" +
                                ob->name() + "了。\n");
                return;
        }
                if(!victim->query("int")) {
                tell_object(me,victim->name()+"根本就无动于衷！\n");
                return;
        }
        if (!ob->query("dynamic_quest")&&!ob->query("money_id"))
         {
                message_vision(HIR "$n" HIR "狠狠地瞪了$N"
                                       HIR "一眼，喝道：滚开。$N"
                                       HIR "只好灰溜溜地走开了。\n"
                                       NOR, me, victim);
                                         tell_object(me, HIG"该物品你不能乞讨到的。\n"NOR);
                return;
        }
        //	return notify_fail("该物品你不能乞讨到的。\n");
      /*
       if ((random(sp + dp) > dp)||ob->query("money_id"))
        {
                if (! ob->query("money_id") || ! (amount = ob->query_amount()))
                {
                        tell_object(me, HIY "看来还是走吧，这家伙身上已经"
                                        "没有多少油水可榨了。\n" NOR);
                        return;
                }

                bcount = amount / 5;
                if (! bcount) bcount = 1;
                ob->set_amount(amount - bcount);

                ob1=new("/clone/money/" + ob->query("money_id"));
                ob1->set_amount(bcount);
                ob1->move(me);

                message_vision(HIC "$n" HIC "皱了皱眉，接着叹了口气，摸出" +
                               ob1->query("unit") + ob1->name() +
                               HIC "扔给$N" HIC "。\n" NOR, me, victim);

                      if (me->can_improve_skill("begging"))
                          me->improve_skill("begging", random(me->query("int")));

                      if ((int)me->query("potential") < (int)me->query_potential_limit())
                        me->add("potential", 1);

                me->add("combat_exp", 1);
                me->start_busy(3 + random(4));
                return;
        }*/
        if((random(sp + dp) > dp)&&random(100)>50)
        {
                message_vision("$N看着$n的可怜样，叹了口气，丢给$n一"
                                + ob->query("unit") + ob->name() + "。\n",victim,me);
                if (me->can_improve_skill("begging"))
                          me->improve_skill("begging", random(me->query("int")));
                          ob->move(me);
                if ((int)me->query("potential") < (int)me->query_potential_limit())
                        me->add("potential", random(3));
                me->start_busy(3);
                me->add("state/beg", 1);
        }
         else
        {
                if (random(sp) > dp)
                {
                        message_vision(HIR "$n" HIR "狠狠地瞪了$N"
                                       HIR "一眼，喝道：滚开。$N"
                                       HIR "只好灰溜溜地走开了。\n"
                                       NOR, me, victim);
                        me->start_busy(3);
                        return;
                }
                message_vision(CYN "$n" CYN "，冷哼一声，对$N"
                               CYN "想死啊。\n" NOR, me, victim);
                victim->fight_ob(me);
             // me->start_busy(3);
                   //     return;
           }
}

int help(object me)
{
write(@HELP
指令格式：beg <财物> from <某人>

如果你是叫花子，可以用这个命令来乞讨点钱。
HELP);
        return 1;
}
