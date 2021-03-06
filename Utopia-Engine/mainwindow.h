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


    void beginning(); // the setup process
    void hide_main_window(); // hides all components in main window, but leaves the window itself open
    void return_to_menu(); // shows all components and destroys all others

public slots:
    void switch_panel(int panel_code, panel* sender = nullptr);
    /* allows child panels to switch to other panels. Sender is the panel to be hidden.
     * current codes:
     * 0: main window(quit)
     * 1: exploration
     * 2: worktable
     */


private slots:
    void dim_bg();
    void change_pic();

    void on_start_button_clicked();
    void on_load_button_clicked();

    void on_quit_button_clicked();

public slots:
    void game_end(QString, QString);

};
#endif // MAINWINDOW_H
