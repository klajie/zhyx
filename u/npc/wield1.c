// wield.c

inherit F_CLEAN_UP;

int do_wield(object me, object ob);

int main(object me, string arg)
{
        object ob, *inv;
        int i, count;

        if( !arg ) return notify_fail("你要装备什么武器？\n");

        if(arg=="all") {
                inv = all_inventory(me);
                for(count=0, i=0; i<sizeof(inv); i++) {
                        if( inv[i]->query("equipped") ) continue;
                        if(do_wield(me, inv[i]) ) count ++;
                }
                write("Ok.\n");
                return 1;
        }

        if( !objectp(ob = present(arg, me)) )
                return notify_fail("你身上没有这样东西。\n");

        if( ob->query("equipped") )
                return notify_fail("你已经装备着了。\n");

        return do_wield(me, ob);
}

int do_wield(object me, object ob)
{
        string str;

    if( ob->query("owner_id") && ob->query("owner_id") != getuid(me) )   {
                destruct(ob);
                return notify_fail("下次别乱偷别人的东西。\n");
        }
        
        if( me->query_temp("No_Wield") )
                return notify_fail("你原形已现，不可再持兵器！\n");
  //add by wsw 20051010
  //加入装备绑定限制条件
  if (ob->query("changed") && (!ob->query("primitive_id") ||!ob->query("unique_code") ) && !wizardp(me)) 
  	return notify_fail("这件装备来历不明，不能使用！\n");
  if (ob->query("bind_id") && ob->query("bind_id") != getuid(me) ) 
  	return notify_fail("这不是你的兵器！\n");
  
                
  //加入装备条件限制 wsw于2003年11月
    if(ob->query("durability/max")>0 && ob->query("durability/now")<=0)
        return notify_fail("这件武器暂时不能用了。\n");
if (!wizardp(me)) {
    if( ob->query("weapon_wiel/exp")*1000> me->query("combat_exp") )  return notify_fail("你的经验不够，请用ll命令查看装备要求。\n");
    if( ob->query("weapon_wiel/str")> me->query("str") )  return notify_fail("你的天赋不够，请用ll命令查看装备要求。\n");
    if( ob->query("weapon_wiel/con")> me->query("con") )  return notify_fail("你的天赋不够，请用ll命令查看装备要求。\n");
    if( ob->query("weapon_wiel/int")> me->query("int") )  return notify_fail("你的天赋不够，请用ll命令查看装备要求。\n");
    if( ob->query("weapon_wiel/dex")> me->query("dex") )  return notify_fail("你的天赋不够，请用ll命令查看装备要求。\n");
    if( ob->query("weapon_wiel/kar")> me->query("kar") )  return notify_fail("你的天赋不够，请用ll命令查看装备要求。\n");
    if( ob->query("weapon_wiel/max_kee")> me->query("max_qi") )  return notify_fail("你的最大气血不够，请用ll命令查看装备要求。\n");
    if( ob->query("weapon_wiel/max_sen")> me->query("max_jing") )  return notify_fail("你的精神不够，请用ll命令查看装备要求。\n");
    if( ob->query("weapon_wiel/skill")> me->query_skill(ob->query("skill_type"),1) )  return notify_fail("你的技能不够。\n");
}               

        if( ob->wield() ) {
        	if (ob->query("bind_type") >=1 && !ob->query("bind_id"))  ob->set("bind_id",getuid(me));//add by wsw 20051011
                if( !stringp(str = ob->query("wield_msg")) )
                        str = "$N装备$n作武器。\n";
                message_vision(str, me, ob);
                return 1;
        } else
                return 0;
}

int help(object me)
{
        write(@HELP
指令格式：wield|zhuangbei <装备名称>
 
这个指令让你装备某件物品作武器, 你必需要拥有这样物品.
 
HELP
    );
    return 1;
}

