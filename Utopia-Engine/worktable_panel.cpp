#include "worktable_panel.h"
#include "ui_worktable_panel.h"

worktable_panel::worktable_panel(game_controller* gm, QWidget *parent) :
    panel(gm, parent),
    ui(new Ui::worktable_panel)
{
    ui->setupUi(this);


    this->hide(); // by default everything is hidden when created
}

worktable_panel::~worktable_panel()
{
    delete ui;
}

void worktable_panel::refresh_panel()
{

}
