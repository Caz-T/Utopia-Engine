#include "battle_dialog.h"
#include "ui_battle_dialog.h"

battle_dialog::battle_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::battle_dialog)
{
    ui->setupUi(this);
}

battle_dialog::~battle_dialog()
{
    delete ui;
}
