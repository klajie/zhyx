//xym_guard.c 

inherit NPC; 

#include <ansi.h> 

int ask_xym(object me, object ob); 
void create() 
{ 
     set_name("守卫",({"shou wei","guard"}) ); 
     set("long","这是一位长的英姿勃勃的年轻人。\n"); 
     set("title","侠义盟剑客"); 
     set("gender","男性"); 
     set("age",20); 
     set("combat_exp",100); 
     set("inquiry",([ 
          "侠义盟" : (: ask_xym :), 
     ]) ); 
     setup(); 
} 

int ask_xym(object me, object ob) 
{ 
     me=this_player(); 
     ob=this_object(); 
     if (me->query("bang_good/name")!="侠义盟" && (int)me->query("shen") >= 0 ) 
     { 
           command("famours " + me->query("id")); 
           tell_object(me,"守卫笑眯眯地对你说：“是想加入咱们侠义盟吧？请进请进。”\n"); 
           me->set_temp("good_xym1",1); 
           return 1; 
     } 
     if( me->query("bang_bad") || (int)me->query("shen") < 0 ) 
     { 
           ob->command("say 哪里来的邪魔歪道，找打么？\n"); 
           return 1; 
     } 

     tell_object(me,"侠义盟守卫奇怪道：“同为本帮兄弟，你何出此言啊？”\n"); 
     return 1; 
} 

