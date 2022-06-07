#include "final_activation_dialog.h"
#include "ui_final_activation_dialog.h"

#include <QMessageBox>
#include <QInputDialog>
final_activation_dialog::final_activation_dialog(game_controller* gm, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::final_activation_dialog),
    game(gm),
    d6(new dice(this))
{
    ui->setupUi(this);
    setWindowTitle("世界的曙光仅有一步之遥...");
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    QInputDialog dlg(this);
    dlg.setInputMode(QInputDialog::InputMode::IntInput);
    dlg.setIntMaximum(game->hp());
    dlg.setIntMinimum(0);
    int ans = 0;
    for (int i = 0; i < 6; i++) ans += game->link_value(i);
    dlg.setLabelText(QString("你希望消耗多少生命来降低最终激活难度？\n（你不会因为生命值到零而昏迷。）\n目前的最终激活难度是：") + QString::number(ans));
    dlg.setWindowTitle("世界的曙光仅有一步之遥...");
    dlg.setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    dlg.exec();

    difficulty = ans - dlg.intValue();
    ui->difficulty_label->setText(QString("最终激活难度：") + QString::number(difficulty));
}

final_activation_dialog::~final_activation_dialog()
{
    delete ui;
}

void final_activation_dialog::update_hearts()
{
    QLabel* hearts[6] = {ui->heart_1, ui->heart_2, ui->heart_3, ui->heart_4, ui->heart_5, ui->heart_6};
    for (auto& label : hearts) label->setScaledContents(true);
    int i;
    for (i = 0; i < game->hp(); i++) hearts[i]->setPixmap(QPixmap(":/full_heart"));
    for (; i < 6; i++) hearts[i]->setPixmap(QPixmap(":/empty_heart"));
}


void final_activation_dialog::on_roll_button_clicked()
{
    int result_1 = d6->roll();
    int result_2 = d6->roll();
    dice::show_dice_result(ui->die_result_1, result_1);
    dice::show_dice_result(ui->die_result_2, result_2);
    if (result_1 + result_2 >= difficulty)
    {
        game->succeed();
        accept();
        // 愿近日所有的苦痛都如此这般化为苦涩而快乐的结晶。
    }
    else game->change_hp(-1, false);
}

