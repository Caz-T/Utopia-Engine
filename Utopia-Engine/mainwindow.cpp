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
    ui->setupUi(this);
    ui->start_button->hide();
    ui->load_button->hide();
    ui->quit_button->hide();
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
    ui->start_button->show();
    ui->load_button->show();
    ui->quit_button->show();
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
        setStyleSheet("#MainWindow {background-image: url(://explore_bg)}");
        break;
    case 2:
        worktable->refresh_panel();
        setStyleSheet("#MainWindow {background-image: url(://worktable_bg)}");
        break;
    }
}

void MainWindow::on_start_button_clicked()
{
    game = new game_controller(this);
    worktable = new worktable_panel(game, this);
    exploration = new exploration_panel(game, this);
    connect(worktable, SIGNAL(switch_panel_signal(int,panel*)), this, SLOT(switch_panel(int,panel*)));
    connect(exploration, SIGNAL(switch_panel_signal(int,panel*)), this, SLOT(switch_panel(int,panel*)));
    connect(game, SIGNAL(game_end(QString,QString)), this, SLOT(game_end(QString,QString)));

    worktable->close_panel();
    exploration->close_panel();

    hide_main_window();
    switch_panel(1);
}


void MainWindow::on_load_button_clicked()
{
    game = new game_controller(this);
    if (!game->load_game())
    {
        delete game;
        QMessageBox msg;
        msg.setText("存档读取失败，将开始新游戏。");
        msg.setWindowTitle("存档读取失败");
        msg.exec();
        on_start_button_clicked();
        return;
    }
    worktable = new worktable_panel(game, this);
    exploration = new exploration_panel(game, this);
    connect(worktable, SIGNAL(switch_panel_signal(int,panel*)), this, SLOT(switch_panel(int,panel*)));
    connect(exploration, SIGNAL(switch_panel_signal(int,panel*)), this, SLOT(switch_panel(int,panel*)));
    connect(game, SIGNAL(game_end(QString,QString)), this, SLOT(game_end(QString,QString)));

    worktable->close_panel();
    exploration->close_panel();

    hide_main_window();
    switch_panel(1);
}

void MainWindow::hide_main_window()
{
    ui->background->hide();
    ui->load_button->hide();
    ui->quit_button->hide();
    ui->start_button->hide();
}
void MainWindow::return_to_menu()
{
    delete game;

    close();
}
void MainWindow::game_end(QString title, QString explanation)
{
    QMessageBox msg;
    msg.setWindowTitle(title);
    msg.setText(explanation);
    msg.exec();

    return_to_menu();
}

void MainWindow::on_quit_button_clicked()
{
    close();
}

