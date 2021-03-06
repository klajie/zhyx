// write by yeer
// update by Lonely 2005.1
// modified by weed 2006.5
// xiang.c

#include <ansi.h>

inherit ITEM;
inherit F_SAVE;

#define TO_STORE(x, y) (["name" : ob->query("name"), "id" : ob->query("id"), "file" : base_name(ob), "amount" : x, "sign" : y])

nosave int load;
mapping *store;
mapping *data_dbase;
mapping *temp_dbase;

int do_store(string arg);
int do_take(string arg);
int do_lock(string arg);
int do_open(string arg);
int do_view(string arg);
int get_passwd(string pass, object ob);
int confirm(string yn, object me);
int set_passwd(string pass, object ob);
int store_item(object me, object obj, int amount);
int store_data(object me, object ob, int sn);
int compare_mapping(mapping m1, mapping m2);
int compare_array(mixed *a1, mixed *a2);

void create()
{
        set_name(HIY "失物招领箱" NOR, ({ "xiang" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", HIW "仅供失物招领,不能储放物品。\n"
                                "格式view box, take 数量 编号。" NOR);

                set("value", 100);
                set("unit", "个");
                set("no_get", 1);
        }
        setup();
}



void init()
{

        add_action("do_view", "view");
        add_action("do_take", "take");

}

int do_view(string arg)
{
        object me;
        mixed ob_name_real_len;
        string msg, ob_name;

        me = this_player();

        set("owner", me->query("id"));
        restore();

        if (! id(arg))
                return notify_fail("你要查看什么？\n");

        if (! store || sizeof(store) < 1)
                return  notify_fail("你目前没有存放任何物品在柜子里。\n");

        msg = HIW "\n目前你存放的物品有：\n编号  物品                                      数量\n"
                  "──────────────────────────\n" NOR;

        for (int i = 0; i < sizeof(store); i++)
        {
                ob_name = filter_color(store[i]["name"] + "(" + store[i]["id"] + ")");
                ob_name_real_len = color_len(store[i]["name"] + "(" + store[i]["id"] + ")");
                msg += sprintf("[%2d]  %-" + (36 + ob_name_real_len) + "s     %5d\n",
                               i + 1, store[i]["name"] + "(" + store[i]["id"] + ")",
                               store[i]["amount"]);
                if (store[i]["amount"] == 0)
                        store[i] = 0;
        }
        msg += HIW "──────────────────────────\n" NOR;
        this_player()->start_more(msg);
        store -= ({ 0 });
        return 1;
}

int do_take(string arg)
{
        object me, ob;
        int i, j, sn, amount, amount1;
        mapping data;
        string *ks;

        me = this_player();

        set("owner", me->query("id"));
        restore();


        if (! arg || sscanf(arg, "%d %d", amount, sn) != 2)
                return notify_fail("格式错误，请用 take 数量 编号 来取回物品。\n");

        if (amount < 1 || amount > 2000)
                return notify_fail("每次取物品的数量不得小于一同时也不能大于两千。\n");

        if (sn < 1) return notify_fail("你要取第几号物品？\n");

        if (! store || sizeof(store) < 1 || sn > sizeof(store))
                return notify_fail("你的柜子里没有存放这项物品。\n");

        if (amount > store[sn-1]["amount"])
                return notify_fail("这项物品你没有那么多存货。\n");

        ob = new(store[sn-1]["file"]);
        if (me->query_encumbrance() + ob->query_weight() * amount > me->query_max_encumbrance())
        {
                tell_object(me, "你的负重不够，无法一次取出这么多物品。\n");
                destruct(ob);
                return 1;
        }

        store[sn-1]["amount"] -= amount;

        if (ob->query_amount())
        {
                if (store[sn-1]["amount"] == 0)
                {
                        store[sn-1] = 0;
                        store -= ({ 0 });
                }
                ob->set_amount(amount);
                ob->move(me);
                save();

                message_vision("$N从柜子里取出一" +
                                ob->query("unit") + ob->query("name") + "。\n", me);
                return 1;
        }

        destruct(ob);

        amount1 = amount;

        while (amount1--)
        {
                ob = new(store[sn-1]["file"]);
                if (data_dbase && sizeof(data_dbase) > 0)
                {
                        for (i = 0; i < sizeof(data_dbase); i++)
                        {
                                if (data_dbase[i]["sign"] == store[sn-1]["sign"])
                                {
                                        data = data_dbase[i];
                                        ks = keys(data);
                                        for (j = 0; j < sizeof(ks); j++)
                                        {
                                                if (ks[j] == "sign") continue;
                                                ob->set(ks[j], data[ks[j]]);
                                        }
                                        data_dbase[i] = 0;
                                }
                        }
                        data_dbase -= ({ 0 });
                }
                if (temp_dbase && sizeof(temp_dbase) > 0)
                {
                        for (i = 0; i < sizeof(temp_dbase); i++)
                        {
                                if (temp_dbase[i]["sign"] == store[sn-1]["sign"])
                                {
                                        data = temp_dbase[i];
                                        ks = keys(data);
                                        for (j = 0; j < sizeof(ks); j++)
                                        {
                                                if (ks[j] == "sign") continue;
                                                ob->set_temp(ks[j], data[ks[j]]);
                                        }
                                        temp_dbase[i] = 0;
                                }
                        }
                        temp_dbase -= ({ 0 });
                }

                if(ob->short() != store[sn-1]["name"] + "(" + store[sn-1]["id"] + ")")
                {
                        amount1++;
                        destruct(ob);
                        continue;
                }
                ob->move(me);
        }

        message_vision("$N从柜子里取出" + chinese_number(amount) +
                        ob->query("unit") + ob->query("name") + "。\n", me);

        if (store[sn-1]["amount"] == 0)
        {
                store[sn-1] = 0;
                store -= ({ 0 });
        }
        save();
        return 1;
}





int store_data(object me, object ob, int sn)
{
        mapping data;

        if (! data_dbase)
                data_dbase = ({});
        data = ob->query_entire_dbase();
        data += ([ "sign" : sn ]);
        data_dbase += ({data});

        if (! temp_dbase)
                temp_dbase = ({});

        data = ob->query_entire_temp_dbase();

        if (! data) return 1;

        data += ([ "sign" : sn ]);
        temp_dbase += ({data});

        return 1;
}

int compare_mapping(mapping m1, mapping m2)
{
        string index, m_type;

        if (! m1 && ! m2 )
                return 1;

        if (sizeof(m1) != sizeof(m2))
                return 0;

        foreach (index in keys(m1))
        {
                m_type = typeof(m1[index]);
                if (m_type != typeof(m2[index]))
                        return 0;
                if (m_type == "mapping" && ! compare_mapping(m1[index], m2[index]))
                        return 0;
                if (m_type == "array" && ! compare_array(m1[index], m2[index]))
                        return 0;
                if (m1[index] != m2[index])
                        return 0;
        }
        return 1;
}

int compare_array(mixed *a1, mixed *a2)
{
        int a_size;
        string a_type;

        if (! a1 && ! a2)
                return 1;

        a_size = sizeof(a1);
        if (a_size != sizeof(a2))
                return 0;

        for (int i = 0; i < a_size; i++)
        {
                a_type = typeof(a1[i]);
                if (a_type != typeof(a2[i]))
                        return 0;
                if (a_type == "mapping" && !compare_mapping(a1[i], a2[i]))
                        return 0;
                if (a_type == "array" && !compare_array(a1[i], a2[1]))
                        return 0;
                if (a1[i] != a2[i])
                        return 0;
        }
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
      return DATA_DIR + "room/" + id + "/" + "storage";
}
