// qianting.c 盘龙居前庭

#include <ansi.h> 
//** inherit PRIVATE_ROOM;

inherit ROOM;                                   /* EXAMPLE */

void create()
{
        object ob;

	set("short", "前庭");             /* EXAMPLE */
//**    set("short", "ROOM_NAME前庭");
	set("long", @LONG
这里似乎非常安静，倒是时不时听见鸟儿唧唧喳喳的叫。院中不少树
木已然有遮天之势，肃穆非常。
LONG );

	set("default_long", "这里似乎非常安静，听不到什么声响，到是时不" /* EXAMPLE */
                            "时听见鸟儿唧唧喳喳的叫。院中不少树木已然有" /* EXAMPLE */
                            "遮天之势，肃穆非常。");                     /* EXAMPLE */
                                                                         /* EXAMPLE */

	set("exits", ([
                "south"  : __DIR__"dayuan",
                "east"   : __DIR__"zuowei",
                "west"   : __DIR__"youwei",
	]));

        set("outdoors", "OUTDOORS");
        set("no_sleep_room", 1);
        set("gate", "close");
        setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}

void init()
{
        add_action("do_push", "push");
        add_action("do_close", "close");       
//**    add_action("set_code", "setcode");
//**    add_action("type_code", "typecode");
}

int set_code(string arg)
{
	object me;
       me = this_player();
       if ( me->query("id") != query("room_owner_id") )
       return notify_fail(HIR"不是屋主不能设定密码!\n"NOR);
       if ( !arg) 
       return notify_fail("你要把密码设定成什么?\n");
       if ( sizeof(arg) > 10 ) 
       return notify_fail("密码长度不能超过10个字符!\n");

       this_object()->set("code", arg);  
       write(HIG"设定了密码为" + arg +"\n"NOR);     
//**   save();
       return 1;
}

int type_code(string arg)
{
       object me = this_player();
       if ( me->query("id") == query("room_owner_id") )
       return notify_fail(HIG"屋主不用输入密码!\n"NOR);
       if ( !arg ) 
       return notify_fail("你要输入什么密码?\n");
       if ( arg != query("code") )
       return notify_fail(HIR"对不起，密码错误，你不能进入这所房子！\n"NOR);
       me->set_temp("roomcode_ok/" + query("room_owner_id"),1); 
       write(HIG"密码正确，你可以push gate开门了。\n"NOR);
       return 1;

}

int do_push()
{        
        object me;
        object room;

        if (query("gate") == "open")
                return notify_fail("大门开着呢，你还推什么？\n");

        me = this_player();
        
        if (me->query("id") == query("room_owner_id") || ! query("code") )
        {
                message_vision("$N用力一推大门，就听见大门“吱呀呀”的开了。\n",
                               me);
        } else
        if ( me->query("id") != query("room_owner_id") )
        {                     
               if ( ! me->query_temp("roomcode_ok/" + query("room_owner_id") ) )               
               { 
                 write(HIR"要进屋得先用typecode输入密码!\n"NOR);
                 return 1; 
               }     
               message_vision("$N用力一推大门，就听见大门“吱呀呀”的开了。\n",
                               me);
                           
        }        
        

        room = get_object(__DIR__"zoudao");
        message("vision", "大门“吱呀呀”的被人推开了。\n", room);       
        set("gate", "open");
        set("exits/north", __DIR__"zoudao");
        room->set("exits/south", __FILE__);
        room->set("gate", "open");
        remove_call_out("do_close");
        call_out("do_close", 10, 0, 1);
        return 1;
}

int do_close(string arg, int n)
{
        object me;
        object room;

        if (query("gate") == "close")
                return notify_fail("大门关着呢，你还再关一遍？\n");

        me = this_player();
        
        if (! n && me )       
                message_vision("$N用力一拉大门，就听见大门“吱呀呀”的关上了。\n",
                               me);
                        
        message("vision", "大门“吱呀呀”的被人关上了。\n",
                        this_object());

        room = get_object(__DIR__"zoudao");
        message("vision", "大门“吱呀呀”的关上了。\n", room);
        set("gate", "close");
        delete("exits/north");
        room->delete("exits/south");
        room->set("gate", "close");
        return 1;
}

int valid_leave(object me, string dir)
{
        

//**        if ( dir == "north" &&  me->query("id") != query("room_owner_id") 
//**                 && query("code") &&
//**             ! me->query_temp("roomcode_ok/" + query("room_owner_id") ) )               
//**        { 
//**                 write(HIR"要进屋得先用typecode输入密码!\n"NOR);
//**                 return 0; 
//**        }  
       
        if ( me->query("id") == query("room_owner_id")        
             && ! query("code") )
        {  
           message("vision", HIR"\n你尚未用setcode设置密码！"
                             "小心盗贼破门而入!\n\n"NOR, me);
         }          

       
        me->delete_temp("roomcode_ok/" + query("room_owner_id") ); 
        return ::valid_leave(me, dir);           
        return 1;
}




