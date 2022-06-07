#include "game_controller.h"
#include "QtWidgets/qwidget.h"
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include "dice.h"

game_controller::game_controller(QObject *parent)
    : QObject{parent}
{

}

int game_controller::hp() const {return _hp;}
int game_controller::date() const {return _date;}
int game_controller::doomsday() const {return _doomsday;}
int game_controller::god_hand() const {return _god_hand;}
int game_controller::position() const {return _position;}
int game_controller::storage(int code) const {return _storage[code];}
bool game_controller::tool_available(int code) const {return _tool_available[code];}
int game_controller::expl_progress(int code) const {return _expl_progress[code];}
int game_controller::event_location(int code) const {return _event_location[code];}
int game_controller::artifact_status(int code) const {return _artifact_status[code];}
bool game_controller::treasure_found(int code) const {return _treasure_found[code];}
bool game_controller::seal_of_balance_available() const {return _seal_of_balance_available;}
bool game_controller::the_ancient_record_abailable() const {return _the_ancient_record_available;}
int game_controller::link_value(int code) const {return _link_value[code];}
int game_controller::link_number(int link_id, int order) const {return _link_numbers[link_id][order];}
int game_controller::activation_energy(int code) const {return _activation_energy[code];}
int game_controller::activation_attempt(int code) const {return _activation_attempt[code];}
int game_controller::wastebasket_slots() const {return _wastebasket_slots;}

bool game_controller::change_hp(int count)
{
    _hp += count;
    if (_hp < 0)
    {
        emit game_end("你死了", "你于对抗末日的旅程中长眠。\n"
                      "末日将至的世界险象环生，你很走运，至少活到了现在。\n"
                      "你的死同时意味着这个世界再无生还可能。\n"
                      "你向世界致以最后的晚安。");
        return true;
    }
    else if (_hp == 0)
    {
        recover_from_unconsciousness();
        return true;
    }
    else if (_hp > 6)
    {
        _hp = 6;
    }
    return false;
}

