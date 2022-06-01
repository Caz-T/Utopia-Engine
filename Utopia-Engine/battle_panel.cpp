#include "battle_panel.h"
#include "ui_battle_panel.h"

battle_panel::battle_panel(game_controller* gm, QWidget *parent) :
    panel(gm, parent),
    ui(new Ui::battle_panel)
{
    ui->setupUi(this);
}

battle_panel::~battle_panel()
{
    delete ui;
}

void battle_panel::refresh_panel()
{
    panel::refresh_panel();
}
