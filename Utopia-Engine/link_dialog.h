#ifndef LINK_DIALOG_H
#define LINK_DIALOG_H

#include <QDialog>
#include "game_controller.h"
#include "dice.h"

namespace Ui {
class link_dialog;
}

class link_dialog : public QDialog
{
    Q_OBJECT


public:
    explicit link_dialog(game_controller* gm, int link_id, QWidget *parent = nullptr);
    ~link_dialog();

private slots:
    void on_roll_button_clicked();

    void on_quit_button_clicked();

    void on_discard_button_clicked();

    void on_place_button_1_clicked();
    void on_place_button_2_clicked();
    void on_place_button_3_clicked();
    void on_place_button_4_clicked();
    void on_place_button_5_clicked();
    void on_place_button_6_clicked();

private:
    Ui::link_dialog *ui;

    int link_number;
    game_controller* game;
    dice* d6;
    int result_1, result_2;

    int minus_results[3] = {-1, -1, -1}; // -1 for unset

    QLabel* number_labels[6];
    QPushButton* number_buttons[6];
    QLabel* result_labels[3];

    void update_status();
    void button_candy(int);


};

#endif // LINK_DIALOG_H
