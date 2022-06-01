#include "exploration_panel.h"
#include "ui_exploration_panel.h"
#include <QDebug>

exploration_panel::exploration_panel(game_controller* gm, QWidget *parent) :
    panel(gm, parent),
    ui(new Ui::exploration_panel)
{
    ui->setupUi(this);
    this->hide();
}

exploration_panel::~exploration_panel()
{
    delete ui;
}

void exploration_panel::refresh_panel()
{
    int i;

    // show hitpoints
    QLabel* hearts[6] = {ui->heart_1, ui->heart_2, ui->heart_3, ui->heart_4, ui->heart_5, ui->heart_6};
    for (i = 0; i < game->hp(); i++) hearts[i]->setPixmap(QPixmap(":/full_heart"));
    for (; i < 6; i++) hearts[i]->setPixmap(QPixmap(":/empty_heart"));

    // show calendar-related stuff
    ui->calendar_bar_upper->setValue(game->date() > 11 ? 11 : game->date());
    ui->calendar_bar_lower->setValue(game->date() > 11 ? game->date() - 11 : 0);
    QLabel* skulls[8] = {ui->skull_1, ui->skull_2, ui->skull_3, ui->skull_4, ui->skull_5, ui->skull_6, ui->skull_7, ui->skull_8};
    for (i = 15; i < game->doomsday(); i++) skulls[i - 15]->setPixmap(QPixmap("://skull_crossed"));
    for (; i <= 22; i++) skulls[i - 15]->setPixmap(QPixmap(":/skull"));
    ui->days_left->display((int) game->doomsday() - game->date());

    // show artifacts and stuff
    QLCDNumber* components[6] = {ui->compo_count_1, ui->compo_count_2, ui->compo_count_3, ui->compo_count_4, ui->compo_count_5, ui->compo_count_6 };
    for (i = 0; i < 6; i++) components[i]->display(game->storage(i));
    // IMPLEMENT artifacts and treasures

    // show exploration status
    QProgressBar* prog[6] = {ui->peak_bar, ui->peak_bar_2, ui->peak_bar_3, ui->peak_bar_4, ui->peak_bar_5, ui->peak_bar_6};
    for (i = 0; i < 6; i++) prog[i]->setValue(game->expl_progress(i));



    panel::refresh_panel();
}
