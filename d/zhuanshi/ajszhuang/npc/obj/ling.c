// tu.c BY YUCHANG

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIB"令牌"NOR, ({"ling pai", "lingpai"}) );
        set_weight(10);
        set("no_steal", 1);
        set("no_beg", 1);
        set("no_sell", 1);
        set("value",1);
        set("long",@LONG
令牌上刻着”不哭死神“四个大字，看来是天下会步惊云所有！
还不快去物归原主?
LONG );
        if( clonep() )
               set_default_object(__FILE__);
        else
       {
                set("unit", "块");
                set("material", "unknow");
        }
}

int query_autoload() { return 1; }

