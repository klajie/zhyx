#include <ansi.h>

inherit F_CLEAN_UP;

string *msg_dunno = ({
	CYN "$n" CYN "摇摇头，说道：“没听说过，没听说过。”\n" NOR,
	CYN "$n" CYN "疑惑地看着$N" CYN "，摇了摇头。\n" NOR,
	CYN "$n" CYN "睁大眼睛望着$N" CYN "，显然不知道$P" CYN "在说什么。\n" NOR,
	CYN "$n" CYN "耸了耸肩，很抱歉地说：“对不起，无可奉告。”\n" NOR,
	CYN "$n" CYN "说道：“嗯……这我可不清楚，你最好问问别人吧。”\n" NOR,
	CYN "$n" CYN "想了一会儿，说道：“对不起，你问的事我实在没有印象。”\n" NOR,
	CYN "$n" CYN "看着$N" CYN "，皱了皱眉头，说道：“我从没听说过这事，你去问别人吧。”\n" NOR,
});

string query_inquiry(object ob)
{
	int i = 0;
	mapping inq;
	string str = "", *indexs;

	if (mapp(inq = ob->query("inquiry")))
	{
		indexs = keys(inq);
		for (i = 0; i < sizeof(indexs); i++)
		{
			str = indexs[i] + " " + str;
		}
		str = "有关于 " HIY + str + NOR "的事情,我很高兴告诉你!";
		return str;
	}
	return "实在是对不起,我什么也不知道呀!";
}

int main(object me, string arg)
{
	string dest, topic, msg;
	object ob;
	mapping inquiry;
	object env;
	mixed info;

	seteuid(getuid());

	if (!arg)
		return notify_fail("你要问谁什么事？\n");

	if (sscanf(arg, "%s about %s", dest, topic) != 2 &&
		sscanf(arg, "%s %s", dest, topic) != 2)
		return notify_fail("你要问谁什么事？\n");

	env = environment(me);
	if (info = env->query("no_say"))
	{
		if (stringp(info))
		{
			write(info);
			return 1;
		}

		write("这个地方不能讲话。\n");
		return 1;
	}

	if (!objectp(ob = present(dest, env)))
		return notify_fail("这里没有这个人。\n");

	if (me->ban_say(1) && playerp(ob))
		return 0;

	if (!ob->is_character())
	{
		message_vision("$N对着$n自言自语。\n", me, ob);
		return 1;
	}

	if (ob == me)
	{
		message_vision("$N自己自言自语。\n", me);
		return 1;
	}

	if (!me->is_ghost() && me->query("jing") < 30 && !playerp(ob))
	{
		write("你现在的精神不太好，没法向别人打听。\n");
		return 1;
	}

	if (!ob->query("can_speak"))
	{
		message_vision(CYN "$N" CYN "向$n" CYN "打听有关『" HIG + topic + NOR CYN "』"
						"的消息，但是$p显然听不懂人话。\n" NOR,
					   me, ob);
		return 1;
	}

	if (!INQUIRY_D->parse_inquiry(me, ob, topic))
		message_vision(CYN "$N" CYN "向$n" CYN "打听有关『" HIG +
						   topic + NOR CYN "』的消息。\n" NOR,
					   me, ob);

	if (!living(ob))
	{
		message_vision(HIC "但是很显然的，$n" HIC "现在的状况没有"
						   "办法给$N" HIC "任何答覆。\n",
					   me, ob);
		return 1;
	}

	if (playerp(ob) || ob->is_chatter())
	{
		ob->set_temp("ask_you", me->query("id"));
		return 1;
	}

	if (!me->is_ghost())
		me->receive_damage("jing", 10 + random(10));

	if (topic == "all")
	{
		message_vision(CYN "$N对你悄声说道:" + query_inquiry(ob) + "!\n" NOR, ob);
		return 1;
	}

	if (msg = ob->query("inquiry/" + topic) || msg = ob->accept_ask(me, topic))
	{
		if (stringp(msg))
		{
			message_vision(CYN "$N" CYN "说道：" + msg + "\n" NOR, ob);
			return 1;
		}
	}
	else
		message_vision(msg_dunno[random(sizeof(msg_dunno))], me, ob);

	return 1;
}

int help(object me)
{
   write( @HELP
指令格式: ask <someone> about <something>

这个指令在解谜时很重要, 通常必须藉由此一指令才能
获得进一步的资讯。
HELP );
   return 1;
}
