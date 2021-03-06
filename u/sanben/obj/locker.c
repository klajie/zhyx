//密码箱

#include <ansi.h>

inherit ITEM;
inherit F_SAVE;

nosave int load;
int do_cun(string arg, int all);

void create()
{

        set_name(HIY "密码箱" NOR, ({ "locker" }));
        set_weight(1000);

        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", YEL "这是密码箱,知道密码的人可以存取物品。\n"
                                "使用方法如下: \n"
                                "    输入密码打开箱子:  type <密码>\n"
                                "    更换密码(仅限屋主):changeto <新密码>\n"
                                "    锁箱子: lock\n"
                                "    查询物品编号: check\n"
                                "    存入身上所有物品:cun all\n"
                                "    存入某个物品: cun <数量> <物品id>\n"
                                "    取物品: qu <数量> <物品编号>\n"NOR);

                set("value", 100);
                set("unit", "个");
                set("no_get", 1);

        }
        setup();
}
/*
string long()
{
        object ob;
        string msg;

        msg = query("long");
        if (query("open"))
            msg += HIG "密码箱目前是开着的。\n" NOR;
        else
            msg += HIR "密码箱目前是关着的，请先用type输入密码。\n\n" NOR;

        return msg;

}

void init()
{
        string owner;

        object env = environment(this_object());

        if (! load)
        {
                env = environment(this_object());
                if (stringp(owner = env->query("room_owner_id")))
                        set("owner", owner);

                restore();
                delete("open");
                load = 1;
        }


        add_action("do_type", "type");
        add_action("do_changeto", "changeto");
        add_action("do_lock", "lock");
        add_action("do_check", "check");
        add_action("cun_check", "cun");
        add_action("do_qu", "qu");
}

int do_type(string arg)
{
    if (!arg)
       return notify_fail("你要输入的密码是什么?\n");

    if (! query("passwd"))
       return notify_fail("此箱尚未设置密码!\n"
              "必须等屋主用changeto设置密码后方可使用!\n");

    if (query("open"))
        return notify_fail("这个密码箱已经是开着的了!\n");

    if (arg != query("passwd"))
      return notify_fail(HIR"密码错误!你不能使用这个箱子!\n"NOR);

    set("open", 1);
    message_vision(HIC "只见$N" HIC "在密码箱上按了几下,"
                   "箱子就打开了。\n"NOR, this_player());

    return 1;
}


int do_changeto(string arg)
{
    object me;
    me = this_player();

    if (query("owner") != me->query("id"))
       return notify_fail(HIR"只有屋主才能修改密码!\n"NOR);

    if ( !arg)
       return notify_fail("你要把密码改成什么?\n");

    if (sizeof(arg) > 6 )
       return notify_fail("对不起,密码最多只能设置六位!\n"NOR);

    if (!me->query_temp("locker_change_pass")
        || me->query_temp("locker_change_pass") != arg)
    {
       write(HIY"你将把密码箱的密码改成"NOR HIG + arg +
             NOR HIY",\n如果没错的话请再输入一次。\n"NOR);
       me->set_temp("locker_change_pass", arg);
       return 1;
    }

    me->delete_temp("locker_change_pass");
    set("passwd", arg);
    write(HIG"你将密码箱的密码改成了" + arg + "。\n"NOR);
    save();

    return 1;
}

int do_lock(string arg)
{
    if (!query("open"))
    return notify_fail("密码箱已经是锁着的了。\n"NOR);

    delete("open");
    message_vision(HIW "只见$N" HIW "卡嚓一声把密码箱锁了起来。"
                   "\n"NOR, this_player());
    save();
    return 1;
}

int do_check()
{
    int i, cun_num;
    object ob, me = this_player();

    string msg, cun_itm, *deposit = query("deposit"),
           cun_name, cun_unit, cun_id;

    if (!query("open"))
    {
        write(HIR"密码箱现在关着，没法操作！\n"
              "请先用type <密码> 来打开箱子！\n"NOR);
        return 1;
     }

    if (me->is_busy())
    {
        write("等你忙完了再查东西吧！\n");
        return 1;
    }

    if (sizeof(deposit) == 0 )
    {
       tell_object(me, "你在密码箱里什么也没存！\n");
       return 1;
    }

    msg = "你在密码箱里存放的物品如下：\n";

    for (i = 0; i < sizeof(deposit); i++)
    {
        sscanf(deposit[i], "%s:%d:%s:%s:%s",
          cun_itm, cun_num, cun_unit, cun_name, cun_id);

        msg += HIY + (i+1) + "." + NOR + chinese_number(cun_num)
               + cun_unit + cun_name + "(" + cun_id + ")" + "\n";
    }

    me->start_more(msg);

    me->start_busy(2);

    write(HIW"操作完毕的话请用lock关闭密码箱！\n"NOR);
    return 1;

}

int cun_check(string arg)
{
        object me, *inv;
        int num, i, amount;
        string itm;

        me = this_player();


         if (!query("open"))
        {
           write(HIR"密码箱现在关着，没法操作！\n"
              "请先用type <密码> 来打开箱子！\n"NOR);
           return 1;
        }


        if (me->is_busy())
            return notify_fail("等你忙完了再存东西吧！\n");

        if ( arg == "all" )
        {
           inv = all_inventory(me);
           for (i=0;i<sizeof(inv);i++)
           {
              amount = 0;

              if ( inv[i]->query("base_unit"))
                 amount = inv[i]->query_amount();
              else
                 amount = 1;

               arg = amount + " " + inv[i]->query("id");
               do_cun(arg, 1);
            }

            tell_object(me, "你把身上所有能存的东西都存进了密码箱。\n");

            message("vision", HIC + me->name() + HIC "拿出一些物品存入了密码箱"
                                    "。\n" NOR, environment(me), ({me}));

            me->start_busy(2);
            save();
            write(HIW"操作完毕的话请用lock关闭密码箱！\n"NOR);
            return 1;
         }

        if (!arg || sscanf(arg, "%d %s", num, itm) != 2)
            return notify_fail("你要存什么物品？格式为cun <数量> <物品完整id>\n");

         do_cun(arg, 0);

         me->start_busy(2);
         save();
         write(HIW"操作完毕的话请用lock关闭密码箱！\n"NOR);

         return 1;

}

int do_cun(string arg, int all)
{
        object ob, me, *inv;
        int num, ttl_amt, i, cun_num, same;
        string itm, *deposit, cun_itm, bs_nm, unit,
               cun_name, cun_id, cun_unit;

        me = this_player();
        same = 0;

        sscanf(arg, "%d %s", num, itm);

        ob = present(itm, me);

        if (!ob)
        {  write("你身上没有这个物品呀！\n"); return 1;}


        if (ob->is_character())
        { if ( ! all ) write("活物你也想存？有没有搞错！\n"); return 1;}


        if (! ob->query("can_cun") && file_name(ob)[0..10] != "/clone/fam/"
             && file_name(ob)[0..13] != "/clone/tattoo/"
             && file_name(ob)[0..11] != "/clone/gift/"
             && file_name(ob)[0..15] != "/clone/medicine/"
             || ob->query("no_cun") )
          {  if (! all) write("对不起，这种物品不能存放！\n"); return 1;}


          if (num < 1)
          {write("一次最少存一件物品！\n");return 1;}

         bs_nm = base_name(ob);
         inv = all_inventory(me);


          if (stringp( unit = ob->query("base_unit")))
              ttl_amt = ob->query_amount();

          else
          {
              for (i = 0; i < sizeof(inv); i++)
              {
                 if (bs_nm == base_name(inv[i]))
                    ttl_amt += 1;
              }
              unit = ob->query("unit");
          }

         if (num > ttl_amt)
         {   write("你身上没这么多" +
                   ob->query("name") + NOR"！\n");
             return 1;
         }

        if ( ! all )
        {
           tell_object(me, "你拿出" + chinese_number(num) + unit +
                          ob->name() + "存进了储物箱。\n");


           message("vision", HIC + me->name() + HIC "拿出一些物品存入了储物箱"
                                    "。\n" NOR, environment(me), ({me}));
         }


         if (query("deposit"))
            deposit = query("deposit");
         else deposit = ({});

         for (i=0;i<sizeof(deposit);i++)
         {
            sscanf(deposit[i], "%s:%d:%s:%s:%s", cun_itm, cun_num,
                     cun_unit, cun_name, cun_id);
            if (cun_itm == bs_nm)
            {
               deposit[i] = cun_itm + ":" + (cun_num + num) + ":" +
                unit + ":" + ob->query("name") + ":" + ob->query("id");
               same = 1;
            }
         }

         if (same != 1) deposit += ({ bs_nm + ":" + num + ":" + unit
                        + ":" + ob->query("name") + ":" + ob->query("id")});

         set("deposit", deposit);

         if (ob->query("base_unit"))
         {
            ob->add_amount(-num);
            if (ob->query_amount() < 1) destruct(ob);

         } else
         {
            for (i = 0; i < num; i++)
            {
                ob = present(itm, me);
                destruct(ob);
            }
         }
   return 1;
}

int do_qu(string arg)
{

        object ob, me;
        int num, i, cun_num, itm, x;
        string *deposit, cun_itm, unit,
               cun_unit, cun_name, cun_id;

        me = this_player();


        if (!query("open"))
        {
            write(HIR"密码箱现在关着，没法操作！\n"
              "请先用type <密码> 来打开箱子！\n"NOR);
            return 1;
         }


        if (!arg || sscanf(arg, "%d %d", num, itm) != 2)
            return notify_fail("你要取什么物品？格式为qu <数量> <物品序列号>\n");

        if (me->is_busy())
            return notify_fail("等你忙完了再取东西吧！\n");

        deposit = query("deposit");

        if ( sizeof(deposit) == 0 )
            return notify_fail("你根本没存东西在箱子里，取什么取！\n");

        if (num < 1)
             return notify_fail("一次最少取一件物品！\n");


        if (num > 50)
             return notify_fail("一次最多取五十件物品！\n");

        if ( itm < 1 || itm > sizeof(deposit))
            return notify_fail("你没有存这个物品!\n"
                               "请注意格式为qu <数量> <物品序列号>！\n"
                               "查询你的物品序列号请输入check\n");

       sscanf(deposit[(itm - 1)], "%s:%d:%s:%s:%s",
              cun_itm, cun_num, cun_unit, cun_name, cun_id);

       ob = new(cun_itm);

        if (me->query_encumbrance() + ob->query_weight() * num
            > me->query_max_encumbrance())
        {
                tell_object(me, "你的负重不够，无法一次取出这么多物品。\n");
                destruct(ob);
                return 1;
        }


              if (cun_num < num)
              {
                  write("你没存这么多" + ob->query("name") + "！\n");
                  destruct(ob);
                  return 1;
              }



              if (ob->query("base_unit"))
              {
                 unit = ob->query("base_unit");
                 ob->set_amount(num);
                 ob->move(me, 1);
              }
              else
              {
                 unit = ob->query("unit");
                 destruct(ob);
                 for( x = 0; x < num; x++)
                 {
                    ob = new(cun_itm);
                    ob->move(me, 1);
                 }

              }

              tell_object(me, "你从密码箱里取出" + chinese_number(num) + unit +
                          ob->name() + "。\n");


              message("vision", HIC + me->name() + HIC "从密码箱里拿了些东西出来"
                                    "。\n" NOR, environment(me), ({me}));

              if (num == cun_num) deposit -= ({ cun_itm + ":" + cun_num +
                  ":" + cun_unit + ":" + cun_name + ":" + cun_id });
                 else
              deposit[(itm-1)] = cun_itm + ":" + (cun_num - num) + ":"
                   + cun_unit + ":" + cun_name + ":" + cun_id;

              set("deposit", deposit);

              me->start_busy(2);
              save();
              write(HIW"操作完毕的话请用lock关闭密码箱！\n"NOR);
              return 1;
}

int remove()
{
        save();
}

public void mud_shutdown()
{
        save();
}

string query_save_file()
{
        string id;

        if (! stringp(id = query("owner")) ) return 0;
        return DATA_DIR + "room/" + id + "/" + "locker";
}

*/
