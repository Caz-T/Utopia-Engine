#ifndef FINAL_ACTIVATION_DIALOG_H
#define FINAL_ACTIVATION_DIALOG_H

#include <QDialog>

#include "game_controller.h"
#include "dice.h"

namespace Ui {
class final_activation_dialog;
}

class final_activation_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit final_activation_dialog(game_controller* gm, QWidget *parent = nullptr);
    ~final_activation_dialog();

private slots:
    void on_roll_button_clicked();

private:
    Ui::final_activation_dialog *ui;
    game_controller* game;
    dice* d6;
    int difficulty;

    void update_hearts();
};

#endif // FINAL_ACTIVATION_DIALOG_H
