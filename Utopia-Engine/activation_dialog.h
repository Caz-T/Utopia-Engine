#ifndef ACTIVATION_DIALOG_H
#define ACTIVATION_DIALOG_H

#include <QDialog>
#include "game_controller.h"
#include "dice.h"

namespace Ui {
class activation_dialog;
}

class activation_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit activation_dialog(game_controller* gm, int order, QWidget *parent = nullptr);
    ~activation_dialog();

    int total_energy(); // returns the energy sum from this dialogue only

private slots:
    void on_use_focus_clicked();

private:
    Ui::activation_dialog *ui;

    int artifact_number;
    game_controller* game;
    dice* d6;
    int result_1, result_2;

    int numbers[8] = {0};
    int minus_results[4] = {0}; // 1, 2 for actual value; 0 for unset; -1 for ばつ
    bool focus_used = false;
    void update_hearts();
    void update_status();

    QLabel* number_labels[8];
    QPushButton* number_buttons[8];

    void button_candy(int button_id);

private slots:
    void on_number_button_1_clicked();
    void on_number_button_2_clicked();
    void on_number_button_3_clicked();
    void on_number_button_4_clicked();
    void on_number_button_5_clicked();
    void on_number_button_6_clicked();
    void on_number_button_7_clicked();
    void on_number_button_8_clicked();
    void on_abort_button_clicked();
    void on_roll_button_clicked();
};

#endif // ACTIVATION_DIALOG_H
