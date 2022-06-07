#include "link_dialog.h"
#include "ui_link_dialog.h"
#include <QMessageBox>


link_dialog::link_dialog(game_controller* gm, int link_id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::link_dialog),
    link_number(link_id),
    game(gm),
    d6(new dice)
{
    ui->setupUi(this);

    number_labels[0] = ui->number_label_1;
    number_labels[1] = ui->number_label_2;
    number_labels[2] = ui->number_label_3;
    number_labels[3] = ui->number_label_4;
    number_labels[4] = ui->number_label_5;
    number_labels[5] = ui->number_label_6;

    number_buttons[0] = ui->place_button_1;
    number_buttons[1] = ui->place_button_2;
    number_buttons[2] = ui->place_button_3;
    number_buttons[3] = ui->place_button_4;
    number_buttons[4] = ui->place_button_5;
    number_buttons[5] = ui->place_button_6;

    result_labels[0] = ui->result_label_1;
    result_labels[1] = ui->result_label_2;
    result_labels[2] = ui->result_label_3;

    setWindowTitle("正在尝试链接...");
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    ui->roll_button->show();
    update_status();
    ui->discard_button->hide();
    ui->quit_button->show();


    int i;
    for (i = 0; i < 3; i++)
    {
        if (game->link_number(link_number, i) * game->link_number(link_number, i + 3) == 0) minus_results[i] = -1;
        else minus_results[i] = game->link_number(link_number, i) - game->link_number(link_number, i + 3);
    }
    // update numbers
    for (i = 0; i < 6; i++)
    {
        if (game->link_number(link_number, i) != 0)
        {
            dice::show_dice_result(number_labels[i], game->link_number(link_number, i));
            number_labels[i]->show();
        }
        else
        {
            number_labels[i]->hide();
        }
    }
    for (auto& button : number_buttons) button->hide();

    // update results
    for (i = 0; i < 3; i++)
    {
        switch (minus_results[i])
        {
        case -1:
            result_labels[i]->hide();
            break;
        case 0:
            result_labels[i]->setPixmap(QPixmap(":/star"));
            result_labels[i]->show();
            break;
        default:
            result_labels[i]->setPixmap(QPixmap(QString(":/circled_") + QString::number(minus_results[i])));
            result_labels[i]->show();
        }
    }
}

link_dialog::~link_dialog()
{
    delete ui;
}

void link_dialog::on_roll_button_clicked()
{
    ui->roll_button->hide();
    result_1 = d6->roll();
    result_2 = d6->roll();
    dice::show_dice_result(ui->die_result_1, result_1);
    dice::show_dice_result(ui->die_result_2, result_2);
    for (int i = 0 ; i < 6; i++)
        if (game->link_number(link_number, i) == 0)
            number_buttons[i]->show();
}

void link_dialog::update_status()
{
    QLabel* hearts[6] = {ui->heart_1, ui->heart_2, ui->heart_3, ui->heart_4, ui->heart_5, ui->heart_6};
    for (auto& label : hearts) label->setScaledContents(true);
    int i;
    for (i = 0; i < game->hp(); i++) hearts[i]->setPixmap(QPixmap(":/full_heart"));
    for (; i < 6; i++) hearts[i]->setPixmap(QPixmap(":/empty_heart"));

    // update bin status
    ui->wastepaper_hint->setText(QString("废纸篓空位：") + QString::number(game->wastebasket_slots()));
    if (!ui->roll_button->isVisible() and game->wastebasket_slots() > 0) ui->discard_button->show();
    else ui->discard_button->hide();

    if (ui->roll_button->isVisible()) ui->quit_button->show();
    else ui->quit_button->hide();
}

void link_dialog::button_candy(int i)
{
    number_buttons[i]->hide();
    if (result_1 == 0)
    {
        game->set_link_number(link_number, i, result_2);
        dice::show_dice_result(number_labels[i], result_2);
        result_2 = 0;
        ui->die_result_2->hide();
    }
    else
    {
        game->set_link_number(link_number, i, result_1);
        dice::show_dice_result(number_labels[i], result_1);
        result_1 = 0;
        ui->die_result_1->hide();
    }
    int opposite_number = i >= 3 ? i - 3 : i + 3;
    int small_num = opposite_number > i ? i : opposite_number;
    if (game->link_number(link_number, opposite_number) != 0)
    {
        minus_results[small_num] = i <= 2 ? game->link_number(link_number, i) - game->link_number(link_number, opposite_number) : game->link_number(link_number, opposite_number) - game->link_number(link_number, i);
        switch(minus_results[small_num])
        {
        case 0:
            result_labels[small_num]->setPixmap(QPixmap(":/star"));
            result_labels[small_num]->show();
            break;
        case 1: case 2: case 3: case 4: case 5:
            result_labels[small_num]->setPixmap(QPixmap(":/circled_" + QString::number(minus_results[i])));
            result_labels[small_num]->show();
            break;
        default:
            game->use_component(link_number);
            minus_results[small_num] = 2;
            QMessageBox msg;
            msg.setText(QString("链接时发生了爆炸！\n你损失了一个") + component_names_zh[link_number]);
            if (game->storage(link_number) == 0)
            {
                msg.setText(msg.text() + QString("\n由于你没有更多的") + component_names_zh[link_number] + "，你不得不放下手中的工作。");
                msg.exec();
                done(-1);
            }
            else msg.exec();
        }
    }
    update_status();
    bool flag = true;
    for (int i = 0; i < 6; i++) if (game->link_number(link_number, i) == 0) flag = false;
    if (flag)
    {
        game->use_component(link_number);
        int ans = 0;
        for (auto& i : minus_results) ans += i;
        game->add_link_value(link_number, ans + 1); // +1 since the initial value is -1
        QMessageBox msg;
        msg.setText("你放下已经组装好的神器零件。");
        msg.setWindowTitle("组装成功了！");
        msg.exec();
        done(1);
    }
    else
    {
        if (result_1 == 0 and result_2 == 0)
        {
            ui->roll_button->show();
            ui->die_result_1->hide();
            ui->die_result_2->hide();
            ui->quit_button->show();
            for (auto& button : number_buttons) button->hide();
        }
    } 
}

void link_dialog::on_quit_button_clicked()
{
    QMessageBox msg;
    msg.setText("你确定要暂时搁置手头的组装工作吗？\n所有进度都将保留。");
    msg.setWindowTitle("返回工作台");
    msg.setStandardButtons(QMessageBox::StandardButton::Ok | QMessageBox::StandardButton::Cancel);
    if (msg.exec() == QMessageBox::StandardButton::Ok) done(1);
}
void link_dialog::on_discard_button_clicked()
{
    game->dump_dice();
    if (result_1 == 0)
    {
        result_2 = 0;
        ui->die_result_2->hide();
        ui->discard_button->hide();
        ui->roll_button->show();
        for (auto& button : number_buttons) button->hide();
    }
    else
    {
        result_1 = 0;
        ui->die_result_1->hide();
    }

}

void link_dialog::on_place_button_1_clicked() {button_candy(0);}
void link_dialog::on_place_button_2_clicked() {button_candy(1);}
void link_dialog::on_place_button_3_clicked() {button_candy(2);}
void link_dialog::on_place_button_4_clicked() {button_candy(3);}
void link_dialog::on_place_button_5_clicked() {button_candy(4);}
void link_dialog::on_place_button_6_clicked() {button_candy(5);}
