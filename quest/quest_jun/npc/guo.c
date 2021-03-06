// guojing.c 无敌大将军
inherit NPC;
#include <ansi.h>
string * degree_desc = ({
       BLU "士卒" NOR,
       BLU "游击" NOR,
       HIC "参将" NOR,
       HIC "裨将" NOR,
       HIY "佐将" NOR,
       HIY "副将" NOR,
       HIR "将军" NOR,
       HIR "提督" NOR,
});               
string clear_degree(string arg);
int ask_degree();
int add_degree(object ob,int lv);
string ask_jianlou();
string ask_fuming();
string ask_shoucheng();
string ask_chetui();

void create()
{
        set_name("岳飞", ({"yue fei", "yue", "fei"}));
        set("nickname", HIY"精忠报国"NOR);
        set("gender", "男性");
        set("age", 41);
        set("long", 
                "他就是人称精忠报国的大将军岳飞。\n");
        set("attitude", "friendly");
        set_max_encumbrance(100000000);
        set("per", 20);
        set("str", 40);
        set("int", 20);
        set("con", 30);
        set("dex", 25);
        set_temp("no_kill",1);
        set("chat_chance", 1);
        set("chat_msg", ({
                "岳飞叹了口气道：“金兵越来越多了...\n",
                "岳飞说道：“大丈夫在世，一定要为国为民。\n",
        }));

        set("inquiry", ([
                 "守城"  : (: ask_shoucheng :),
                 "复命"  : (: ask_fuming :),
                 "撤退"  : (: ask_chetui :),
//                 "狙击"  : (: ask_jianlou :), 
                ]));

        set("qi", 8000);
        set("max_qi", 8000);
        set("jing", 8000);
        set("max_jing", 8000);
        set("neili", 24000);
        set("max_neili", 24000);
        set("jiali", 500);
        
        set("combat_exp", 25000000);
        set("score", 200000);
         
        set_skill("force", 400);                // 基本内功
        set_skill("huntian-qigong", 400);        // 混天气功
        set_skill("unarmed", 400);                // 基本拳脚
        set_skill("xianglong-zhang", 400);        // 降龙十八掌
        set_skill("dodge", 400);                // 基本躲闪
        set_skill("xiaoyaoyou", 400);                // 逍遥游
        set_skill("parry", 400);                // 基本招架
        set_skill("arrow", 400);
        set_skill("lianzhu-arrow", 400);

        map_skill("arrow", "lianzhu-arrow");         
        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "xianglong-zhang");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "xianglong-zhang");
        prepare_skill("unarmed","xianglong-zhang");
        setup();
        
        carry_object("/clone/misc/cloth")->wear();
}

string ask_shoucheng()
{
        object *ene;
        object me = this_player();

        if(is_fighting()) 
        {
                ene=query_enemy();
                
                if(sizeof(ene)>1) return "“请"+RANK_D->query_respect(me)+"稍等片刻，我先和这"+sizeof(ene)+"位高手切磋几下！”\n";
                if(sizeof(ene)==1) return "“请"+RANK_D->query_respect(me)+"稍等片刻，我先和"+ene[0]->name()+"切磋几下！”\n";
        }

        if(me->query_temp("guo_shoucheng/mark_shadi") || me->query_temp("guo_jianlou/mark_jianlou") )
        return "“"+RANK_D->query_respect(me)+"不是已有任务了吗！”\n";

       if ((int)me->query("combat_exp")<300000)
       return "“"+RANK_D->query_respect(me)+"手无缚鸡之力，还是别领任务的为好！”\n";

       if ( (int)me->query_skill("force") < 20 )
       return "守城是件危险工作，我看"+RANK_D->query_respect(me)+"的基本内力不足！\n";

       if ( !me->query("family/family_name") )
       return "“"+RANK_D->query_respect(me)+"无门无派，来历不明，不敢有劳！”\n";

       if ((int)me->query_condition("jobshadi_failed"))
       {
        message_vision("$N对着$n摇了摇头说：逃跑失败了还来见我??\n", this_object(), me);
        return "“"+RANK_D->query_respect(me)+"你还是别领任务的为好！”\n";
       }

       if( me->query("guo_shoucheng/failed") )
       {
         me->apply_condition("jobshadi_failed",16);
         return "“临阵脱逃，还敢回来见我！！？？”\n";
       } 

       if ((int)me->query_condition("jobshadi_limit")>1)
       {
        message_vision("$N对着$n摇了摇头说：你不是正做着吗??\n", this_object(), me);
        return "“"+RANK_D->query_respect(me)+"你快点回你的岗位上去！”\n";
       }

       if ((int)me->query_condition("guojob2_busy"))
       {
        message_vision(CYN"$N对着$n摇了摇头说：疲惫之师不利作战！！\n"NOR,
                                                        this_object(), me);
        return "“"+RANK_D->query_respect(me)+"你还是休息一下再来吧！”\n";
       }
       
       if (me->query("shen")>0)
       {
        switch( random(2) ) {
                case 0:
                        me->set_temp("guo_shoucheng/mark_shadi",1);
                        me->set_temp("guo_shoucheng/carry_location","eastgate1");                
                return "“现在金兵侵犯中原，这位"+RANK_D->query_respect(me)+"去玄武内门帮助宋军守城吧。";

                       break;
                case 1:
                        me->set_temp("guo_shoucheng/mark_shadi",2);
                        me->set_temp("guo_shoucheng/carry_location","northgate1");                
                return "“现在金兵侵犯中原，这位"+RANK_D->query_respect(me)+"去青龙内门帮助宋军守城吧。";

                       break;
                }        
        }
        else
        {
        switch( random(2) ) {
                case 0:
                        me->set_temp("guo_shoucheng/mark_shadi",3);
                        me->set_temp("guo_shoucheng/carry_location","southgate1");
                return "“现在金兵侵犯中原，这位"+RANK_D->query_respect(me)+"去朱雀内门帮助宋军守城吧。";

                       break;
                case 1:
                        me->set_temp("guo_shoucheng/mark_shadi",4);
                        me->set_temp("guo_shoucheng/carry_location","westgate1");
                return "“现在金兵侵犯中原，这位"+RANK_D->query_respect(me)+"去白虎内门帮助宋军守城吧。";

                       break;
                }
        }
}



