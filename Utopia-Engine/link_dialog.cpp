#include "link_dialog.h"
#include "ui_link_dialog.h"

link_dialog::link_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::link_dialog)
{
    ui->setupUi(this);
}

link_dialog::~link_dialog()
{
    delete ui;
}
