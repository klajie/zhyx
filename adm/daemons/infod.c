// eventd.c

#include <ansi.h>
#include <localtime.h>

inherit F_DBASE;

string* info = ({	
        "欢迎光临炎黄英雄史，游戏主页：http://yhhero.vicp.net 。",
        "请在ZMUD中的[常规]中关闭[回应指令行]设置。",
        "请在游戏前认真阅读帮助文件(help)，有问题可询问新手导师(who -v)。",        
        "请使用指令 show 查看您当前所在位置的地图，地图中红色闪烁部分为您所在具体位置。",
        "如要了解本游戏的特色，请使用 help feature 查看。",
        "本游戏提供三十余个门派接近千余种武学供玩家选择，武学介绍可参见 help skills 。",
        "本导航系统正在测试和完善当中，请有经验的玩家提供资料 ……",
});	

void create()
{
        string event;
        object eob;

        seteuid(ROOT_UID);
        set("channel_id", "导航精灵");
        CHANNEL_D->do_channel(this_object(), "sys", "导航系统已经启动。");
}

int get_info_size()
{
	return sizeof(info);
}

string get_info(int i)
{
	if (i < 0 || i >= sizeof(info))
	      return "数据溢出，请找在线巫师解决，或在bug留言室里留言。";

	return info[i];
}