#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;

string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});
mapping *data=({
    (["name":WHT"白龙马"NOR,	"id":"bailong ma",]),
    (["name":HIR"红须马"NOR,	"id":"hongxu ma",]),
    (["name":HIG"碧血马"NOR,	"id":"bixue ma",]),
    (["name":HIM"彩云驹"NOR,	"id":"caiyun ju",]),
    (["name":HIY"梅花鹿"NOR,	"id":"meihua lu",]),
    (["name":HIW"白花马"NOR,	"id":"baihua ma",]),
    (["name":HIC"青天马"NOR,	"id":"qingtian ma",]),
    (["name":WHT"白风驹"NOR,	"id":"baifeng ju",]),
    (["name":HIR"红头马"NOR,	"id":"hongtou ma",]),
    (["name":HIG"绿毛驹"NOR,	"id":"lvmao ju",]),
    (["name":HIM"紫天驹"NOR,	"id":"zitian ju",]),
    (["name":HIY"黄龙驹"NOR,	"id":"huanglong ju",]),
    (["name":HIW"白云马"NOR,	"id":"baiyun ma",]),
    (["name":HIC"青风马"NOR,	"id":"qingfeng ma",]),
    (["name":WHT"天山白马"NOR,	"id":"bai ma",]),
    (["name":HIR"蒙古红马"NOR,	"id":"hong ma",]),
    (["name":HIG"西域小马"NOR,	"id":"xiao ma",]),
    (["name":HIM"中原宝驹"NOR,	"id":"bao ju",]),
    (["name":HIY"黄龙汗马"NOR,	"id":"han ma",]),
    (["name":HIW"白蹄马"NOR,	"id":"baiti ma",]),
    (["name":HIC"的青宝驹"NOR,	"id":"diqing baoju",]),
    (["name":WHT"白光马"NOR,	"id":"baiguang ma",]),
    (["name":HIR"红须宝驹"NOR,	"id":"hongxu baoju",]),
    (["name":HIG"东北飞马"NOR,	"id":"fei ma",]),
    (["name":HIM"紫金神驹"NOR,	"id":"zijin shenju",]),
    (["name":HIY"黄金鹿"NOR,	"id":"huangjin lu",]),
});

void create()
{
    mapping npc;
    npc = data[random(sizeof(data))];

    set_name(npc["name"],({ npc["id"] }));
    set("race", "野兽");
    set("gender", "雄性");
    set("age", 2 + random(3));
    set("long", "这是一匹宝马，日行千里，夜行八百。\n");
    set("ridable", 1);
    set("unit", "匹");
    set("value", 100000);
    set("int", 30);
    set("qi", 300);
    set("max_qi", 300);
    set("jing", 100);
    set("max_jing", 100);
    set("shen_type", 0);
    set("combat_exp", 50000);
    set("attitude", "peaceful");

    set("limbs", ({ "头部", "腹部", "尾巴","后腿","前腿" }) );
    set("verbs", ({ "bite", "hoof" }) );
    set_temp("apply/attack", 50);
    set_temp("apply/armor", 15);
    set_temp("apply/damage", 25);

    setup();
}
