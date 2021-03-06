// bojuan.c

inherit ITEM;

void create()
{
	set_name("帛卷", ({ "bo juan", "bo", "juan" }));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "卷");
		set("long",
			"这是一卷帛卷，里面写道 ：\n"
			"庄子“逍遥游”有云：穷发之北有冥海者，天池也。有鱼焉，其广数千里，未有知其修也。\n"
			"又云：且夫水之积也不厚，则其负大舟也无力。覆杯水于坳堂之上，则芥为之舟；置杯焉\n则胶，水浅而舟大也…………\n"
			"\n你可以试着研习(read)一下。");
		set("value", 500);
		set("no_sell", 1);
		set("no_steal",1);
		set("no_put", 1);
		set("no_drop", 1);
		set("material", "silk");
	}
}

void init()
{
	if( this_player() == environment() )
	{
		add_action("do_study", "read");
		remove_call_out("destroy"); 
		call_out("destroy", 300); 
	}
}

int do_study(string arg)
{
	object me = this_player();
	int cost=10,myskill;	

	if ( arg != "bo" && arg != "juan" && arg !="bo juan" )
		return notify_fail("你要读什么？\n");
	if( (int)me->query("jing") < 25 )
	{
		write("你现在过于疲倦，无法专心下来研读新知。\n");
		return 1;
	}
	if (me->is_busy()) return notify_fail("你现在正忙着呢。\n");

	if (me->query("dex") < 30)
		return notify_fail("你的先天身法不足无法学习凌波微步！\n");

	if( (int)me->query_skill("literate",1) < 100 )
		return notify_fail("你的读书写字太生疏，无法理帛卷所写的东西。\n");

        if ((int)me->query_skill("yinyang-shiertian", 1))
	{
		call_out("destroy", 1);
                return notify_fail("你已将凌波微步融汇贯通，合成了普天之下最强"
                                   "的武功，不必再分开学习了。\n");
	}

//	if (me->query("family")==0||me->query("family")["family_name"]!="逍遥派") 
//		return notify_fail("想学更高深的凌波微步，必须加入我逍遥派。\n");

	if ( me->is_fighter()) return notify_fail("战斗中无法阅读新知！\n");

	if (!me->query("reborn")) return notify_fail("你觉得帛卷上所说的东西太深奥了!\n");

	if ( (int)me->query_skill("lingbo-weibu",1) < 1 )
	{
	    if ((int)me->query("jing")>cost)
	       	{
			me->receive_damage("jing", 20);
			me->improve_skill("lingbo-weibu", (me->query_skill("lingbo-weibu",1)+me->query("int")));
			message_vision("$N正在专心研读凌波微步。\n", me);
			call_out("destroy", 1);
			return 1;
		}
	    else
		{
			cost=me->query("jing");
			write("你现在过于疲倦，无法专心下来研读凌波微步。\n");
		}
	}
	call_out("destroy", 1);
	return notify_fail("你对着帛卷看来看去，无法从中领悟出更高深的道理。\n");
}

int destroy() 
{ 
    tell_room(environment(this_object()),  
               "一阵风吹来，帛卷因为年代太久风化成灰烬了!\n"); 
    destruct(this_object()); 
    return 1; 
}
