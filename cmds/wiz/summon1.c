// summon. 取回兵器

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string str)
{
        object ob;
        int i;
        mapping cansm;
        string obj, replace, *objs;

        if (! str)
        {
                cansm = me->query("can_summon");
                if (! sizeof(cansm))
                {
                        write("你目前没有可以 SUMMON 的物品。\n");
                        return 1;
                } else
                {
                        write("你目前可以 SUMMON 的物品有：\n");
                        objs = sort_array(keys(cansm), 1);
                        for (i = 0; i < sizeof(objs); i++)
				write(sprintf(HIW "英文名字：%-15s          中文名字：%20s\n"NOR,objs[i],cansm[objs[i]]->name()));
                        return 1;
                }
        }

//      if (! str)
 //               return notify_fail("你要召唤什么物品？\n");

        if (! stringp(str = me->query("can_summon/" + str)))
                return notify_fail("你不知道如何召唤这个物品。\n");

        if (me->is_ghost())
                return notify_fail("等你还了阳再召唤吧。\n");

        call_other(str, "???");
        ob = find_object(str);
        if (! ob || ! ob->receive_summon(me))
        {
                message_vision(HIM "$N" HIM "扬起手来，口中念念有"
                               "词。\n然而什么也没有发生 :)\n", me);
        }

        return 1;
}

int help(object me)
{
write(@HELP
指令格式 : summon <物品的ID>

此指令可让你把某些物品呼唤过来并装备上，当然你得有一定的
精力施展仙术才行。
HELP
    );
    return 1;
}

