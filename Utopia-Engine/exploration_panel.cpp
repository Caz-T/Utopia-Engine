#include "exploration_panel.h"
#include "ui_exploration_panel.h"

exploration_panel::exploration_panel(QWidget *parent) :
    panel(parent),
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

}
