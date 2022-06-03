#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <QObject>

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


    // getters
    // each XXX() returns the value of _XXX
    int hp() const;
    int date() const;
    int doomsday() const;
    int god_hand() const;
    int position() const;
    int storage(int code) const;
    bool tool_available(int code) const;
    int expl_progress(int code) const;
    int location_event(int code) const;
    int artifact_status(int code) const;
    bool treasure_found(int code) const;
    bool seal_of_balance_available() const;
    bool the_ancient_record_abailable() const;
    int link_value(int code) const;
    int activation_energy(int code) const;
    int wastebasket_slots() const;

    // some setters, each completing its own logic
    void change_hp(int count);

    // usage of one-time stuff. for tools, setting flag to true means recharging it.
    void use_tool(int tool_id, bool flag = false);
    void use_seal_of_balance();
    void use_the_ancient_record();

public slots:
    // Save & Load
    bool save_game(); // This saves all the data. True indicates a successful save. Data are stored in the same order as in declaration.
    bool load_game(); // reads in all data. True indicates a successful load. Booleans are saved in 0/1 format.




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
    int _hp = 6;
    int _date = 0, _doomsday = 15; // current date and doomsday count. When _date >= _doomsday, the game ends.
    int _god_hand = 0; // the remaining energy in god's hand
    int _position = 0; // current position. 0: exploration, 1: worktable

    // backpack
    int _storage[6] = {0}; // quantity of things in backpack.
    bool _tool_available[3] = {true, true, true}; // true means the tool can be used. 0: focus charm, 1: dowsing rod, 2: paralysis wand

    // exploration
    int _expl_progress[6] = {0}; // progress of exploration.
    int _location_event[6] = {0}; // event at each location. 0: null, 1: active monster, 2: fleeting vision, 3: good fortune, 4: foul weather
    int _artifact_status[6] = {0}; // 0: not found, 1: found, 2: activated
    bool _treasure_found[6] = {false}; // whether treasures are found
    bool _seal_of_balance_available = false; // remember to set this to true when acquiring seal of balance.
    bool _the_ancient_record_available = false; // same as above

    // worktable
    int _link_value[6] = {-1, -1, -1, -1, -1, -1}; // order is the same as components, -1 means not yet linked
    int _activation_energy[6] = {0}; // the energy in activation slots
    int _wastebasket_slots = 10; // remaining boxes in the wastebasket



    // data part ended












signals:

};

#endif // GAME_CONTROLLER_H
