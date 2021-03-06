// story:zijinxunzhang 紫金勋章

#include <ansi.h>

inherit F_CLEAN_UP;

mixed random_gift();

nosave mixed *story = ({
        "上古，神界",
        "盘古:“女娲，很久不见，依然那么漂亮。”",
        "女娲:“哟，你个粗人今天嘴怎么那么甜？”",
        "盘古:“见到你我就开心啊，今天我要送你一件宝贝。”说罢，盘古拿出一块亮闪闪的东西递给女娲。",
        "女娲接过来一看，问道:“这是什么东西？”",
        "盘古:“这是紫金勋章，世间少有，我今天好不容易才在马路上捡到一块。”",
        "女娲:“平白无故送人东西，你有事情求我吧？”",
        "盘古想了想，道:“你看咱俩认识也那么久了，要不你搬过来咱俩一起过吧。”",
        "女娲脸色“唰”的一下就红了，沉吟不语。",
        "盘古:“到底行还是不行，你说句话呀？”",
        "女娲:“可我已经有意中人了，你还是换个人吧。”",
        "盘古气愤异常，一把抢过勋章，扭头走了，留下女娲怔怔的站着。",
        "盘古心想:他奶奶的，你看不上我，老子穿越回三国找貂蝉去。",
        "盘古:“哎呀，糟了，我的勋章哪去了？”",
        (: random_gift :),
});

void create()
{
        seteuid(getuid());
}

string prompt() { return HIM "【紫金勋章】" NOR; }

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

mixed random_gift()
{
        object *obs;
        object ob;
        object *gobs;
        object gob;
        string msg;
        mapping my;
        int select;

        select = 0;

        gobs = ({
                "/clone/fam/max/learn-emblem.c",
                "/clone/fam/max/practice-emblem.c",
                "/clone/fam/max/research-emblem.c",
                "/clone/fam/max/research-emblem2.c",
        });
        gob = gobs[random(sizeof(gobs))];
        obs = filter_array(all_interactive(), (:  ! wizardp($1) &&
                                                 living($1) &&
                                                 $1->query("kar") > 40 &&
                                                 $1->query("per") < 20 &&
                                                 environment($1)->query("outdoors") &&
                                                 ! $1->query("story/zijinxunzhang") &&
                                                 ! $1->query("doing") :));
        if (! sizeof(obs))
                return 0;

        ob = obs[random(sizeof(obs))];

        if (random( 5200 -  ob->query("kar") * 100 ) > 0 )
        {
                msg = HIC "盘古：" + ob->name(1) +
                      HIC "把勋章还我，他奶奶的，你也配拿这东西？说罢一把抢过勋章。" NOR;

        } else
        {
                msg = HIY "盘古：靠，" + ob->name(1) +
                      HIY "居然敢捡老子的东西，下次被我碰到，定饶不了他。" NOR;
                gob->move(ob, 1);
                ob->set("story/zijinxunzhang", 1);
                select = 1;

        }
        remove_call_out("announce");
        call_out("announce",1,select,ob);
        return msg;
}

void announce(int select, object ob)
{
      if (select == 0 )
      CHANNEL_D->do_channel(this_object(), "rumor",
         "听说" + ob->name() +"想偷盘古的紫金勋章，结果招人发现被痛打了一顿。\n");
      else
      CHANNEL_D->do_channel(this_object(), "rumor",
           "听说" + ob->name() + "捡到了神奇的紫金勋章。\n");
}
