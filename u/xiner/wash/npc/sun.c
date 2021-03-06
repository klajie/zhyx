//斗战胜佛(转世npc 调整四围)

#include <ansi.h>
inherit  NPC;
int ask_wash();

void create()
{
	set_name("孙悟空", ({ "sun wukong", "sun" }));
	set("title", HIY "斗战胜佛" NOR);
	set("nickname", HIW "脱胎换骨" NOR);
	set("gender", "男性");
	set("age", 3000);
	set("long", @LONG
一团黄色的光芒中隐隐然透出一人，细看却不能捕捉他的身形。
LONG );
        set("gender", "男性" );
        set("age", 3000);
        set("attitude", "friendly");
        set("max_neili", 100000);
        set("neili", 100000);
        set("max_jing", 100000);
        set("jing", 100000);
        set("max_qi", 100000);
        set("qi", 100000);
        set("jingli", 100000);
        set("max_jingli", 100000);
        set("str", 200);
        set("int", 200);
        set("con", 200);
        set("dex", 200);
        set("combat_exp", 99999999);

        set("inquiry", ([ 
            "脱胎换骨" : (: ask_wash :), 
        ])); 

        set_skill("unarmed", 2000);
        set_skill("parry", 2000);
        set_skill("dodge", 2000);
	set_skill("force", 2000);

        set("jiali", 1000);

        set_temp("apply/unarmed_damage", 800);
        set_temp("apply/armor", 3000); 

        setup();
        carry_object("d/city/obj/jiasha")->wear(); 
}


void init()
{
    add_action("do_ketou", "ketou");
    add_action("do_tuotai", "tuotai");  
}

int ask_wash()
{    
    object me = this_player();
    if (me->query("mark/sun_wash")) //已经洗过点判定
    {
       command("xixi " + me->query("id"));        
       return 1;
    }
    me->set_temp("sun/reborn/ask1",1);
    command("look " + me->query("id"));
    command("say 你这个小娃娃才转世的吧！");    
    command("say 可是尚对自身天赋不满？");
    tell_object(me, HIW"孙悟空在你耳边说道，"
                    "你给我磕个头(ketou)先！\n"NOR);   
    return 1;
}

int do_ketou()
{
    object me = this_player();
    string answer;
    if (! me->query_temp("sun/reborn/ask1") ) return 0; //还没问呢!

    if (! me->query("reborn") ) //没有转世的判定
      {
       command("kok " + me->query("id"));        
       command("say 别给我捣乱！好好练功等转世了再来！");
       return 1;
      }

    if (me->query("mark/sun_wash")) //已经洗过点判定
      {
       command("xixi " + me->query("id"));        
       return 1;
      }
     me->delete_temp("sun/reborn/ask1");
     message_vision(WHT"孙悟空嬉皮笑脸的对$N说道：\n“孺子可教也！”\n"NOR, me);                
     write(HIG"孙悟空赐你一次脱胎换骨的机会，可以重新调整四项天赋，\n"NOR
           HIR"但是脱胎换骨后以前增加的先天属将全部无效，\n"
              "实战经验及一切技能全部清除，你可想清楚了？"NOR HIY
             "\n请回答(Y/N)\n" NOR);
     input_to("do_yes", answer);
     return 1;
}


int do_yes(string answer)
{   
   object me;
   me = this_player();
   if ( answer == "Y" || answer == "yes" || answer == "y" )
   {
       me->set_temp("sun/reborn/ask2",1);	//同意洗点
       write(HIG"好的，既然你心意已决，你可以重新分配126点天赋，\n"
                "单项必须大于等于13，小于等于40,\n"
                "指令是tuotai <膂力> <悟性> <根骨> <身法>\n\n"NOR);
     	
   } else
   {            
   	write("好的，改变主意的话随时回来。\n");
   }
   return 1;	
}

