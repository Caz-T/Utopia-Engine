#include "worktable.h"
#include "ui_worktable.h"

worktable::worktable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::worktable)
{
    ui->setupUi(this);
}

worktable::~worktable()
{
    delete ui;
}
