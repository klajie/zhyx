//xym_yz_npc.c

#include <ansi.h>

inherit NPC;

#define PLACE "yz"     //扬州分舵
#define TYPE  "good"    //白道
#define WAIT_TIME 60    //完成不了任务的反省时间

mapping bang_good = ([
        "name" : "侠义盟",
        "id"   : "xym",
        "place": "ca",      //总舵
        "boss" : "成中岳",
        "place_name" : "扬州" //分舵
]);

void create()
{
        set_name("郑云虎", ({ "zheng yunhu", "zheng" }));
        set("gender", "男性");
        set("age", 38);
        set("long", "他就是" + bang_good["name"] + "设在" + bang_good["place_name"] + "的分舵舵主。\n");
        set("nickname",HIY"无敌三板斧"NOR);
        set("title",GRN"侠义盟扬州分舵舵主"NOR);
        set("per",18);
        set("combat_exp", 800000);
        set("shen_type", 1);

        set("attitude", "peaceful");
        
        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver",2);
}
#include <boss_good.h>

