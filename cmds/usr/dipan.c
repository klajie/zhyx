// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string *member;
        string bunch;
        string id;
        object area, npc;
        string msg;
        int n;
                
        if (me->is_busy()) return notify_fail("你正忙着呢！\n");
                
        if (! arrayp(member = BUNCH_D->query_area_fame()))
        {
                write("现在中华英雄没有任何地盘可被帮派利用。\n");
                return 1;
        }

        if (sizeof(member) < 1)
                return notify_fail("中华英雄现在没有任何地盘可被帮派利用。\n");

        msg = sprintf(HIC "\n%-16s%-12s%-20s%-8s%-8s%-14s%-18s%-8s\n" NOR,
                      "地盘名称", "所属帮派", "驻守ＮＰＣ", "资金度", "开发度",
                      "资产（黄金）", "上月收入（白银）", "忠诚度");
                      
        msg += HIY "———————————————————————————————————————————————————\n" NOR;
                
        n = 0;
        foreach (id in member)
        {
                area = get_object(id);
                if (! objectp(area))
                        continue;
                        
                bunch = area->query("bunch/bunch_name");
                
                // npc = get_object(area->query("bunch/npc_file"));
                
                n++;
                msg += sprintf(HIC "%-16s%-12s%-20s%-8s%-8s%-14s%-18s%-8s\n" NOR, 
                               area->short(), stringp(bunch) ? bunch : "独 立 中",
                               area->query("bunch/npc_name") + "(" + area->query("bunch/npc_id") + ")",
                               area->query("area/ziyuan") ? area->query("bunch/jizhi") + "%" : "----", 
                               area->query("area/ziyuan") ? area->query("bunch/kaifa") + "%" : "----", 
                               area->query("bunch/money") / 10000 + " 两", 
                               area->query("bunch/last_money") / 100 + " 两",
                               (stringp(bunch) && bunch == me->query("bunch/bunch_name")) ? 
                               area->query("bunch/zhongcheng") + "%" : "------"); 
        }

        if (n < 1)
                return notify_fail("现在中华英雄没有任何地盘可被帮派利用。\n");

        msg += "\n目前中华英雄共有" + HIM + chinese_number(n) + NOR + "处地盘。\n";
        msg += HIY "———————————————————————————————————————————————————\n" NOR;
        
        write(msg);
        me->start_busy(2);
        return 1;
}
        
int help(object me)
{
        write(@HELP
指令格式：dipan
用于显示中华英雄所有地盘的所属帮会资料。
HELP
        );
        return 1;
}



