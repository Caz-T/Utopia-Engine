#include "game_controller.h"
#include "QtWidgets/qwidget.h"
#include <QDebug>

game_controller::game_controller(QObject *parent)
    : QObject{parent}
{

}

int game_controller::hp() const {return _hp;}
int game_controller::date() const {return _date;}
int game_controller::doomsday() const {return _doomsday;}
int game_controller::god_hand() const {return _god_hand;}
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

void game_controller::change_hp(int count)
{
    _hp += count;
    if (_hp < 0)
    {
        // IMPLEMENT death ending
    }
    else if (_hp == 0)
    {
        // IMPLEMENT unconsciousness
    }
    else if (_hp > 6)
    {
        _hp = 6;
    }
}
