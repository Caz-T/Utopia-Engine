#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

const QString location_names_zh[6] = {
    "苍髯群峰", "无垠原野", "根脉泥沼", "晶岩峡谷", "堕落古城", "熔岩石窟"
};
const QString artifact_names_zh[6] = {
    "平衡封印", "隐士之镜", "虚空界门", "黄金罗盘", "预示棱镜", "晶簇电池"
};
const QString treasure_names_zh[6] = {
    "玄冰胸甲", "雷神之锤", "烁影月链", "虬龙鳞甲", "古迹手札", "熔融晶片"
};
const QString tool_names_zh[3] = {
    "聚焦光束", "探测手杖", "瘫痪魔杖"
};
const QString component_names_zh[6] = {
    "白银", "石英", "树脂", "硅晶", "石蜡", "铅矿"
};
const QString monster_names_zh[6][5] = { // remember here the order is 1 less than encounter level
    {"冰熊", "漫游强盗", "血狼", "食马巨鹰", "残心巨人"},
    {"盗贼", "鸦群", "角背野牛", "覆草巨魔", "雷霆王"},
    {"珠鳞蟒", "远古巨鳄", "陆生鲨", "深渊血蛭", "巨潮宿物"},
    {"烦躁地精", "晶翼飞龙", "蔽天恶爪", "可怖虬龙", "无尽虬龙"},
    {"盗墓者", "魂灯", "复仇阴魂", "噩梦蟹", "不可名"},
    {"小恶魔", "反抗术士", "巨炎蜥", "火花元素", "火山之魂"}
};
const bool is_spirit_monster[6][5] = {
    {false, false, false, false, true},
    {false, false, false, false, false},
    {false, false, false, true, false},
    {false, false, true, false, true},
    {false, true, true, false, false},
    {false, false, false, true, true}
};

// combat: the following stores the upper limits for monsters' attacks, and the lower limits for players' attacks.
// note that all further alternations are done in-place by exploration_dialog.
const int monster_attack[5] = {1, 1, 2, 3, 4};
const int player_attack[5] = {5, 6, 6, 6, 6};
const QString event_names_zh[5] = {
    "", "活跃怪物", "幻梦预视", "好运气", "恶劣天气"
};//^^ notice this empty string!!
/*
const QString mdsah[6] = {
        "", "", "", "", "", ""
}; // IMPLEMENT remove this: just a template
*/

#endif // CONSTANTS_H
