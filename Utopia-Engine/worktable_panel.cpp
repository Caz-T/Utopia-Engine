#include "worktable_panel.h"
#include "ui_worktable_panel.h"

worktable_panel::worktable_panel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::worktable_panel)
{
    ui->setupUi(this);
}

worktable_panel::~worktable_panel()
{
    delete ui;
}
