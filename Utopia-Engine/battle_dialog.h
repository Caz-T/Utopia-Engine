#ifndef BATTLE_DIALOG_H
#define BATTLE_DIALOG_H

#include <QDialog>
#include "game_controller.h"

namespace Ui {
class battle_dialog;
}

class battle_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit battle_dialog(game_controller* gm, int rg, int lv, QWidget *parent = nullptr);
    ~battle_dialog();

private:
    Ui::battle_dialog *ui;
    game_controller* game;
    int level;
    int region;
};

#endif // BATTLE_DIALOG_H