string ask_fuming()
{
        int job_pot,job_sc,job_exp,job_tihui,reward;
        object me = this_player();

        if( !me->query_condition("jobshadi_failed") && me->query("guo_shoucheng/failed") )
        {
         me->delete_temp("guo_shoucheng");
         me->delete_temp("guo_jianlou"); 
         me->apply_condition("jobshadi_failed",15);
         return "“临阵脱逃，还敢回来复命！！？？”\n";
        } 

        if( me->query_temp("guo_shoucheng/help_killed")
            && !me->query_temp("guo_shoucheng/job_over") ) 
        {
                 job_exp=((int)me->query_temp("guo_shoucheng/help_killed"))*40;
                job_pot=job_exp*2/3;
                job_tihui=job_pot/2;
                job_sc=job_pot/2;
                job_exp=job_exp;
                me->add("combat_exp", job_exp);
                me->add("potential",job_pot);
                me->add("experience",job_tihui);
                me->add("score",job_sc);
                tell_object(me,HIW"你被奖励了"+chinese_number(job_exp)+"点经验值！及"+chinese_number(job_pot)+"点潜能！及"+chinese_number(job_tihui)+"点体会,"+chinese_number(job_sc)+"点阅历！\n"NOR);
                me->delete_temp("guo_shoucheng/help_killed");        
                me->apply_condition("guojob2_busy",4);
                me->add("guo_shoucheng/reward_exp", job_exp);
                me->add("guo_shoucheng/reward_potential",job_pot);  
                me->add("guo_shoucheng/reward_experience",job_tihui);  
                me->add("guo_shoucheng/reward_potential",job_pot);  
        return "“"+RANK_D->query_respect(me)
               +"，为国杀敌，不错不错！”\n";
        }
           
        if( (!me->query_temp("guo_shoucheng/mark_shadi")
                || !me->query_temp("guo_shoucheng/job_over")) 
             && (!me->query_temp("guo_jianlou/mark_jianlou")
                || !me->query_temp("guo_jianlou/job_over")) )    
        return "“你好象没完成任务吧，还来复什么命？”\n";
        
        if(me->query_temp("guo_shoucheng/killed_mgb")<2 
           && me->query_temp("guo_jianlou/killed_mgb")<2)
        {
         me->delete_temp("guo_shoucheng");

         me->delete_temp("guo_jianlou");  
         return "“你杀了几个敌人啊，就从前线逃回来了？\n";
        }

        message_vision(CYN "$N对$n说道：“"+RANK_D->query_respect(me)+"辛苦了，去休息一下吧！”\n" NOR, this_object(), me);
          job_exp=((int)me->query_temp("guo_shoucheng/killed_mgb"))*30;
         job_exp=job_exp+((int)me->query_temp("guo_jianlou/killed_mgb"))*25; 
        job_pot=job_exp*2/3;
        job_tihui=job_pot/2;
        job_sc=job_pot/2;
        reward=((int)me->query_temp("guo_shoucheng/killed_mgb")
               + (int)me->query_temp("guo_jianlou/killed_mgb"))/5;

        tell_object(me, HIW"你被奖励了"+chinese_number(job_exp)+"点经验值及"+chinese_number(job_pot)+"点潜能及"+chinese_number(job_tihui)+"点体会,"+chinese_number(job_sc)+"点阅历！！\n"NOR);
        me->apply_condition("guojob2_busy",4);
        me->add("combat_exp", job_exp);
        me->add("potential",job_pot);
        me->add("experience",job_tihui);
        me->add("score",job_sc);
        me->add("guo_shoucheng/reward_exp", job_exp);
        me->add("guo_shoucheng/reward_potential",job_pot);  
        me->add("guo_shoucheng/reward",reward);  
        me->delete_temp("guo_jianlou");    
        me->delete_temp("guo_shoucheng"); 
        if (me->query("potential") > me->query_potential_limit()) 
             me->set("potential", me->query_potential_limit()); 
        if (me->query("experience") > me->query_experience_limit()) 
             me->set("experience", me->query_experience_limit()); 
               return "“"+RANK_D->query_respect(me)
               +"，为国杀敌，奋勇当先，当给予奖励！！”\n";
}

string ask_chetui()
{
         object me;
         me = this_player();
         if( !me->query_temp("guo_shoucheng/start_job") )
         return "你没有领任务,跑这里瞎嚷嚷什麽?";
         
      if (me->query("experience") < 100+random(20))
            return "你体会不足取消任务。";
       if (me->query("potential") < 100+random(20))
            return "你潜能不足取消任务。";           
         me->apply_condition("jobshadi_limit",0);
         me->add("combat_exp",-100+random(20));
         me->add("potential",-100+random(20));
         me->add("experience",-100+random(20));
         me->apply_condition("jobshadi_failed",6);
         me->delete_temp("guo_shoucheng");
         me->delete("guo_shoucheng/failed");
         return "没关系,下次继续努力 。不过你的经验潜能和体会降低了!";
}

