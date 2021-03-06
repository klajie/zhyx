//佛祖(转世npc)

#include <ansi.h>
inherit  NPC;
inherit  F_SAVE;

//尚差性别

int ask_reborn();

nosave string *word = ({
"班", "若", "菠", "萝", "密", "啊", "吗", "咪", "哄",
"度", "众", "生", "者", "应", "明", "以", "何", "得",
"有", "空", "净", "相", "我", "虚", "妄", "情", "少",
"福", "如", "來", "法", "金", "思", "悟", "灭", "失",
});

void create()
{
        seteuid(getuid());
        restore();
        set_name(HIY "释迦牟尼" NOR, ({ "buddha", "fo zu",
                "fo", "shijia muni" }));
        set("long", @LONG
佛祖庄严宝像，让人不敢正视。
LONG);

        if (clonep())
                destruct(this_object());
        else {
                set("nickname", HIW "三界法王" NOR);
                set("title", HIC "佛祖" NOR);
                set("gender", "男性" );
                set("age", 500);
                set("attitude", "friendly");
                set("max_jing", 99999);
                set("max_qi", 99999);
                set("max_jingli", 99999);
                set("jingli", 99999);
                set("max_neili", 99999);
                set("neili", 99999);
                set("jiali", 9999);
                set("str", 99);
                set("int", 99);
                set("con", 99);
                set("dex", 99);
                set("combat_exp", 99999999);

                set_skill("dodge", 999);
                set_skill("unarmed", 999);
                set_skill("force", 999);
                set_skill("parry", 999);
                set_skill("sword", 999);
                set_skill("medical", 999);
                set_skill("literate", 999);
                set_skill("lamaism", 999);
                set_skill("buddhism", 999);
                set_skill("shaolin-yishu", 999);
                set_skill("idle-force", 999);
                set_skill("huntian-baojian", 999);
                set_skill("lunhui-jian", 999);

                map_skill("force", "huntian-baojian");
                map_skill("parry", "lunhui-jian");
                map_skill("sword", "lunhui-jian");
                map_skill("medical", "shaolin-yishu");

                set("inquiry", ([
                    "转世重生" : (: ask_reborn :),
                ]));
                set("chat_chance_combat", 200);
                set("chat_msg_combat", ({
                        (: perform_action, "sword.hui" :),
                        (: exert_function, "recover" :),
                        (: exert_function, "powerup" :),
                        (: exert_function, "shield" :),
                        (: exert_function, "heal" :),
                        (: exert_function, "dispel" :),
                        (: exert_function, "regenerate" :),
                }));
             }

        setup();
        carry_object("d/city/obj/jiasha")->wear();
        carry_object("/d/city/obj/changjian")->wield();
}

// 毁灭时保存进度
void remove()
{
        save();
}

// 存盘文档
string query_save_file()
{
        return "/data/reborn/buddha";
}

void init()
{
     add_action("do_decide", "decide");

}


int ask_reborn()
{
    object me;
    object *inv;
    me = this_player();

    command("look " + me->query("id"));

    if ( me->query("reborn") )
    {
       command("say 你的阿赖耶识不是已经打开了吗？");
       return 1;
    }

    if ( me->query_skill("martial-cognize",1) < 600 )
    {
       command("say 给我滚开！你连武学修养都不够，你是怎么上来的？");
       return 1;
    }

 /*   if ( ! me->query("reborn_ok") ) //判断是否已完成所有转世任务
    {
        command("say 你好像还没到能重生的境界吧？");
        return 1;
    }*/

    command("say 你可是也对此生感到困惑，想要探寻人生真谛吗？");
    command("say 若要转生则你之武学就将尽毁，你可愿意？");
    message_vision(HIC"$N" HIC"对$n" HIC"道：若你心意已决就输入"
                   "decide吧！\n"NOR, this_object(), me);
    me->set_temp("reborn_start/ask",1);
    return 1;
}

int do_decide()
{
    int i;
    string msg;


    object me = this_player();
    msg = "";


    if ( ! me->query_temp("reborn_start/ask"))
        return 0;

    tell_object(me, HIW"佛祖在你耳边说道：我告诉你一句揭语，"
                "你可参悟一下是啥意思，\n来世你若有缘再见到我，"
                "凭此揭语我会给你开启前生记忆！\n"
                "此揭语须当谨记在心，切记切记！\n"NOR);

    for( i = 0; i < 5; i++)
        msg += word[random(sizeof(word))];

    tell_object(me, HIY"\n佛祖在你耳边说道，给你的揭语是："HIR + msg + "\n"NOR);
    tell_object(me, HIY"记下了吗?我即刻就送你去投胎了!\n\n"NOR);

    remove_call_out("reborn");
    call_out("reborn", 5, me, msg);
    return 1;
}

int reborn(object me, string msg)
{
    int i;

    set("data/" + me->query("id") + "/reborn_time", time());
    set("data/" + me->query("id") + "/pass", msg);

    set("data/" + me->query("id") + "/str", me->query("str"));
    set("data/" + me->query("id") + "/int", me->query("int"));
    set("data/" + me->query("id") + "/con", me->query("con"));
    set("data/" + me->query("id") + "/dex", me->query("dex"));

    set("data/" + me->query("id") + "/sun", me->query("gift/sun"));
    set("data/" + me->query("id") + "/water", me->query("gift/water"));
    set("data/" + me->query("id") + "/feng", me->query("gift/feng"));
    set("data/" + me->query("id") + "/lighting", me->query("gift/lighting"));

    for( i = 0; i < sizeof(me->query("special_skill")); i++)

       set("data/" + me->query("id") + "/special_skill/" + i,
            keys( me->query("special_skill"))[i] );


    save();

    message("vision", HIG"【天界传闻】" + me->query("name") + "(" +
             me->query("id") + ")" + "已得佛祖恩准，即时转世重生！\n"NOR, users());

    message_vision("只见$N化作一屡轻烟，渐渐消失了……\n", me);

    UPDATE_D->remove_user(me->query("id"));

    return 1;
}
