#ifndef RECHARGE_TOOL_DIALOG_H
#define RECHARGE_TOOL_DIALOG_H

#include "game_controller.h"
#include <QDialog>
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class recharge_tool_dialog;
}

class recharge_tool_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit recharge_tool_dialog(game_controller* gm, QWidget *parent = nullptr);
    ~recharge_tool_dialog();

private slots:
    void on_cancel_button_clicked();

    void on_confirm_button_1_clicked();
    void on_confirm_button_2_clicked();
    void on_confirm_button_3_clicked();

    void on_choice_button_1_clicked();
    void on_choice_button_2_clicked();
    void on_choice_button_3_clicked();
    void on_choice_button_4_clicked();
    void on_choice_button_5_clicked();
    void on_choice_button_6_clicked();

private:
    Ui::recharge_tool_dialog *ui;
    game_controller* game;

    int chosen = 0;
    int chosen_comp[3] = {-1, -1, -1};
    int chosen_times[6] = {0};

    void button_candy(int code);
    void confirm_candy(int code);
};

#endif // RECHARGE_TOOL_DIALOG_H
