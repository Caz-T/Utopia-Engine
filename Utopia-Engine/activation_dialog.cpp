#include "activation_dialog.h"
#include "ui_activation_dialog.h"

#include <QMessageBox>

activation_dialog::activation_dialog(game_controller* gm, int order, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::activation_dialog),
    artifact_number(order),
    game(gm),
    d6(new dice)
{
    int i;
    ui->setupUi(this);

    // please don't ask why these are written this way. Special purposes.
    QLabel* temp_label_store[8] = {ui->number_label_1, ui->number_label_2, ui->number_label_3, ui->number_label_4, ui->number_label_5, ui->number_label_6, ui->number_label_7, ui->number_label_8};
    for (i = 0; i < 8; i++) number_labels[i] = temp_label_store[i];
    QPushButton* temp_button_store[8] = {ui->number_button_1, ui->number_button_2, ui->number_button_3, ui->number_button_4, ui->number_button_5, ui->number_button_6, ui->number_button_7, ui->number_button_8};
    for (i = 0; i < 8; i++) number_buttons[i] = temp_button_store[i];

    setWindowTitle(QString("正在尝试激活") + artifact_names_zh[order]);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    update_hearts();

}

activation_dialog::~activation_dialog()
{
    delete d6;
    delete ui;
}
void activation_dialog::update_hearts()
{
    QLabel* hearts[6] = {ui->heart_1, ui->heart_2, ui->heart_3, ui->heart_4, ui->heart_5, ui->heart_6};
    for (auto& label : hearts) label->setScaledContents(true);
    int i;
    for (i = 0; i < game->hp(); i++) hearts[i]->setPixmap(QPixmap(":/full_heart"));
    for (; i < 6; i++) hearts[i]->setPixmap(QPixmap(":/empty_heart"));
}
void activation_dialog::update_status()
{
    int i;
    update_hearts();

    // update numbers
    for (i = 0; i < 8; i++)
    {
        if (numbers[i] == 0)
        {
            dice::show_dice_result(number_labels[i], numbers[i]);
            number_labels[i]->show();
            number_buttons[i]->hide();
        }
        else
        {
            number_labels[i]->hide();
            number_buttons[i]->show();
        }
    }

    // update result numbers
    QLabel* result_labels[4] = {ui->result_label_1, ui->result_label_2, ui->result_label_3, ui->result_label_4};
    for (i = 0; i < 4; i++)
    {
        switch(minus_results[i])
        {
        case 0:
            result_labels[i]->hide();
            break;
        case 1:
            result_labels[i]->setPixmap(QPixmap(":/circled_1"));
            result_labels[i]->setScaledContents(true);
            result_labels[i]->show();
            break;
        case 2:
            result_labels[i]->setPixmap(QPixmap(":/circled_2"));
            result_labels[i]->setScaledContents(true);
            result_labels[i]->show();
            break;
        case -1:
            result_labels[i]->setPixmap(QPixmap(":/cross"));
            result_labels[i]->setScaledContents(true);
            result_labels[i]->show();
            break;
        default:
            qDebug() << "error in minus results" << i << ":" << minus_results[i] << Qt::endl;
            break;
        }
    }

    // show tool status
    if (game->tool_available(0))
    {
        ui->focus_hint->setText(QString("你的") + tool_names_zh[0] + QString("可以使用，直接获得2点神器能量。"));
        ui->use_focus->show();
    }
    else if (!focus_used)
    {
        ui->focus_hint->setText(QString("你的") + tool_names_zh[0] + QString("不能使用。"));
        ui->use_focus->hide();
    }

    // show current energy
    if (game->activation_energy(artifact_number + total_energy()) > 4) ui->energy_bar->setValue(4);
    else ui->energy_bar->setValue(game->activation_energy(artifact_number + total_energy()));

}
void activation_dialog::on_use_focus_clicked()
{
    game->use_tool(0);
    focus_used = true;
    ui->use_focus->hide();
    ui->focus_hint->setText(QString("你已经使用了") + tool_names_zh[0]);
}
int activation_dialog::total_energy()
{
    int ans = focus_used ? 2 : 0;
    for (auto& i : minus_results)
        ans += i;
    return ans;
}

void activation_dialog::button_candy(int i)
{
    int opposite_number = i >= 4 ? i - 4 : i + 4;
    if (result_1 == 0)
    {
        numbers[i] = result_2;
        result_2 = 0;
        ui->die_result_2->hide();
    }
    else
    {
        numbers[i] = result_1;
        result_1 = 0;
        ui->die_result_1->hide();
    }
    if (numbers[opposite_number] == numbers[i])
    {
        numbers[i] = 0;
        numbers[opposite_number] = 0;
    }
    else if (numbers[opposite_number] != 0)
    {
        switch(i >= 4 ? numbers[i] - numbers[opposite_number] : numbers[opposite_number] - numbers[i])
        {
        case 5:
            minus_results[i >= 4 ? i - 4 : i] = 2;
            break;
        case 4:
            minus_results[i >= 4 ? i - 4 : i] = 1;
            break;
        case 3:case 2:case 1:
            minus_results[i >= 4 ? i - 4 : i] = -1;
        case 0:
            numbers[i] = 0;
            numbers[opposite_number] = 0;
            break;
        default:
            minus_results[i >= 4 ? i - 4 : i] = -1;
            if (game->change_hp(-1))
            {
                setResult(0);
                return;
            }
            break;
        }
    }
    bool flag = true;
    for (auto p : numbers) if (p == 0) flag = false;
    update_status();
    if (flag)
    {
        game->increase_activate_attempt(i);
        done(total_energy());
    }
    else
    {
        if (result_1 == 0 and result_2 == 0)
        {
            ui->roll_button->show();
            ui->die_result_1->hide();
            ui->die_result_2->hide();
            for (auto& button : number_buttons) button->hide();
        }
    }
}

void activation_dialog::on_number_button_1_clicked() {button_candy(0);}
void activation_dialog::on_number_button_2_clicked() {button_candy(1);}
void activation_dialog::on_number_button_3_clicked() {button_candy(2);}
void activation_dialog::on_number_button_4_clicked() {button_candy(3);}
void activation_dialog::on_number_button_5_clicked() {button_candy(4);}
void activation_dialog::on_number_button_6_clicked() {button_candy(5);}
void activation_dialog::on_number_button_7_clicked() {button_candy(6);}
void activation_dialog::on_number_button_8_clicked() {button_candy(7);}
void activation_dialog::on_abort_button_clicked()
{
    QMessageBox msg;
    msg.setWindowTitle("放弃激活");
    msg.setText("你确定要放弃激活此神器吗？\n本次激活中所有的能量将会消失，进度将会重置。");
    msg.setStandardButtons(QMessageBox::StandardButton::Ok | QMessageBox::StandardButton::Cancel);
    if (msg.exec() == QMessageBox::StandardButton::Ok) done(0);
}