int do_tuotai(string arg)
{
    object me;
    int tmpstr, tmpint, tmpcon,tmpdex;
    string answer;

    me = this_player();
    if	(!me->query_temp("sun/reborn/ask2")) return 0;
    if( !arg || sscanf(arg, "%d %d %d %d", tmpstr, tmpint, tmpcon,tmpdex)!=4 )
                return notify_fail(HIG"指令格式：tuotai <膂力> <悟性> <根骨> <身法>\n"NOR);

    if( tmpstr>40) return notify_fail("你所选择的膂力参数不能大于40。\n");
    if( tmpstr<13) return notify_fail("你所选择的膂力参数不能小于13。\n");
    if( tmpint>40) return notify_fail("你所选择的悟性参数不能大于40。\n");
    if( tmpint<13) return notify_fail("你所选择的悟性参数不能小于13。\n");
    if( tmpcon>40) return notify_fail("你所选择的根骨参数不能大于40。\n");
    if( tmpcon<13) return notify_fail("你所选择的根骨参数不能小于13。\n");
    if( tmpdex>40) return notify_fail("你所选择的身法参数不能大于40。\n");
    if( tmpdex<13) return notify_fail("你所选择的身法参数不能小于13。\n");
    if((tmpstr+tmpint+tmpcon+tmpdex)>126) 
    return notify_fail("你所选择的参数总和不能大于126。\n");
    write(HIC "指定天赋为 臂力:" + tmpstr + " 悟性:" + tmpint + " 根骨:" +
          tmpcon + " 身法:" + tmpdex + "，可以吗？Y/N。\n" NOR, me);

    me->set_temp("/sun/reborn/str",tmpstr);
    me->set_temp("/sun/reborn/int",tmpint);
    me->set_temp("/sun/reborn/con",tmpcon);
    me->set_temp("/sun/reborn/dex",tmpdex);

    input_to("do_yes2", answer);
    return 1;
}

int do_yes2(string answer)
{
   object me;
   mapping my, my_sk;
   string skills_name;

   me = this_player();
   my = me->query_entire_dbase();
   my_sk = me->query_skills();

   if ( answer == "Y" || answer == "yes" || answer == "y" )
   { 	 	
      message_vision(HIY "只见一道金光钻入了$N体内，$N顿时感到头痛欲裂，"   
                         "苦不堪言。\n\n"NOR, me);

		me->set("mark/sun_wash", 1);//洗点记录
	        my["str"] = me->query_temp("/sun/reborn/str");
        	my["int"] = me->query_temp("/sun/reborn/int");
	        my["con"] = me->query_temp("/sun/reborn/con");
	        my["dex"] = me->query_temp("/sun/reborn/dex");

		//清除吃丹的记录
                me->set("gift/str/all",0),
                me->set("gift/str/succeed",0),
                me->set("gift/str/fail",0),
                me->set("gift/int/all",0),
                me->set("gift/int/succeed",0),
                me->set("gift/int/fail",0),
                me->set("gift/con/all",0),
                me->set("gift/con/succeed",0),
                me->set("gift/con/fail",0),
                me->set("gift/dex/all",0),
                me->set("gift/dex/succeed",0),
                me->set("gift/dex/fail",0),
		//清除前世中的故事
                me->delete("gift/feng");
                me->delete("gift/lighting");
                me->delete("gift/water");
                me->delete("gift/sun");
		//清除门派记录
              //me->add("detach/" + me->query("family/family_name"), 1);
                me->delete("family");
                me->set("gongxian", 0);
                me->delete("quest");
                me->delete_temp("quest");
                me->set("title", "普通百姓");

                me->set("combat_exp", 0);       	
                me->set("max_neili",0);
                me->set("neili",0);
                me->set("max_jingli",0);
                me->set("jingli",0);
                me->set("max_qi",100);
                me->set("eff_qi",100);
                me->set("qi",100);
                me->set("max_jing",100);
                me->set("eff_jing",100);
                me->set("jing",100);
                me->set("shen",0);
                me->delete("breakup");
                me->delete("animaout");
                me->set("mud_age",0);            
                me->set("age", 14);

	        message("vision", HIG"【天界传闻】据说有人已得齐天大圣恩典，"
                             "重塑金身。\n"NOR, users());

		me->unconcious();

        	foreach(skills_name in keys(my_sk))
		{
		me->delete_skill(skills_name);
              	}
		me->delete("mark/guofu_ok"); 	 
		me->delete("mark/guofu_over"); 	
                me->delete("mark/guofu_out"); 			
		me->set("potential", me->query_potential_limit());
		me->delete_temp("sun/reborn/ask2");
		log_file("static/reborn", sprintf("%s(%s) rewash at %s .\n",
			me->name(1), me->query("id"), ctime(time())));

   } else
   {
   	  write("那请重新选择天赋。\n");
   }
   return 1;		

}
