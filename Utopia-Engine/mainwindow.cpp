#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    beginning();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::beginning()
{
    // IMPLEMENT the title
    ui->setupUi(this);
    ui->startButton->hide();
    ui->loadButton->hide();
    ui->quitButton->hide();
    ui->background->setPixmap(QPixmap("://StarryParadoxBackgroundPic.jpg"));
    ui->background->setWindowOpacity(0.0);
    timer = new QTimer;
    timer->singleShot(3000, this, SLOT(change_pic()));

}

void MainWindow::dim_bg()
{
    ui->background->setWindowOpacity(ui->background->windowOpacity() + 0.005);
    if (ui->background->windowOpacity() >= 1.0)
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(dim_bg()));
        delete timer;
    }
}

void MainWindow::change_pic()
{
    ui->background->setPixmap(QPixmap("://MainwindowBackground.jpg"));
    ui->startButton->show();
    ui->loadButton->show();
    ui->quitButton->show();
}

void MainWindow::switch_panel(int panel_code, panel* sender)
{
    if (sender != nullptr) sender->close_panel();
    switch(panel_code)
    {
    case 0:
        return_to_menu();
        break;
    case 1:
        exploration->refresh_panel();
        break;
    case 2:
        worktable->refresh_panel();
        break;
    }
}

void MainWindow::on_startButton_clicked()
{
    game = new game_controller(this);
    worktable = new worktable_panel(game, this);
    exploration = new exploration_panel(game, this);
    connect(worktable, SIGNAL(switch_panel_signal(int,panel*)), this, SLOT(switch_panel(int,panel*)));
    connect(exploration, SIGNAL(switch_panel_signal(int,panel*)), this, SLOT(switch_panel(int,panel*)));

    worktable->close_panel();
    exploration->close_panel();

    hide_main_window();
    switch_panel(1);
}


void MainWindow::on_loadButton_clicked()
{
    game = new game_controller(this);
    if (!game->load_game())
    {
        delete game;
        on_startButton_clicked();
        return;
    }
    worktable = new worktable_panel(game, this);
    exploration = new exploration_panel(game, this);

    worktable->close_panel();
    exploration->close_panel();

    hide_main_window();
    switch_panel(1);
}

void MainWindow::hide_main_window()
{
    ui->background->hide();
    ui->loadButton->hide();
    ui->quitButton->hide();
    ui->startButton->hide();
}
void MainWindow::return_to_menu()
{
    delete game;
    delete exploration;
    delete worktable;
    ui->setupUi(this);
}