bool game_controller::save_game()
{
    // IMPLEMENT ask for savename
    QFile tempsave("/Users/casorazitora/Desktop/save.txt");
    if (!tempsave.open(QIODevice::WriteOnly | QIODevice::Text)) return false;
    QTextStream saveout(&tempsave);

    saveout << _hp << ' ' << _date << ' ' << _doomsday << ' ' << _god_hand << ' ' << _position << Qt::endl;
    for (int i = 0; i <= 5; i++) saveout << _storage[i] << ' '; saveout << Qt::endl; // intended to keep them in the same line.
    for (int i = 0; i <= 2; i++) saveout << (_tool_available[i] ? 1 : 0) << ' '; saveout << Qt::endl;
    for (int i = 0; i <= 5; i++) saveout << _expl_progress[i] << ' '; saveout << Qt::endl;
    for (int i = 0; i <= 3; i++) saveout << _event_location[i] << ' '; saveout << Qt::endl;
    for (int i = 0; i <= 5; i++) saveout << _artifact_status[i] << ' '; saveout << Qt::endl;
    for (int i = 0; i <= 5; i++) saveout << (_treasure_found[i] ? 1 : 0) << ' '; saveout << Qt::endl;
    saveout << (_seal_of_balance_available ? 1 : 0) << ' ' << (_the_ancient_record_available ? 1 : 0) << Qt::endl;
    for (int i = 0; i <= 5; i++) saveout << _link_value[i] << ' '; saveout << Qt::endl;
    for (int i = 0; i <= 5; i++) for (int j = 0; j <= 5; j++) saveout << _link_numbers[i][j] << ' '; saveout << Qt::endl;
    for (int i = 0; i <= 5; i++) saveout << _activation_energy[i] << ' '; saveout << Qt::endl;
    for (int i = 0; i <= 5; i++) saveout << _activation_attempt[i] << ' '; saveout << Qt::endl;
    saveout << _wastebasket_slots << Qt::endl;

    tempsave.close();
    return true;
}
bool game_controller::load_game()
{
    //IMPLEMENT ask for load name
    QFile tempload("/Users/casorazitora/Desktop/save.txt");
    if (!tempload.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
    QTextStream loadin(&tempload);
    int num;

    try
    {
        loadin >> _hp; if (_hp > 6 or _hp < 0) throw 1;
        loadin >> _date >> _doomsday; if (_date >= _doomsday or _date < 0 or _doomsday > 22) throw 2;
        loadin >> _god_hand; if (_god_hand < 0 or _god_hand > 6) throw 3;
        loadin >> _position; if (_position < 0 or _position > 2) throw 15;
        for (int i = 0; i <= 5; i++) {loadin >> _storage[i]; if (_storage[i] < 0 or _storage[i] > 4) throw 4;}
        for (int i = 0; i <= 2; i++) {loadin >> num; switch(num){case 1:_tool_available[i] = true; break; case 0:_tool_available[i] = false; break; default: throw 5;}}
        for (int i = 0; i <= 5; i++) {loadin >> _expl_progress[i]; if (_expl_progress[i] < 0 or _expl_progress[i] > 6) throw 6;}
        for (int i = 0; i <= 3; i++) {loadin >> _event_location[i]; if (_event_location[i] < -1 or _event_location[i] > 5) throw 7;}
        for (int i = 0; i <= 5; i++) {loadin >> _artifact_status[i]; if (_artifact_status[i] < 0 or _artifact_status[i] > 2) throw 8;}
        for (int i = 0; i <= 5; i++) {loadin >> num; switch(num){case 1:_treasure_found[i] = true; break; case 0:_treasure_found[i] = false; break; default: throw 9;}}
        loadin >> num; switch(num){case 1:_seal_of_balance_available = true; break; case 0:_seal_of_balance_available = false; break; default: throw 10;}
        loadin >> num; switch(num){case 1:_the_ancient_record_available = true; break; case 0:_the_ancient_record_available = false; break; default: throw 11;}
        for (int i = 0; i <= 5; i++) {loadin >> _link_value[i]; if (_link_value[i] < -1 or _link_value[i] > 15) throw 12;}
        for (int i = 0; i <= 5; i++)
            for (int j = 0; j <= 5; j++)
                {loadin >> _link_numbers[i][j]; if (_link_numbers[i][j] < 0 or _link_numbers[i][j] > 6) throw 17;}
        for (int i = 0; i <= 5; i++) {loadin >> _activation_energy[i]; if (_activation_energy[i] < 0 or _activation_energy[i] > 4) throw 13;}
        for (int i = 0; i <= 5; i++) {loadin >> _activation_attempt[i]; if (_activation_attempt[i] < 0 or _activation_energy[i] > 2) throw 16;}
        loadin >> _wastebasket_slots; if (_wastebasket_slots < 0 or _wastebasket_slots > 10) throw 14;
    }
    catch (int error_code)
    {
        QMessageBox msg;
        msg.setWindowTitle("存档读取错误");
        msg.setText(QString("读取存档时发生错误，错误代码：") + QString::number(error_code) + QString("。是否重试，或直接开始新游戏？"));
        msg.addButton("开始新游戏", QMessageBox::AcceptRole);
        msg.addButton("重试", QMessageBox::RejectRole);
        if (msg.exec() == QMessageBox::Accepted) load_game(); // IMPLEMENT fix this strange thing.
        else return false;
    }
    QMessageBox msg;
    msg.setWindowTitle("存档读取成功");
    msg.setText("存档读取成功！");
    return true;
}

void game_controller::use_tool(int tool_id, bool flag) {_tool_available[tool_id] = flag;}
void game_controller::use_seal_of_balance(int loc)
{
    _seal_of_balance_available = false;
    for (int i = 0; i < 4; i++)
        if (_event_location[i] == loc)
            _event_location[i] = -1;
}
void game_controller::use_the_ancient_record() {_the_ancient_record_available = false;}
void game_controller::day_progress(int count)
{
    bool flag = false;
    if (_treasure_found[3]) change_hp(1);
    while (count--)
    {
        _date++;
        if (_date % 3 == 2) flag = true;
        if (_date >= _doomsday)
        {
            emit game_end("末日降临", "一切归于尘土。\n"
                          "尽管你夜以继日地搜寻组件、组装乌托邦引擎，你仍然没能从注定的末日中救下这个世界。\n"
                          "\"空想之根落下。最后的希望存于虚空之中。\"");
            break;
        }
    }
    if (flag) reroll_events();
}
void game_controller::charge_god_hand(int increment)
{
    _god_hand += increment;
    if (_god_hand > 6) _god_hand = 6;
    while (_god_hand >= 3 and _doomsday < 22)
    {
        _god_hand -= 3;
        _doomsday ++;
    }
}
void game_controller::find_component(int id) {if (_storage[id] < 4) _storage[id] ++;}
void game_controller::find_artifact(int id)
{
    if (_artifact_status[id] != 0) qDebug() << "artifact status exception! artifact code: " << id << " status: " << _artifact_status[id];
    else _artifact_status[id] = 1;

}
void game_controller::activate_artifact(int id)
{
    if (_artifact_status[id] != 1) qDebug() << "artifact status exception! artifact code: " << id << " status: " << _artifact_status[id];
    else
    {
        if (id == 0) _seal_of_balance_available = true;
        _artifact_status[id] = 2;
    }
}
void game_controller::proceed_exploration(int id)
{
    const int day_prog_checkpoint[6][4] =
    {
        {0, 1, 3, -1},
        {0, 3, -1, -1},
        {0, 2, 4, -1},
        {0, 1, 3, -1},
        {0, 2, 4, -1},
        {0, 1, 2, 4}
    };
    for (int i = 0; i < 4; i++)
        if (_expl_progress[id] == day_prog_checkpoint[id][i])
            day_progress();
    if (_expl_progress[id] < 5) _expl_progress[id]++;
    else _expl_progress[id] = 0;
}
void game_controller::reroll_events()
{
    dice* d6= new dice;
    QString message = "事件重置了！新的事件为：\n";
    for (int i = 0; i < 4; i++)
    {
        int ret = d6->roll() - 1;
        _event_location[i] = ret;
        message += event_names_zh[i+1];
        message += "：";
        message += location_names_zh[ret];
        message += "\n";
    }
    QMessageBox msg;
    msg.setText(message);
    msg.exec();
}
void game_controller::find_treasure(int id)
{
    _treasure_found[id] = true;
    if (id == 4) _the_ancient_record_available = true;
}
void game_controller::add_link_value(int id, int increment)
{
    _link_value[id] += increment;
}
void game_controller::clean_exploration_progress()
{
    for (int i = 0; i < 6; i++) _expl_progress[i] = 0;
}
void game_controller::rest(int days, bool is_at_worktable)
{
    for (int i = 0; i < days; i++) day_progress();
    change_hp(days + (is_at_worktable and days >= 3 ? 1 : 0));
}
void game_controller::recover_from_unconsciousness()
{
    _hp = 6;
    if (_artifact_status[2] == 2) day_progress(4);
    else day_progress(6);
    QMessageBox msg;
    msg.setWindowTitle("你逐渐恢复意识...");
    msg.setText(QString("眼前一黑，你昏迷了。\n应急医疗系统把你传送回了工作室，") + QString::number(_artifact_status[2] == 2 ? 4 : 6) + QString("天后你才醒来。\n继续工作吧，末日不会等你太久。"));
    msg.exec();
}
void game_controller::increase_activate_attempt(int id) {_activation_attempt[id] ++;}
void game_controller::set_link_number(int link_id, int order, int number)
{
    _link_numbers[link_id][order] = number;
}
void game_controller::dump_dice() {_wastebasket_slots--;}
void game_controller::use_component(int id) {_storage[id]--;}
void game_controller::increase_activate_energy(int id, int increment)
{
    _activation_energy[id] += increment;
    if (_event_location[1] == id) // fleeting visions
    {
        if (_activation_energy[id] > 3)
        {
            activate_artifact(id);
            charge_god_hand(_activation_energy[id] - 3);
            _activation_energy[id] = 3;
        }
    }
    else
    {
        if (_activation_energy[id] > 4)
        {
            activate_artifact(id);
            charge_god_hand(_activation_energy[id] - 4);
            _activation_energy[id] = 4;
        }
    }
}
