// medicine.c 太极本草

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIG "太极本草" NOR; }

int perform(object me, string skill)
{
        return notify_fail("这项技能可使你更快更有效的吸收各类药物，不需要运用。\n");
}

