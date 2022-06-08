#ifndef BATTLE_DIALOG_H
#define BATTLE_DIALOG_H

#include <QDialog>
#include "game_controller.h"
#include "dice.h"
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

namespace Ui {
class battle_dialog;
}

// done(code): 1 = beaten but no drops, 2 = beaten and drops, -1 = unconscious or death with no drops
class battle_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit battle_dialog(game_controller* gm, int rg, int lv, QWidget *parent = nullptr);
    ~battle_dialog();

private slots:
    void on_roll_dice_clicked();

    void on_use_para_clicked();

    void on_proceed_button_clicked();

    void on_loot_roll_clicked();

private:
    Ui::battle_dialog *ui;
    game_controller* game;
    int level; // consistent with INDEX, rather than with ACTUAL LEVEL
    int region;
    int dice_modification = 0;

    int monster_atk;
    int player_atk;
    void update_hearts();

    dice* d6;
    int result_1, result_2;
    int hp_lost = 0;
};


#endif // BATTLE_DIALOG_H
