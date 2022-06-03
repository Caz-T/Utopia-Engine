#ifndef EXPLORATION_DIALOG_H
#define EXPLORATION_DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include "dice.h"
#include "game_controller.h"


namespace Ui {
class exploration_dialog;
}

class exploration_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit exploration_dialog(game_controller* gm, int id, QWidget *parent = nullptr);
    ~exploration_dialog();

private slots:
    void on_roll_button_clicked();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();

private:
    Ui::exploration_dialog *ui;
    game_controller* game;
    dice* d6;

    int numbers[6] = {0};
    int roll_times = 0;
    int location_id;
    int result_1, result_2;

    QLabel* blanks[6]; // 0,1,2 for upper layer, 3,4,5 for lower layer
    QPushButton* buttons[6]; // same as above

    void button_candy(int); // just a private function that deals homogeneously with button clicks

};

#endif // EXPLORATION_DIALOG_H
