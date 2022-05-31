#include "exploration_panel.h"
#include "ui_exploration_panel.h"

exploration_panel::exploration_panel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::exploration_panel)
{
    ui->setupUi(this);
}

exploration_panel::~exploration_panel()
{
    delete ui;
}
