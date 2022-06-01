#include "backpack_panel.h"
#include "ui_backpack_panel.h"

backpack_panel::backpack_panel(game_controller* gm, QWidget *parent) :
    panel(gm, parent),
    ui(new Ui::backpack_panel)
{
    ui->setupUi(this);
}

backpack_panel::~backpack_panel()
{
    delete ui;
}

void backpack_panel::refresh_panel()
{
    panel::refresh_panel();
}
