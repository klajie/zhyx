// mjade.c ��֮���

#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
	set_name(HIG "��֮���" NOR, ({ "magic jade" }) );
	set_weight(50);
	if( clonep() )
		set_default_object(__FILE__);
	else {
                set("long", HIG "һ�Ż���������Ĺ�ʵ���䣬"
                    "�����Բ�ͬѰ���ĸо���\n" NOR);
                set("value", 200000);
		set("unit", "��");
                set("can_be_enchased", 1);
                set("magic/type", "cold");
                set("magic/power", 150);
                set("armor_prop/personality", 8);
                set("wear_msg", HIC "$N" HIC "����ذ�$n"
                    HIC "����ͷ�ϡ�\n" NOR);
                set("remove_msg", HIC "$N" HIC "����ذ�$n"
                    HIC "��ͷ��ժ��������\n" NOR);
	}
        setup();
}

int query_autoload() { return 1; }