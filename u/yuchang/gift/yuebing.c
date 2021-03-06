#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "金丹" NOR, ({ "jin dan", "jin", "dan" }) );
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW " 浪翻云练制的神奇金丹！\n" NOR);
                set("no_give", 1);
                set("no_drop", 1);
                set("no_sell", 1);
                set("unit", "颗");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        string mapsk;
        int effect;
        int neili;

        effect = 0;

        if(! objectp(present("jin dan", me)))return 0;

        if (me->query("eat_moon_gift/y2003"))
        {
              message_vision(HIY "$N" HIY "哈哈一笑，吞下金丹，但是没什么作用！\n" NOR, me);
              destruct(this_object());
              return 1;
        }

       	message_vision(HIY "$N" HIY "哈哈一笑，将金丹吞了。\n" NOR, me);

        me->set("eat_moon_gift/y2003", 1);
       	me->add("combat_exp", 50000);
       	me->add("potential", 10000);

       	mapsk = me->query_skill_mapped("force");

       	if (me->can_improve_skill("force"))
               	me->improve_skill("force", 1500000);
       	if (stringp(mapsk) && me->can_improve_skill(mapsk))
               	me->improve_skill(mapsk, 1500000);

       	mapsk = me->query_skill_mapped("dodge");

       	if (me->can_improve_skill("dodge"))
               	me->improve_skill("dodge", 1500000);
       	if (stringp(mapsk) && me->can_improve_skill(mapsk))
               	me->improve_skill(mapsk, 1500000);

       	mapsk = me->query_skill_mapped("parry");

       	if (me->can_improve_skill("parry"))
               	me->improve_skill("parry", 1500000);
       	if (stringp(mapsk) && me->can_improve_skill(mapsk))
               	me->improve_skill(mapsk, 1500000);

       	mapsk = me->query_skill_mapped("unarmed");

       	if (me->can_improve_skill("unarmed"))
               	me->improve_skill("unarmed", 1500000);
       	if (stringp(mapsk) && me->can_improve_skill(mapsk))
               	me->improve_skill(mapsk, 1500000);

       	if (me->can_improve_skill("martial-cognize"))
               	me->improve_skill("martial-cognize", 1500000);

        message_vision(HIC "$N" HIC "你获得了五万点经验和一万点潜能。\n" NOR, me);

        destruct(this_object());
        return 1;
}
