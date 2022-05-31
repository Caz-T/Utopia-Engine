#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <QObject>
#include "panel.h"

class game_controller : public QObject
{
    Q_OBJECT
public:
    explicit game_controller(QObject *parent = nullptr);



public:
    // constants

    // combat: the following stores the upper limits for monsters' attacks, and the lower limits for players' attacks.
    // note that these all have the const modifier, so further alternations are done in-place by exploration_dialog.
    constexpr static const int monster_attack[5] = {1, 1, 2, 3, 4};
    constexpr static const int player_attack[5] = {5, 6, 6, 6, 6};



private:

    /* these are all the game's data.
     *
     * if not specified, the order are as follows:
     * Locations: Halebeard peak, the great wilds, root-strangled marshes, glassrock canyon, ruined city of the ancients, the fiery maw
     * Components: silver, quartz, gum, silica, wax, lead (same as locations)
     * Artifacts: (same as locations)
     * Tool belt: focus charn, dowsing rod, paralysis wand
     * Events: active monsters, fleeting visions, good fortune, foul weather.
     *
     */


    // global
    int _hitpoint = 6;
    int _date = 0, _doomsday = 15; // current date and doomsday count. When _date >= _doomsday, the game ends.
    int _god_hand = 0; // the remaining energy in god's hand

    // backpack
    int _storage[6] = {0}; // quantity of things in backpack.
    bool _tool_available[3] = {true, true, true}; // true means the tool can be used.

    // exploration
    int _expl_progress[6] = {0}; // progress of exploration.
    int _location_event[6] = {0}; // event at each location.
    int _artifact_status[6] = {0}; // 0: not found, 1: found, 2: activated
    bool _treasure_found[6] = {false}; // whether treasures are found
    bool _seal_of_balance_available = false; // remember to set this to true when acquiring seal of balance.
    bool _the_ancient_record_availabel = false; // same as above

    // worktable
    bool _linked[6] = {false}; // order is the same as components
    int _link_value = {0}; // same as above
    int _activation_energy = {0}; // the energy in activation slots
    int _wastebasket_slots = 10; // remaining boxes in the wastebasket









signals:

};

#endif // GAME_CONTROLLER_H
