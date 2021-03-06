//newitems.c
//wsw 2002 12
//2004 3月修改
//随机出装备文件。
//添加名称、花样以及属性  huarong 2004/10
// newweapon.h

#include <ansi.h>
inherit __DIR__"newitemname.c";
object get_weapon(object me,object killer);
object get_armor(object me,object killer);
object get_baoshi(object me,object killer);
mapping tianfu1=([
                "str":"体格",
                "int":"悟性",
                "per":"容貌",
                "kar":"福缘",
                ]);

mapping tianfu2=([
                "con":"根骨",
                "cps":"定力",
                "spi":"灵性",
                "cor":"胆识",
                ]);

//added by huarong 2004/11
void setname_weapon(object weapon)
{
     int k,mark;
     string type;
     string temp_name, *temp_id, long;

     type=weapon->query("skill_type");
     k=weapon->query("grade");
     if (type=="mace") return 0;
     if (random(100)>90) return 0;
	switch(type)
	{
	  case "sword" :     
                if(random(2))
                {
		temp_name=name_sword1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_sword2[k][0];
		mark=2;
	        }
		temp_name+=random(2)?"剑":"牙";	
		if(mark==1)
		temp_id=({name_sword1[k][1]+" sword","sword"});
	        else
		temp_id=({name_sword2[k][1]+" sword","sword"});
		break;
	  case "blade" :     
                if(random(2))
                {
		temp_name=name_blade1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_blade2[k][0];
		mark=2;
	        }
                if(k>5) temp_name+=random(2)?"神":"妖";
		temp_name+=random(2)?"刀":"斩";	
		if(mark==1)
		temp_id=({name_blade1[k][1]+" blade","blade"});
	        else
		temp_id=({name_blade2[k][1]+" blade","blade"});
		break;
	  case "fork" :     
                if(random(2))
                {
		temp_name=name_fork1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_fork2[k][0];
		mark=2;
	        }
                if(k>5) temp_name+=random(2)?"飞":"灵";
		temp_name+="叉";	
		if(mark==1)
		temp_id=({name_fork1[k][1]+" fork","fork"});
	        else
		temp_id=({name_fork2[k][1]+" fork","fork"});
		break;
	  case "stick" :     
                if(random(2))
                {
		temp_name=name_stick1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_stick2[k][0];
		mark=2;
	        }
		temp_name+=random(2)?"棍":"棒";	
		if(mark==1)
		temp_id=({name_stick1[k][1]+" stick","stick"});
	        else
		temp_id=({name_stick2[k][1]+" stick","stick"});
		break;
	  case "whip" :
	       if(random(2))
	       {    
                if(random(2))
                {
		temp_name=name_whip1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_whip2[k][0];
		mark=2;
	        }
		temp_name+=random(2)?"鞭":"索";	
		if(mark==1)
		temp_id=({name_whip1[k][1]+" whip","whip"});
	        else
		temp_id=({name_whip2[k][1]+" whip","whip"});
	       }
	       else
	       {
                if(random(2))
                {
		temp_name=name_whip3[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_whip4[k][0];
		mark=2;
	        }
		if(k<6) temp_name+=random(2)?"绸":"丝";
		else
		  {
                         temp_name+=random(2)?"仙":"青";
			 temp_name+="绫";	
	          }
		if(mark==1)
		temp_id=({name_whip3[k][1]+" whip","whip"});
	        else
		temp_id=({name_whip4[k][1]+" whip","whip"});
	       }
		break;
	  case "hammer" :     
                if(random(2))
                {
		temp_name=name_hammer1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_hammer2[k][0];
		mark=2;
	        }
                if(k>5) temp_name+=random(2)?"神":"雷";
		temp_name+="锤";	
		if(mark==1)
		temp_id=({name_hammer1[k][1]+" hammer","hammer"});
	        else
		temp_id=({name_hammer2[k][1]+" hammer","hammer"});
		break;		
	  case "spear" :     
                if(random(2))
                {
		temp_name=name_spear1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_spear2[k][0];
		mark=2;
	        }
		temp_name+=random(2)?"枪":"戟";	
		if(mark==1)
		temp_id=({name_spear1[k][1]+" spear","spear"});
	        else
		temp_id=({name_spear2[k][1]+" spear","spear"});
		break;				
	  case "staff" :     
                if(random(2))
                {
		temp_name=name_staff1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_staff2[k][0];
		mark=2;
	        }
                if(k>5) temp_name+=random(2)?"禅":"佛";
		temp_name+="杖";	
		if(mark==1)
		temp_id=({name_staff1[k][1]+" staff","staff"});
	        else
		temp_id=({name_staff2[k][1]+" staff","staff"});
		break;				
	  case "axe" :     
                if(random(2))
                {
		temp_name=name_axe1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_axe2[k][0];
		mark=2;
	        }
                if(k>5) temp_name+=random(2)?"之":"玄";
		temp_name+="斧";	
		if(mark==1)
                temp_id=({name_axe1[k][1]+" axe","axe"});
	        else
                temp_id=({name_axe2[k][1]+" axe","axe"});
		break;						
	   default :
	  	break;
	}	
     temp_name=temp_name+""NOR;
     if(temp_name) weapon->set_name(temp_name, temp_id);	
}			

//added by huarong 2004/11
void setname_armor(object armor)
{
     int k,mark;
     string type;
     string temp_name, *temp_id, long;

     type=armor->query("armor_type");
     k=armor->query("grade");
     if (type=="shield") return 0;
	switch(type)
	{
	  case "armor" :     
                if(random(2))
                {
		temp_name=name_armor1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_armor2[k][0];
		mark=2;
	        }
                if(k>10) temp_name+=random(2)?"宝":"异";
		temp_name+=random(2)?"甲":"铠";	
		if(mark==1)
		temp_id=({name_armor1[k][1]+" armor","armor"});
	        else
		temp_id=({name_armor2[k][1]+" armor","armor"});
		break;
	  case "cloth" :
	       if(random(2))
	       {
                if(random(2))
                {
		temp_name=name_cloth11[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_cloth12[k][0];
		mark=2;
	        }
                if(k>10) temp_name+=random(2)?"奇":"神";
		temp_name+=random(2)?"衫":"衣";	
		if(mark==1)
		temp_id=({name_cloth11[k][1]+" cloth","cloth"});
	        else
		temp_id=({name_cloth12[k][1]+" cloth","cloth"});
		armor->set("male_only", 1);
	       }
	       else
	       {
                if(random(2))
                {
		temp_name=name_cloth21[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_cloth22[k][0];
		mark=2;
	        }
                if(k>10) temp_name+=random(2)?"霓裳":"霞帔";
		else temp_name+=random(2)?"裳":"裙";	
		if(mark==1)
		temp_id=({name_cloth21[k][1]+" cloth","cloth"});
	        else
		temp_id=({name_cloth22[k][1]+" cloth","cloth"});
		armor->set("female_only", 1);
	       }
		break;
	  case "head" :
	       if(random(2))
	       {
                if(random(2))
                {
		temp_name=name_head11[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_head12[k][0];
		mark=2;
	        }
                if(k>10) temp_name+=random(2)?"之":"神";
		temp_name+=random(2)?"盔":"冠";	
		if(mark==1)
		temp_id=({name_head11[k][1]+" hat","hat"});
	        else
		temp_id=({name_head12[k][1]+" hat","hat"});
		armor->set("male_only", 1);
	       }
	       else
	       {
                if(random(2))
                {
		temp_name=name_head21[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_head22[k][0];
		mark=2;
	        }
                if(k>10) temp_name+=random(2)?"魔":"神";
		temp_name+=random(2)?"巾":"钗";	
		if(mark==1)
		temp_id=({name_head21[k][1]+" hat","hat"});
	        else
		temp_id=({name_head22[k][1]+" hat","hat"});
		armor->set("female_only", 1);
	       }
		break;
	  case "boots" :     
                if(random(2))
                {
		temp_name=name_boots1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_boots2[k][0];
		mark=2;
	        }
                if(k>10) temp_name+=random(2)?"神":"魔";
		temp_name+=random(2)?"靴":"鞋";	
		if(mark==1)
		  if(random(2)) temp_id=({name_boots1[k][1]+" boots","boots"});
		  else temp_id=({name_boots1[k][1]+" shoes","shoes"});
	        else
		  if(random(2)) temp_id=({name_boots2[k][1]+" boots","boots"});
		  else temp_id=({name_boots2[k][1]+" shoes","shoes"});
		break;
	  case "neck" :     
                if(random(2))
                {
		temp_name=name_neck1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_neck2[k][0];
		mark=2;
	        }
		temp_name+=random(2)?"护身符":"项链";	
		if(mark==1)
		temp_id=({name_neck1[k][1]+" neck","neck"});
	        else
		temp_id=({name_neck2[k][1]+" neck","neck"});
		break;
	  case "wrists" :     
                if(random(2))
                {
		temp_name=name_wrists1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_wrists2[k][0];
		mark=2;
	        }
                if(k>10) temp_name+=random(2)?"神":"幻";
		if(mark==1)
		{
		temp_id=({name_wrists1[k][1]+" wrists","wrists"});
		temp_name+="护腕";	
	        }
	        else
	        {
		temp_id=({name_wrists2[k][1]+" wrists","wrists"});
		temp_name+="镯";	
		}
		break;
	  case "finger" :     
		temp_name=name_ring[k][0];
                if(k>0 && k<=10) temp_name+="之戒";
                else temp_name+="戒";
		temp_id=({name_ring[k][1]+" ring","ring"});
		break;
	  case "waist" :     
		temp_name=name_waist[k][0];
                if(k>0 && k<=10) temp_name+="腰带";
		if(random(2)) temp_id=({name_waist[k][1]+" belt","belt"});
		else temp_id=({name_waist[k][1]+" waist","waist"});
		break;
	  case "surcoat" :     
                if(random(2))
                {
		temp_name=name_surcoat1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_surcoat2[k][0];
		mark=2;
	        }
                if(k>0 && k<=10) temp_name+=random(2)?"披风":"斗篷";
		if(mark==1)
		temp_id=({name_surcoat1[k][1]+" cloak","cloak"});
	        else
		temp_id=({name_surcoat2[k][1]+" cloak","cloak"});
		break;
	  case "hands" :     
                if(random(2))
                {
		temp_name=name_hands1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_hands2[k][0];
		mark=2;
	        }
                if(k>0 && k<=10) temp_name+=random(2)?"手套":"护手";
		if(mark==1)
		temp_id=({name_hands1[k][1]+" gloves","gloves"});
	        else
		temp_id=({name_hands2[k][1]+" gloves","gloves"});
		break;
	  default :
	  	break;
	}	
     temp_name=temp_name+""NOR;
     if(temp_name) armor->set_name(temp_name, temp_id);	
}


object get_item(object me,object killer)
{
	//object item;
      int i,j;
      j=killer->query_temp("mieyao/level")-6;
      if(j<0) j=0;
      if (wizardp(killer)) i=2;
      else i=13-j; 
      		
      switch(random(i))
      	{
		case 0: 
			return get_weapon(me,killer);break;
		case 1:
		        return get_armor(me,killer);break;
                case 2: 
                case 3:
//                case 4:                    
//                        return get_baoshi(me,killer);break;
                default: return 0;
	}
}


object get_weapon(object me,object killer)
{
	object weapon;
	int i,j,value,bind_pro,bind_type;
        int myexp,taexp,exp,max_level;
	string att;
	string *file=({
		"/d/obj/newitem/newweapon/sword.c",
		"/d/obj/newitem/newweapon/blade.c",
		"/d/obj/newitem/newweapon/fork.c",
		"/d/obj/newitem/newweapon/stick.c",
		"/d/obj/newitem/newweapon/whip.c",
		"/d/obj/newitem/newweapon/hammer.c",
		"/d/obj/newitem/newweapon/spear.c",
		"/d/obj/newitem/newweapon/staff.c",
		"/d/obj/newitem/newweapon/axe.c",
		"/d/obj/newitem/newweapon/mace.c"});
	mixed *name=({
		({YEL"青铜","bronz",50,3500,2000,50,3,0,3,200,100,20,500,500,1}),
		({HIC"精钢","steel",75,2500,5000,60,4,0,3,500,120,21,600,600,2}),
		({HIB"寒铁","iron",100,3000,15000,75,5,1,3,1000,150,22,800,800,3}),
		({HIY"乌金","gold",150,4000,25000,95,6,1,4,4000,200,23,1000,1000,4}),
		({HIG"灵玉","jade",200,2000,50000,120,7,2,4,10000,280,24,1500,1500,5}),
		({HIR+BLK"仙灵","xianling",250,2000,100000,140,8,2,5,25000,350,24,2000,2000,6}),
		({HIW"唐王","datang",250,2000,200000,160,9,3,5,40000,450,24,2500,2500,7})
		});                   
                //0名称 1id 2最大耐久度 3重量 4value 5damage 6魔法最高等级 7luck 8最大孔数 9exp 10skill 11 12max_kee 13 max_sen
	
	myexp=me->query("combat_exp",1);
	taexp=killer->query("combat_exp",1);
      if (myexp<taexp/1.5 && random(myexp+taexp) < taexp && !wizardp(killer) )
          return 0;   
//得到绿色装备
		i=random(10);
		weapon=new(file[i]);
		
		//得到武器的材料,对目标道行取随机值
		exp=random(myexp)/1000;
		if (exp>40000)  i=random(random(8));//四万年以上才能得暗黑装备
		else if (exp>25000) i=random(random(7));
		else if (exp>10000) i=i=random(random(6));
		else if (exp>4000) i=random(random(5));
		else if (exp>1000) i=random(random(4));
		else if (exp>500) i=random(random(3));
		else  i=0;
		
		
		
		//设置属性
		//add by wsw 20051010
		weapon->set("primitive_id",killer->query("id")); //爆出此装备的玩家ID
		weapon->set("unique_code",time()); //以时间定义装备唯一识别码
		//计算绑定形式
		bind_pro = 10; //绑定机率,10%绑定
		bind_pro += to_int(atan(taexp/1000000)*180/3.1415926);
		//weapon->set("bind_pro",bind_pro);//测试用
 
		bind_pro = random(bind_pro);
		if (bind_pro>70) bind_type = 3;
		else if (bind_pro>40) bind_type = 2;
		else if (bind_pro>10) bind_type = 1;
		else bind_type = 0;
		
		weapon->set("bind_type",bind_type); //0不绑定，1装备绑定，2拾取绑定,3，直接绑定。需修改wield.c，get.c，对应set("bind_id")
	        if (bind_type == 3) weapon->set("bind_id",killer->query("id")); //绑定id，在wield或get里设置
	        //add end
		weapon->set("changed",1);//有此属性，系统自动保存此装备
		weapon->set("unbreak",1);//有此属性，兵器不能被打断，同时应该修改weapond.c及可打断兵器的pfm和cast 
					//龙宫huntian-hammer,perform break,cast dragonfire,方寸的perform leiting
		weapon->set_name(name[i][0]+weapon->query("name")+NOR,({name[i][1]+" "+weapon->query("id"),weapon->query("id")}));
		weapon->set("durability/max",name[i][2]+random(name[i][2]));//最大耐久度,大于等于400时为永不磨损
		weapon->set("durability/now",random(name[i][2]));//当前耐久度
		weapon->set_weight((name[i][3]+weapon->query_weight())/2);
		switch(i)
		{
			case 0: att="是由青铜制成的。\n";break;
			case 1: att="是由百炼精铸成的。\n";break;
			case 2: att="是由千年寒铁铸成的。\n";break;
			case 3: att="是由万年乌金铸成的。\n";break;
			case 4: att="是由上古灵玉铸成的。\n";break;
			case 5: att="是由传说中的月亮之石化成的。\n";break;
                        case 6: att="是由传说中的大唐西游太阳之石化成的。\n";break;
		}
        	weapon->set("long",HIG+weapon->query("long")+att+NOR);
        	weapon->set("material", name[i][1]);
        	weapon->set("grade", name[i][14]);//等级 1－7
        	        	
        	//附加属性
        	weapon->set("weapon_prop/damage",name[i][5]+name[i][5]*random(20)/100);//攻击力
        	weapon->set("weapon_prop/luck",random(name[i][7]+1));//幸运值，出连招的次数
        	weapon->set("sockets/max",random(name[i][8]));//安放宝石数
        	weapon->set("sockets/now",0);
        	j=random(5);
        	switch(j)
        	{
        		case  0: att="cold_attack";break;
        		case  1:att="fire_attack";break;
        		case  2:att="lightning_attack";break;
        		case  3:att="poison_attack";break;
        		case  4:att="wind_attack";break;
        		default:att="";
		}
		if (att!="") //魔法攻击
		{			
			max_level=name[i][6]-random(3);//最高等级
			if (max_level<1) max_level=1;
			weapon->set((att+"/max_level"),max_level);
			weapon->set("weapon_prop"+"/"+att,1);//当前等级
			weapon->set((att+"/exp"),0);//经验值
		}
		
		//价值
        	value=name[i][4];
        	value+=weapon->query("durability/max")*50;
        	value+=weapon->query("durability/now")*25;
        	value+=weapon->query("weapon_prop/luck")*20000;
        	value+=weapon->query("sockets/max")*2500;
        	value+=weapon->query("cold/max_level")*2500;
        	value+=weapon->query("fire/max_level")*2500;
        	value+=weapon->query("lightning/max_level")*2500;
        	value+=weapon->query("poison/max_level")*2500;
        	value+=weapon->query("wind/max_level")*2500;
        	weapon->set("value", value*(i+1));
		
		//装备要求
		weapon->set("weapon_wiel/exp",name[i][9]);
		weapon->set("weapon_wiel/skill",name[i][10]);
                if(random(2))
                weapon->set("weapon_wiel/"+keys(tianfu1)[random(sizeof(tianfu1))],10+random(21));
                else 
                weapon->set("weapon_wiel/"+keys(tianfu2)[random(sizeof(tianfu2))],10+random(16));

		weapon->set("weapon_wiel/max_kee",name[i][12]);
		weapon->set("weapon_wiel/max_sen",name[i][13]);
		setname_weapon(weapon);
     if (wizardp(this_player()))
     tell_object(this_player(),HIM+"类型："+weapon->query("skill_type")+"     初始等级："+weapon->query("grade")+"\n"NOR);
		return weapon;
}


object get_armor(object me,object killer)
{
	object armor;
	int i,j,value,a1,a2,a3,bind_pro,bind_type;
	int myexp,taexp,exp;
	string att;
	string *file=({
		"/d/obj/newitem/newarmor/armor.c",
		"/d/obj/newitem/newarmor/boots.c",
		"/d/obj/newitem/newarmor/cloth.c",
		"/d/obj/newitem/newarmor/finger.c",
		"/d/obj/newitem/newarmor/hands.c",
		"/d/obj/newitem/newarmor/head.c",
		"/d/obj/newitem/newarmor/neck.c",
		"/d/obj/newitem/newarmor/shield.c",
		"/d/obj/newitem/newarmor/surcoat.c",
		"/d/obj/newitem/newarmor/waist.c",
		"/d/obj/newitem/newarmor/wrists.c"});
	mixed *name=({
		({HIY"蟒皮","boa","40/70",3000,2000,"15/25","15/5/10","5/0/2","5/0/2","5/0/2","5/0/2","",1,50,1}),
		({HIR+BLK"黑金","gold","20/50",2500,5000,"15/30","15/5/15","40/5/15","40/5/15","40/5/15","40/5/15","10/5",1,100,2}),
		({CYN"鳄鱼","crocodile","50/100",3000,10000,"15/35","15/8/15","5/0/2","5/0/2","5/0/2","5/0/2","",2,200,3}),
		({HIM"彩玉","jade","30/60",2500,20000,"20/40","15/8/20","40/10/15","40/8/15","40/8/15","40/8/15","10/6",2,500,4}),
		({HIG"猛犸","mammoth","60/110",4000,30000,"20/45","15/10/20","5/0/3","5/0/3","5/0/3","5/0/3","",2,1000,5}),
		({YEL"琥珀","amber","40/80",2000,40000,"25/50","15/10/25","40/8/20","40/8/20","40/8/20","40/8/20","10/7",2,2000,6}),
		({MAG"麒麟","kylin","80/120",2500,60000,"25/55","15/10/25","5/0/3","5/0/3","5/0/3","5/0/3","",3,4000,7}),
		({HIM"翡翠","emerald","50/80",2000,80000,"30/60","15/10/30","40/8/16","40/8/16","40/8/16","40/8/16","10/8",3,6000,8}),
		({HIC"龙鳞","dragon","100/150",2500,100000,"30/65","15/10/30","5/1/3","5/1/3","5/1/3","5/1/3","",3,10000,9}),
		({HIY"水晶","crystal","60/100",1500,120000,"35/70","15/10/35","40/10/22","40/10/22","40/10/22","40/10/22","10/9",3,15000,10}),
		({HIR"战神","mars","120/170",3000,140000,"35/75","15/10/35","5/1/4","5/1/4","5/1/4","5/1/4","",4,20000,11}),
		({HIB"灵魂","spirit","80/120",1000,160000,"40/80","15/15/35","40/10/25","40/10/25","40/10/25","40/10/25","10/10",4,25000,12}),
		({HIW"无敌","sunshine","150/250",2000,180000,"40/85","15/15/40","5/2/4","5/2/4","5/2/4","5/2/4","",5,30000,13}),
		({HIR+BLK"大唐","dark","100/150",1000,200000,"45/90","15/15/40","40/10/30","40/10/30","40/10/30","40/10/30","10/11",5,35000,14})
		});	
	
	
	myexp=me->query("combat_exp",1);
	taexp=killer->query("combat_exp",1);
      if (myexp<taexp/1.5 && random(myexp+taexp) < taexp && !wizardp(killer) ) 
         return 0;
//得到绿色装备
		i=random(11);
		armor=new(file[i]);
                 if (!armor) return 0;
		
		//得到防具的材料,对目标道行取随机值
		exp=random(myexp)/1000;
		if (exp>35000)  i=random(14);//四万年以上才能得暗黑装备
		else if (exp>30000) i=random(13);
		else if (exp>25000) i=random(12);
		else if (exp>20000) i=random(11);
		else if (exp>15000) i=random(10);
		else if (exp>10000) i=random(9);
		else if (exp>6000) i=random(8);
		else if (exp>4000) i=random(7);
		else if (exp>2000) i=random(6);
		else if (exp>1000) i=random(5);
		else if (exp>500) i=random(4);
		else if (exp>200) i=random(3);
		else if (exp>100) i=random(2);
           else  i=0;
		//i=6;
		//add by wsw 20051010
		armor->set("primitive_id",killer->query("id")); //爆出此装备的玩家ID
		armor->set("unique_code",time()); //以时间定义装备唯一识别码
		//计算绑定形式
		bind_pro = 10; //绑定机率,10%绑定
		bind_pro += to_int(atan(taexp/1000000)*180/3.1415926); 
		//armor->set("bind_pro",bind_pro);//测试用
		bind_pro = random(bind_pro);
		if (bind_pro>70) bind_type = 3;
		else if (bind_pro>40) bind_type = 2;
		else if (bind_pro>10) bind_type = 1;
		else bind_type = 0;
		
		armor->set("bind_type",bind_type); //0不绑定，1装备绑定，2拾取绑定,3，直接绑定。需修改wield.c，get.c，对应set("bind_id")
	        if (bind_type == 3) armor->set("bind_id",killer->query("id")); //绑定id，在wield或get里设置
	        //add end

		armor->set("changed",1);//有此属性，系统自动保存此装备
		armor->set("unbreak",1);//有此属性，兵器不能被打断，同时应该修改weapond.c及可打断兵器的pfm和cast 
					//龙宫huntian-hammer,perform break,cast dragonfire,方寸的perform leiting
		armor->set_name(name[i][0]+armor->query("name")+NOR,({name[i][1]+" "+armor->query("id"),armor->query("id")}));
		sscanf (name[i][2], "%d/%d", a1, a2) ;
		armor->set("durability/max",a1+random(a2-a1));//最大耐久度
		armor->set("durability/now",random(a2));//当前耐久度
		armor->set_weight((name[i][3]+armor->query_weight())/2);
        	armor->set("long",armor->query("name"));
        	armor->set("material", name[i][1]);	
        	armor->set("grade", name[i][14]);//等级 1－14
        	
         	//附加属性
         	sscanf (name[i][5], "%d/%d", a1, a2) ;
        	armor->set("armor_prop/armor",a1+random(a2-a1));//防御力
        	//armor->set("armor_prop/luck",random(name[i][7]+1));//幸运值，出连招的次数
        	if (sscanf (name[i][6], "%d/%d/%d", a1, a2,a3)==3)
        	{
                  if (random(200)<=a1) armor->set("armor_prop/cold_defence",a2+random(a3-a2));//冰系防御
                  if (random(200)<=a1) armor->set("armor_prop/fire_defence",a2+random(a3-a2));//火系防御
                  if (random(200)<=a1) armor->set("armor_prop/lightning_defence",a2+random(a3-a2));//电系防御
                  if (random(200)<=a1) armor->set("armor_prop/poison_defence",a2+random(a3-a2));//毒系防御
                  if (random(200)<=a1) armor->set("armor_prop/wind_defence",a2+random(a3-a2));//风系防御
        	}
        	switch(random(5000))//随机出全防的防具
        	{
        		case 0 :
        			armor->set("armor_prop/cold_defence",5+random(5));
        			armor->set("armor_prop/fire_defence",5+random(5));
        			armor->set("armor_prop/lightning_defence",5+random(5));
        			armor->set("armor_prop/poison_defence",5+random(5));
        			armor->set("armor_prop/wind_defence",5+random(5));
        			break;
        		case 1 :
        			armor->set("armor_prop/cold_defence",5+random(10));
        			armor->set("armor_prop/fire_defence",5+random(10));
        			armor->set("armor_prop/lightning_defence",5+random(10));
        			armor->set("armor_prop/poison_defence",5+random(10));
        			armor->set("armor_prop/wind_defence",5+random(10));
        			break;	
        		case 2 :
        			armor->set("armor_prop/cold_defence",5+random(15));
        			armor->set("armor_prop/fire_defence",5+random(15));
        			armor->set("armor_prop/lightning_defence",5+random(15));
        			armor->set("armor_prop/poison_defence",5+random(15));
        			armor->set("armor_prop/wind_defence",5+random(15));
        			break;
        	}
        	if (sscanf (name[i][11], "%d/%d", a1, a2)==2) 
        		if (random(100)<=a1) armor->set("armor_prop/chance",random(a2));//魔法装备获得率       	
        	armor->set("sockets/max",random(name[i][12]));//安放宝石数
        	armor->set("sockets/now",0);       		
		
		//价值
        	value=name[i][4];
        	value+=armor->query("durability/max")*50;
        	value+=armor->query("durability/now")*25;
        	value+=armor->query("sockets/max")*2000;
        	value+=armor->query("armor_prop/armor")*100;        	
        	value+=armor->query("armor_prop/cold_defence")*100;
        	value+=armor->query("armor_prop/fire_defence")*100;
        	value+=armor->query("armor_prop/lightning_defence")*100;
        	value+=armor->query("armor_prop/poison_defence")*100;
        	value+=armor->query("armor_prop/wind_defence")*100;
        	value+=armor->query("armor_prop/chance")*500;        	
        	armor->set("value", value);
        	
		//装备要求
		armor->set("armor_wiel/exp",name[i][13]);
                if(random(2))
                armor->set("armor_wiel/"+keys(tianfu1)[random(sizeof(tianfu1))],10+random(21));
                else 
                armor->set("armor_wiel/"+keys(tianfu2)[random(sizeof(tianfu2))],10+random(16));

     
		setname_armor(armor);
     if (wizardp(this_player()))
     tell_object(this_player(),HIM+"类型："+armor->query("armor_type")+"     初始等级："+armor->query("grade")+"\n"NOR);
		return armor;
}


object get_baoshi(object me,object killer)
{
	object baoshi;
	int i,j,value;
	int myexp,taexp,exp;
	string *file=({
  		"/d/obj/newitem/dazao/kuangshi.c",
		"/d/obj/newitem/baoshi/baoshi.c"});
	
	myexp=me->query("combat_exp",1);
	taexp=killer->query("combat_exp",1);
      if (myexp<taexp/1.5 && myexp > 3000000 && !wizardp(killer) )
        return 0;
//得到宝石
		baoshi=new(file[random(sizeof(file))]);
		return baoshi;
}
		
������
