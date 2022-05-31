#include "exploration_dialog.h"
#include "ui_exploration_dialog.h"

exploration_dialog::exploration_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::exploration_dialog)
{
    ui->setupUi(this);
}

exploration_dialog::~exploration_dialog()
{
    delete ui;
}
