inherit ROOM;

void create()
{
        set("short", "书院书库");
        set("long", @LONG
这里是书院的图书馆，窗明几净，一尘不染。壁上的书架
堆满侠客行的先贤们的文选，记录了侠客行的风风雨雨和无数
凄婉的、遥远磨灭不去的传说。
LONG);
        set("item_desc", ([
            "shelf" : "此处已经被衙门查封了。\n",
        ]));
        set("no_fight", 1);
        set("no_fire",1);
        set("exits", ([
            "down" : __DIR__"shuyuan",
            "up" : __DIR__"shuyuan3",
        ]));
  /*      set("objects", ([
             "/u/cindy/cindy":1,
             "/adm/npc/mike":1,
               ]));    */

       set("objects", ([
      //       "/u/sanben/npc/dumb":1, 
           //  "/u/sanben/yuanxiao/lottery" : 1,            
       ])); 
        set("no_clean_up", 0);
       set("coor/x",10);
        set("coor/y",10);
        set("coor/z",10);
        setup();

        //replace_program(ROOM);
}