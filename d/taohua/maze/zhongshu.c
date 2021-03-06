// Code of ShenZhou
#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	object ob;

        set("short", "石阵中枢");
        set("long", @LONG
这是桃花岛石阵中枢所在地，四壁(wall)上绘着二十八星宿图，地上
密密麻麻刻着诸般卦象。地上一个太极图(tu)，周围分别环绕先天八卦与
后天八卦，外圈则是推演而出的六十四卦。一缕天光悄然注下，映得室中
忽明忽暗，似乎万籁俱寂，又似乎诸声杂陈，动静之间，不可琢磨。
LONG
        );

        set("exits", ([
                "up" : "/d/taohua/neidong",
        ]));

        set("no_fight", 1);
	set("no_steal", 1);
	set("no_beg",1);

        set("item_desc", ([
                "tu" : "太极图上阴(yin)鱼与阳(yang)鱼分列左右。\n",
		"wall" :
"青龙七宿：角木蛟、亢金龙、氐土貉、房月狐、心日兔、尾火虎、箕水豹\n"
"白虎七宿：奎木狼、娄金狗、胃土雉、昂日鸡、毕月鸟、觜火猴、参水猿\n"
"朱雀七宿：井木犴、鬼金羊、柳土獐、星日马、张月鹿、翼水蛇、轸火蚓\n"
"玄武七宿：斗木獬、牛金羊、女土蝠、虚日鼠、危月燕、室火猪、壁水＜犭俞＞\n",
        ]));

	set("cost", 1);

        setup();
}

void init()
{
        add_action("do_sit", "sit");
	add_action("do_stand", "stand");
	add_action("do_leave", "leave");
	add_action("do_think", "lingwu");
}

int do_think()
{
	object me = this_player();
	int qmwx = me->query_skill("qimen-wuxing",1);

	if (me->is_busy())
		return notify_fail("你现在正忙着呢。\n");

	if (!me->query_temp("sitted") && !me->query_temp("standed") )
		return notify_fail("你看着地上的太极图，琢磨着是否可以坐(sit)上去或者站(stand)上去。\n");

	if( !query("yin") || !query("yang") )
		return notify_fail("太极图上只有你一个人，你还需要一位同伴协助运功。\n");

	if ( me->query_skill("qimen-wuxing", 1) < 170 &&
	  !present("he tu", me) && !present("luo shu", me) ) 
	{
		tell_object(me,MAG"你只觉气血翻涌，无数异像怪声向你袭来！\n"NOR);
		me->unconcious();
		return 1;
	}

	if( !me->query("taohua_maze") ) {
		tell_object(me,MAG"你只觉气血翻涌，无数异像怪声向你袭来！\n"NOR);
		me->unconcious();
		return 1;
	}

	if( me->query("jing") < 100 )
		return notify_fail("你现在精神不佳，无法定下心来思考！\n");

	if( (int)me->query("potential") - (int)me->query("learned_points") < 1 )
		return notify_fail("你的潜能不足，无法领悟基本武功！\n");

	me->receive_damage("jing", random(qmwx));

	if(random(20) == 0) {
		me->add("potential", -2);
		me->improve_skill("qimen-wuxing", qmwx/2 + random(qmwx*2));
		write( "只觉脑中豁然开朗，你对奇门五行的领悟又进了一层！\n" );
	}
	else if(random(10) == 0) {
		me->add("potential", -1);
		me->improve_skill("qimen-wuxing", qmwx/5 + random(qmwx*2));
		write( "你冥思苦想，对奇门五行渐渐加深一层体会！\n" );
	}
        else if(random(2) == 0) {
                me->improve_skill("qimen-wuxing", qmwx/10 + random(qmwx/2));
                write( "你苦苦思索，隐约把握到了奇门五行之中的一些难解之处。\n" );
        }
	else {
                write( "你坐立不安，潜心苦思奇门五行上的难解之处。\n" ); 
	}
	return 1;
}

int do_sit(string arg)
{
        mapping skl;
        object me=this_player();
        string *sname;
        int i,j;

        if( !arg ) 
		return notify_fail("你想坐在哪里？\n");

	if( arg != "yin")
		return notify_fail("玄门重地，不要随地乱坐！\n");


	if( !me->query("family") || me->query("family/family_name") != "桃花岛")
		return notify_fail("你笨拙的想坐到“阴”上，结果一阵阴气侵入你屁股，你一下子跳了起来。\n");

	if( me->query_temp("sitted"))
		return notify_fail("你已经坐在“阴”上面了！\n");

        if( me->query_temp("standed"))
                return notify_fail("你已经站在“阳”上面了！\n");

	if( query("yin")){
		write(query("yin")->name()+"已经坐在“阴”上面了！\n");
		tell_object(query("yin"),"看起来"+me->query("name")+"也想坐上来。\n");
		return 1;
	}

	message_vision("$N盘膝坐上左面阴鱼图。\n", me);

	if ( me->query_skill("qimen-wuxing", 1) < 150 &&
	     !present("he tu", me) && !present("luo shu", me) )
	{
		tell_object(me,MAG"你只觉气血翻涌，无数异像怪声向你袭来！\n"NOR);
		me->unconcious();
		return 1;
	}

	message_vision(HIG"$N眼观鼻，鼻观心，由制心止自体真止，顷刻之间已神游物外。\n"NOR, me);
	me->set_temp("sitted", 1);
	set("yin", me);

	return 1;
}

int do_stand(string arg)
{
	mapping skl;
	object me=this_player();
        string *sname;
        int i,j;

        if( !arg ) 
		return notify_fail("你想站在哪里？\n");

	if( arg != "yang")
		return notify_fail("玄门重地，不要随处乱走！\n");

	if( !me->query("family") || me->query("family/family_name") != "桃花岛")
		return notify_fail("你笨拙的想站到“阳”上，结果一个不小心，摔了四脚朝天。\n");

        if( me->query_temp("standed"))
                return notify_fail("你已经站在“阳”上面了！\n");

        if( me->query_temp("sitted"))
                return notify_fail("你已经坐在“阴”上面了！\n");

        if( query("yang")){
                write(query("yang")->name()+"已经站“阳”在上面了！\n");
		tell_object(query("yang"),"看起来"+me->query("name")+"也想站上来。\n");
                return 1;
        }

        message_vision("$N缓步站上右面的阳鱼图。\n", me);

        if ( me->query_skill("qimen-wuxing", 1) < 150 &&
             !present("he tu", me) && !present("luo shu", me) )
	{		
		tell_object(me,MAG"你只觉气血翻涌，无数异像怪声向你袭来！\n"NOR);
		me->unconcious();
                return 1;
        }
	message_vision(HIY"$N足下虚步先后天八卦方位，自先天而后天，片刻间已万物不萦于怀。\n"NOR,me);
	me->set_temp("standed", 1);
	set("yang", me);

        return 1;
}

int do_leave()
{
	object me;

	me = this_player();
	if (me->query_temp("sitted")) {
		me->delete_temp("sitted");
		delete("yin");
		message_vision("$N长吁一口气，收摄心神，站起身来。\n",me);
	}

        if (me->query_temp("standed")) {
                me->delete_temp("standed");
                delete("yang");
		message_vision("$N调息片刻，停住步伐，看上去有点疲倦。\n",me);
	}

	return 1;
}

int valid_leave(object me, string dir)
{
	if (me->query_temp("sitted") || me->query_temp("standed"))
		return notify_fail("你周天搬运未毕(leave)，贸然离开太极图恐受内伤！\n");
	return ::valid_leave(me, dir);
}
