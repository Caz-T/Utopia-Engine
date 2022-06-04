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
int game_controller::location_event(int code) const {return _location_event[code];}
int game_controller::artifact_status(int code) const {return _artifact_status[code];}
bool game_controller::treasure_found(int code) const {return _treasure_found[code];}
bool game_controller::seal_of_balance_available() const {return _seal_of_balance_available;}
bool game_controller::the_ancient_record_abailable() const {return _the_ancient_record_available;}
int game_controller::link_value(int code) const {return _link_value[code];}
int game_controller::activation_energy(int code) const {return _activation_energy[code];}
int game_controller::wastebasket_slots() const {return _wastebasket_slots;}

bool game_controller::change_hp(int count)
{
    _hp += count;
    if (_hp < 0)
    {
        // IMPLEMENT death ending
        return true;
    }
    else if (_hp == 0)
    {
        // IMPLEMENT unconsciousness
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
    QFile tempsave("save.txt");
    if (!tempsave.open(QIODevice::WriteOnly | QIODevice::Text)) return false;
    QTextStream saveout(&tempsave);

    saveout << _hp << ' ' << _date << ' ' << _doomsday << ' ' << _god_hand << ' ' << _position << Qt::endl;
    for (int i = 0; i <= 5; i++) saveout << _storage[i] << ' '; saveout << Qt::endl; // intended to keep them in the same line.
    for (int i = 0; i <= 2; i++) saveout << (_tool_available[i] ? 1 : 0) << ' '; saveout << Qt::endl;
    for (int i = 0; i <= 5; i++) saveout << _expl_progress[i] << ' '; saveout << Qt::endl;
    for (int i = 0; i <= 5; i++) saveout << _location_event[i] << ' '; saveout << Qt::endl;
    for (int i = 0; i <= 5; i++) saveout << _artifact_status[i] << ' '; saveout << Qt::endl;
    for (int i = 0; i <= 5; i++) saveout << (_treasure_found[i] ? 1 : 0) << ' '; saveout << Qt::endl;
    saveout << (_seal_of_balance_available ? 1 : 0) << (_the_ancient_record_available ? 1 : 0) << Qt::endl;
    for (int i = 0; i <= 5; i++) saveout << _link_value[i] << ' '; saveout << Qt::endl;
    for (int i = 0; i <= 5; i++) saveout << _activation_energy[i] << ' '; saveout << Qt::endl;
    saveout << _wastebasket_slots << Qt::endl;

    tempsave.close();
    return true;
}
bool game_controller::load_game()
{
    //IMPLEMENT ask for load name
    QFile tempload("save.txt");
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
        for (int i = 0; i <= 5; i++) {loadin >> num; switch(num){case 1:_tool_available[i] = true; break; case 0:_tool_available[i] = false; break; default: throw 5;}}
        for (int i = 0; i <= 5; i++) {loadin >> _expl_progress[i]; if (_expl_progress[i] < 0 or _expl_progress[i] > 6) throw 6;}
        for (int i = 0; i <= 5; i++) {loadin >> _location_event[i]; if (_location_event[i] < 0 or _location_event[i] > 4) throw 7;}
        for (int i = 0; i <= 5; i++) {loadin >> _artifact_status[i]; if (_artifact_status[i] < 0 or _artifact_status[i] > 2) throw 8;}
        for (int i = 0; i <= 5; i++) {loadin >> num; switch(num){case 1:_treasure_found[i] = true; break; case 0:_treasure_found[i] = false; break; default: throw 9;}}
        loadin >> num; switch(num){case 1:_seal_of_balance_available = true; break; case 0:_seal_of_balance_available = false; break; default: throw 10;}
        loadin >> num; switch(num){case 1:_the_ancient_record_available = true; break; case 0:_the_ancient_record_available = false; break; default: throw 11;}
        for (int i = 0; i <= 5; i++) {loadin >> _link_value[i]; if (_link_value[i] < -1 or _link_value[i] > 15) throw 12;}
        for (int i = 0; i <= 5; i++) {loadin >> _activation_energy[i]; if (_activation_energy[i] < 0 or _activation_energy[i] > 4) throw 13;}
        loadin >> _wastebasket_slots; if (_wastebasket_slots < 0 or _wastebasket_slots > 10) throw 14;
    }
    catch (...)
    {
        //IMPLEMENT error message
        return false;
    }
    // IMPLEMENT success message
    return true;
}

void game_controller::use_tool(int tool_id, bool flag) {_tool_available[tool_id] = flag;}
void game_controller::use_seal_of_balance() {_seal_of_balance_available = false;}
void game_controller::use_the_ancient_record() {_the_ancient_record_available = false;}
void game_controller::day_progress()
{
    _date++;
    if (_date >= _doomsday)
    {
        //IMPLEMENT DOOMSDAY
    }
    if (_date % 3 == 2) reroll_events();
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
    else _artifact_status[id] = 2;
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
        int ret = d6->roll();
        _location_event[ret] = i;
        message += event_names_zh[i];
        message += "：";
        message += location_names_zh[ret];
        message += "\n";
    }
    QMessageBox msg;
    msg.setText(message);
    msg.exec();
}
