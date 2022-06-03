#include "battle_dialog.h"
#include "ui_battle_dialog.h"

battle_dialog::battle_dialog(game_controller* gm, int rg, int lv, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::battle_dialog),
    game(gm),
    level(lv),
    region(rg)
{
    ui->setupUi(this);
}

battle_dialog::~battle_dialog()
{
    delete ui;
}
