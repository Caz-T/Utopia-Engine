#include "connection_dialog.h"
#include "ui_connection_dialog.h"

connection_dialog::connection_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connection_dialog)
{
    ui->setupUi(this);
}

connection_dialog::~connection_dialog()
{
    delete ui;
}
