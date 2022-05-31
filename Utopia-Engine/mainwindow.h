#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// This is the main entrance to the whole project.

#include <QMainWindow>
#include <QTimer>


#include "game_controller.h"
#include "exploration_panel.h"
#include "worktable_panel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    game_controller* game;

    //MainWindow saves all ui interfaces
    exploration_panel* exploration;
    worktable_panel* worktable;

    // a public timer
    QTimer* timer;

    // the setup process
    void beginning();

private slots:
    void dim_bg();
    void change_pic();
};
#endif // MAINWINDOW_H
