// nick.c
// by jackyboy @ cctx 98/12/12
#include <ansi.h>

inherit F_CLEAN_UP;
//string replace_color(string,int);
//此函数被移动到/adm/simul_efun/message.c里作为sim_efun使用！
//如果第二个函数为0表示清除颜色控制！否则为将$HIW$等字符串替换为颜色控制代码
int help();
int wiz_set(string,string,string,int);

int main(object me, string arg)
{
	string dest;
	if(!arg) return help();
	if(sscanf(arg,"-title %s,%s",dest,arg)==2)
	{
		if(!wizardp(me))
			return notify_fail("这个功能只能由巫师使用。\n");
		if(wiz_level(me)<wiz_level("(arch)")&&(dest!="me"&&dest!=me->query("id")))
			return notify_fail("你的权限不够进行这个操作。\n");
		return wiz_set(dest,arg,"title",1)?1:notify_fail("命令失败。\n");
	}
	if(sscanf(arg,"-name %s,%s",dest,arg)==2)
	{
		if(!wizardp(me))
			return notify_fail("这个功能只能由巫师使用。\n");
		if(wiz_level(me)<wiz_level("(arch)")&&(dest!="me"&&dest!=me->query("id")))
			return notify_fail("你的权限不够进行这个操作。\n");
		return wiz_set(dest,arg,"name",0)?1:notify_fail("命令失败。\n");
	}
	if(sscanf(arg,"-id %s,%s",dest,arg)==2)
	{
		if(wiz_level(me)<wiz_level("(arch)"))
			return notify_fail("这个操作只能由护法或天神执行。\n");
		return wiz_set(dest,arg,"id",0)?1:notify_fail("命令失败。\n");
	}
	if(sscanf(arg,"-nick %*s")==1)
		sscanf(arg,"-nick %s",arg);
	if(sscanf(arg,"%s,%s",dest,arg)==2)
	{
		if(wiz_level(me)<wiz_level("(apprentice)"))
			return notify_fail("这个操作只能由小巫以上级别的巫师执行。\n");
		return wiz_set(dest,arg,"nickname",1)?1:notify_fail("命令失败。\n");
	}
             if (strlen(filter_color(arg)) > 500) 
              me->set("nickname", arg + NOR); 
              write("你取好了绰号。\n"); 
             return 1; 
                  }

int help()
{
	write(@HELP
指令格式 : 
nick <绰号> (适用于普通玩家)
nick -title <id>,<字串>	给id为<id>的玩家、NPC或OBJECT设定title属性 (适用于wiz)
nick -name  <id>,<字串>	给id为<id>的玩家、NPC或OBJECT设定name属性 (适用于wiz)
nick -id    <id>,<字串>	给id为<id>的玩家、NPC或OBJECT设定id属性 (适用于wiz)
nick <id>,<绰号>,	给id为<id>的玩家、NPC或OBJECT设定id属性 (适用于wiz)
其中hufa以下级别巫师只能设置自己的tilte和name。
任何一个命令都不能对更高级别的巫师进行修改。
如果你希望使用 ANSI 的控制字元改变颜色，可以用以下的控制字串：
$BLK$ - 黑色		$NOR$ - 恢复正常颜色
$RED$ - 红色		$HIR$ - 亮红色
$GRN$ - 绿色		$HIG$ - 亮绿色
$YEL$ - 土黄色		$HIY$ - 黄色
$BLU$ - 深蓝色		$HIB$ - 蓝色
$MAG$ - 浅紫色		$HIM$ - 粉红色
$CYN$ - 蓝绿色		$HIC$ - 天青色
$WHT$ - 浅灰色		$HIW$ - 白色
$BLINK$ - 字符闪烁
其中系统自动会在字串尾端加一个 $NOR$。
字串或绰号为cancel时将取消该项属性，玩家只能取消<绰号>。
By JackyBoy @ CCTX 98/12/12
HELP
	);
	return 1;
}
