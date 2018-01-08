#include <weapon.h> 
#include <ansi.h>
inherit SWORD; 

void create()
{
        set_name(HIR"绝世好剑"NOR, ({ "jueshi haojian", "jueshi", "sword", "jian" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("long", HIR"这是一柄四尺来长的宝剑，全身通红。此剑出自"
                           "傲剑山庄，\n经山庄三代铸剑师历时百年铸成，堪称剑中之王。\n"NOR);
                set("wield_msg", HIW"刹那间一道气壮山河的黑虹"
                             "宛似天际间忽起的闪电出现在众人眼前！\n"NOR);
                set("unwield_msg", HIW"但见$N" HIW"将$n" HIW"向天一指，"
                                 "数匹布条随风而起，将$n" HIW"严严实实地裹了起来！\n"NOR);
                set("unit", "柄");
                set("value", 10000);
                set("material", "steel"); 
                set("no_sell", 1);      
               
        }
        init_sword(140);
        setup();
}

int query_autoload()
{
       return 1;
}
