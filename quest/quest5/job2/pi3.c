// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// pi.c 裨将 朱雀内门

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("裨将", ({ "pi jiang", "pi", "jiang" }));
        set("gender", "男性");
        set("age", random(10) + 30);
        set("str", 25);
        set("dex", 16);
        set("long", "这是一个大宋年轻将领，满脸征尘。\n");
        set("combat_exp", 45000);
        set("shen_type", 1);
        set("attitude", "peaceful");

        set_skill("unarmed", 60);
        set_skill("force", 60);
        set_skill("sword", 60);
        set_skill("dodge", 60);
        set_skill("parry", 60);
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/armor", 50);
        set_temp("apply/damage", 30);

        set("neili", 400); 
        set("max_neili", 400);
        set("jiali", 10);

        setup();
        carry_object("/d/city/obj/changjian")->wield();
        carry_object("/d/city/obj/tiejia")->wear();
}

void init()
{       
        object ob;

        ::init();

        if (objectp(ob = this_player()) && ! is_fighting()) 
        {
                // remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if (! ob || environment(ob) != environment()) 
                return;

        if (ob->query_temp("guo_shoucheng/start_job") == 1)
                say("裨将皱了皱眉：这位" + RANK_D->query_respect(ob) + "，你还是安心守城吧。\n");
        else 
        if (ob->query_temp("guo_shoucheng/mark_shadi") == 3
        &&  ! ob->query_temp("guo_shoucheng/job_over"))
        {
                say("裨将拱手说道：这位" + RANK_D->query_respect(ob) + "，你来得正是时候，金兵已经快攻上城了。\n");
                
                ob->apply_condition("jobshadi_limit", 10 + random(5));
                ob->set_temp("guo_shoucheng/start_job", 1);
                ob->set_temp("guo_shoucheng/where", environment(ob));
                // remove_call_out("to_rob");
                call_out("to_rob", 10, ob);
        } else
        if (ob->query_temp("guo_shoucheng/job_over"))
        {
                say("裨将拱手说道：这位" + RANK_D->query_respect(ob) + "，你已经可以回去复命了。\n");
                return;
        } 

}

void to_rob(object ob)
{
        object *target, robber, room;              
        int i;
        
        if (! ob || environment(ob) != environment()) 
                return;

        room = environment(ob);
        
        if (environment(ob)->query("short") == "朱雀内门")
        {
                robber = new(__DIR__"robber1");
                robber->do_change(ob);
                robber->set("want_kill", ob);
                robber->move(room);
                message_vision(HIR "突然城下爬上来一个金兵兵士。\n" NOR, this_player()); 
                robber->kill_ob(ob);
                ob->kill_ob(robber);
        }
}

void unconcious()
{
        return;
}

void die()
{
        return;
}
