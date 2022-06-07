#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <QObject>
#include "constants.h"

class game_controller : public QObject
{
    Q_OBJECT
public:
    explicit game_controller(QObject *parent = nullptr);

public:
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
    int event_location(int code) const;
    int artifact_status(int code) const;
    bool treasure_found(int code) const;
    bool seal_of_balance_available() const;
    bool the_ancient_record_abailable() const;
    int link_value(int code) const;
    int link_number(int link_id, int order) const;
    int activation_energy(int code) const;
    int activation_attempt(int id) const;
    int wastebasket_slots() const;


    // some setters, each completing its own logic
    bool change_hp(int count, bool quit_on_coma = true); // default = false. True means character unconscious. if character dies, this function just kills the game
    void charge_god_hand(int increment);
    void rest(int days, bool is_at_worktable);
    void day_progress(int count = 1);


    // exploration-related
    void find_component(int id);
    void find_artifact(int id);
    void find_treasure(int id);
    void proceed_exploration(int id);
    void clean_exploration_progress();

    // worktable-related
    void activate_artifact(int id);
    void increase_activate_attempt(int id);
    void increase_activate_energy(int id, int increment);
    void add_link_value(int id, int increment);
    void set_link_number(int link_id, int order, int number);
    void dump_dice();
    void use_component(int id);


    // usage of one-time stuff. for tools, setting flag to true means recharging it.
    void use_tool(int tool_id, bool flag = false);
    void use_seal_of_balance(int loc);
    void use_the_ancient_record();

    void succeed();


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
    int _event_location[4] = {-1, -1, -1, -1}; // location of each event. 0: active monster, 1: fleeting vision, 2: good fortune, 3: foul weather
    int _artifact_status[6] = {0}; // 0: not found, 1: found, 2: activated
    bool _treasure_found[6] = {false}; // whether treasures are found
    bool _seal_of_balance_available = false; // remember to set this to true when acquiring seal of balance.
    bool _the_ancient_record_available = false; // same as above

    // worktable
    int _link_value[6] = {-1, -1, -1, -1, -1, -1}; // order is the same as components, -1 means not yet linked
    int _link_numbers[6][6] = {
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0}
    };
    int _activation_energy[6] = {0}; // the energy in activation slots
    int _activation_attempt[6] = {0}; // attempts to activate the artifact
    int _wastebasket_slots = 10; // remaining boxes in the wastebasket

    // data part ended

    // private setters:
    void reroll_events();
    void recover_from_unconsciousness();

signals:
    int game_end(QString title, QString explanation); // passes a string to MainWindow's slot
};

#endif // GAME_CONTROLLER_H
