#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    game = new game_controller(this);
    worktable = new worktable_panel(this);
    exploration = new exploration_panel(this);
    backpack = new backpack_panel(this);



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
        // IMPLEMENT return to main
        break;
    case 1:
        exploration->refresh_panel();
        break;
    case 2:
        worktable->refresh_panel();
        break;
    case 3:
        backpack->refresh_panel();
        break;

    }
}
