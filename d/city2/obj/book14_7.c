
inherit ITEM;
inherit F_NOCLONE;

int do_tear(string arg);

void init()
{
        add_action("do_tear", "tear");
}

void create()
{
        set_name("四十二章经七", ({"book7"}));
        set_weight(1000);
        set("long", "\n一本镶白旗的经书,封皮(binding)很精致。\n");
        set("unit", "本");
        set("material", "paper");
        setup();
        set("startroom", "/d/city2/aobai9");
        check_clone();
}

int do_tear(string arg)
{
	object me;
	string dir;
	me = this_player();

        if( !arg || arg=="" ) return 0;

	if(arg=="book7")
	{
	message_vision("$N一下把经书撕得粉碎。\n", this_player());
	destruct(this_object());
	return 1;
	}

	if( sscanf(arg, "book7 %s", dir)==1 ) {
	if( dir=="binding" ) {
		if(this_object()->query("hasgot"))
		message_vision("$N将封皮撕开,发现羊皮已经被取走了。\n", this_player());
		else
		{
		message_vision("$N将封皮撕开，几块羊皮掉了下来。\n", this_player());
		message_vision("$N先将羊皮上的地图记了下来，然后把它们烧掉了。\n", this_player());
	        me->set("huanggong/haspi7", 1);
                this_object()->set("hasgot",1);  
        	}
	}
        else
	{
	message_vision("$N一下把经书撕得粉碎。\n", this_player());
	destruct(this_object());
	}
	return 1;
        }	
}
