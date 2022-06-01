#include "exploration_panel.h"
#include "ui_exploration_panel.h"
#include <QDebug>

exploration_panel::exploration_panel(game_controller* gm, QWidget *parent) :
    panel(gm, parent),
    ui(new Ui::exploration_panel)
{
    ui->setupUi(this);

    this->hide();
}

exploration_panel::~exploration_panel()
{
    delete ui;
}

void exploration_panel::refresh_panel()
{
    this->show();
}
