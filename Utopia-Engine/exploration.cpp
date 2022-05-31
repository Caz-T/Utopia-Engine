#include "exploration.h"
#include "ui_exploration.h"

exploration::exploration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::exploration)
{
    ui->setupUi(this);
}

exploration::~exploration()
{
    delete ui;
}
