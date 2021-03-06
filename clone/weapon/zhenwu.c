#include <weapon.h>
#include <ansi.h>

inherit SWORD;
inherit F_NOCLONE;

string do_wield();
string do_unwield();

void create()
{
        set_name(HIY "真武剑" NOR,({ "zhenwu jian", "jian", "sword", "zhenwu" }) );
        set_weight(1500);
        if (clonep())
                destruct(this_object());
        else {
                set("long", @LONG
这是一柄寒光闪闪的宝剑，昔年武当张真人持此剑荡妖除魔，扫尽群丑。
江湖宵小，见此剑无不心荡神摇。
LONG );
                set("unit", "把");
                set("value", 800000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", (: do_wield :));
                set("unwield_msg", (: do_unwield :));
        }
        init_sword(200);
        setup();
}

string do_wield()
{
        object me;

        me = this_player();
        remove_call_out("check_npc");
        call_out("check_npc", 0, me, environment(me));
        if (me->query("shen") > 10000)
        {
                me->set_temp("apply/attack", me->query_skill("sword") / 4);
                me->set_temp("apply/defense", me->query_skill("parry") / 4);
                return HIC "$N一声长啸，将$n" HIC "荡出剑鞘，霎时天地间浩气凛然。\n" NOR;
        } else
        if (me->query("shen") >= 0)
        {
                return HIC "$N一伸手，已然把$n" HIC "亮在手中。\n" NOR;
        } else
        if (me->query("shen") > -10000)
        {
                me->set_temp("apply/attack", -me->query_skill("sword") / 5);
                me->set_temp("apply/defense", -me->query_skill("parry") / 5);
                return HIG "$N战战兢兢的摸出一把$n" HIG "。\n" NOR;
        } else
        {
                return HIG "$N一声冷笑，“唰”的一声亮出了$n" HIG "。\n" NOR;
        }
}

string do_unwield()
{
        object me;

        me = this_player();
        remove_call_out("check_npc");
        me->delete_temp("apply/attack", me->query_skill("sword") / 4);
        me->delete_temp("apply/defense", me->query_skill("parry") / 4);
        if (me->query("shen") >= 0)
                return HIC "$N一挥手，还剑入鞘。\n" NOR;
        else
        if (me->query("shen") > -10000)
                return HIG "$N把$n" HIG "插回剑鞘，抹了抹头上的汗。\n" NOR;
        else
                return HIG "$N一晒，把$n" HIG "插回剑鞘。\n" NOR;
}

void check_npc(object me, object env)
{
        object *ob;
        int i;

        if (! objectp(me) || ! living(me))
                return;

        if (environment(me) != env)
                return;

        ob = all_inventory(env);
        for (i = 0; i < sizeof(ob); i++)
        {
                if (! ob[i]->is_character() || ob[i] == me ||                    
                    ! living(ob[i]) || ob[i]->query("not_living") ||
                    ob[i]->query("id") == "zhang sanfeng")
                        continue;

                if (me->is_bad())
                {
                        if (userp(ob[i]))
                                continue;

                        if (ob[i]->query("shen") > 10000)
                        {
                                message_vision("$N大怒喝道：好你个" + RANK_D->query_rude(me) +
                                               "，居然敢盗用真武剑？\n", ob[i]);
                                if (! env->query("on_fight"))
                                        ob[i]->kill_ob(me);
                        } else
                        if (ob[i]->is_bad())
                        {
                                message_vision(random(2) ? "$N哈哈大笑，对$n道：干得好，干得好。\n" :
                                                           "$N拼命鼓掌，对$n道：兄弟加油干啊！",
                                               ob[i], me);
                        }
                        continue;
                }

                if (me->is_not_good())
                        continue;

                if (ob[i]->query("shen") > 10000 && ! userp(ob[i]))
                {
                        message_vision(random(2) ? "$N赞道：好剑，好剑！\n" :
                                                   "$N叹道：见此剑真是如见张真人啊！\n",
                                       ob[i]);
                } else
                if (ob[i]->query("shen") < -10 && ! userp(ob[i]))
                {
                        int ob_exp, my_exp;
                        ob_exp = ob[i]->query("combat_exp");
                        my_exp = me->query("combat_exp");
                        if (ob_exp > my_exp * 2 || ob_exp > 1500000)
                        {
                                message_vision(random(2) ? "$N对$n冷冷道：滚开！少在我面前卖弄。\n" :
                                                           "$N一声冷笑，对$n道：你以为你是谁？张三丰？哈哈哈哈！\n",
                                               ob[i], me);
                        } else
                        if (ob_exp > 20000)
                        {
                                message_vision(random(2) ? "$N脸色有些不对劲。\n" :
                                                           "$N露出害怕的神色。\n",
                                               ob[i]);
                                if (env->query("no_fight"))
                                        continue;
                                message_vision(random(2) ? "$N怒喝一声，“大家都不要活了！”\n" :
                                                           "$N一言不发，忽的扑向$n，身形极快。\n",
                                               ob[i], me);
                                ob[i]->kill_ob(me);
                        } else
                        {
                                message_vision(random(2) ? "$N扑通一声，瘫倒在地，双手急摇道：“不是我！真的不是我！”\n" :
                                                           "$N一个哆嗦，结结巴巴的什么也说不上来。\n",
                                               ob[i], me);
                                if (! env->query("no_fight"))
                                        ob[i]->unconcious();
                        }
                }
        }
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->is_bad() || victim->is_good())
                return - damage_bonus / 2;

        if (me->is_not_good() || victim->is_not_bad())
                return 0;

        if (me->query_skill_mapped("sword") != "taiji-jian" ||
            me->query_skill("taiji-jian", 1) < 100)
                // only increase damage
                return damage_bonus / 2;

        switch (random(4))
        {
        case 0:
//                victim->start_busy(me->query_skill("sword") / 10 + 2);^M
                return HIC "$N跨前一步，手中的" NOR+HIY "真武剑" NOR+HIC "幻化成无数圆圈，"
                       "向$n逼去，剑法细密之极。$n大吃一\n"
                       "惊，不知如何抵挡，只有连连后退。\n" NOR;

        case 1:
                n = me->query_skill("sowrd");
                victim->receive_damage("qi", n, me);
                victim->receive_wound("qi", n, me);
                n = victim->query("eff_jing");
                n /= 2;
                victim->receive_damage("jing", n, me);
                victim->receive_wound("jing", n / 2, me);
                return random(2) ? HIY "$N一声长吟，手中的真武剑化作一到长虹，“唰”的扫过$n。\n" NOR:
                                   HIY "$N突然大声喝道：“邪魔外道，还不受死？”手中真武剑"
                                   HIY "忽的一抖，$n登时觉得眼前一花。\n" NOR;
        }

        // double effect
        return damage_bonus;
}


