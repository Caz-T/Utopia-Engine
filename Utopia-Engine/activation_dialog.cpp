#include "activation_dialog.h"
#include "ui_activation_dialog.h"

activation_dialog::activation_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::activation_dialog)
{
    ui->setupUi(this);
}

activation_dialog::~activation_dialog()
{
    delete ui;
}
