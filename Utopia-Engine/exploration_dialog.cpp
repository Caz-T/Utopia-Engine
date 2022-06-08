#include "exploration_dialog.h"
#include "ui_exploration_dialog.h"

#include <QMessageBox>

exploration_dialog::exploration_dialog(game_controller* gm, int id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::exploration_dialog),
    game(gm),
    d6(new dice(this)),
    location_id(id)
{
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    ui->setupUi(this);

    blanks[0] = ui->label;
    blanks[1] = ui->label_2;
    blanks[2] = ui->label_3;
    blanks[3] = ui->label_4;
    blanks[4] = ui->label_5;
    blanks[5] = ui->label_6;
    buttons[0] = ui->pushButton_1;
    buttons[1] = ui->pushButton_2;
    buttons[2] = ui->pushButton_3;
    buttons[3] = ui->pushButton_4;
    buttons[4] = ui->pushButton_5;
    buttons[5] = ui->pushButton_6;

    for (auto& button : buttons) button->setVisible(false);

    setWindowTitle(QString("探索：") + location_names_zh[id]);
    QString envi_text = "当前环境效果：\n";
    if (game->event_location(2) == location_id) envi_text.append("好运气——搜索结果-10\n");
    if (game->artifact_status(1) == 2 and (location_id == 0 or location_id == 5)) envi_text.append("隐士之镜——此处搜索结果-10\n");
    if (game->artifact_status(4) == 2 and (location_id == 2 or location_id == 3)) envi_text.append("预示棱镜——此处搜索结果-10\n");
    ui->envi_effects->setText(envi_text);

}

exploration_dialog::~exploration_dialog()
{
    delete ui;
}

void exploration_dialog::on_roll_button_clicked()
{
    ui->roll_button->hide();
    result_1 = d6->roll();
    result_2 = d6->roll();
    dice::show_dice_result(ui->die_result_1, result_1);
    dice::show_dice_result(ui->die_result_2, result_2);
    for (int i = 0 ; i < 6; i++)
        if (numbers[i] == 0)
            buttons[i]->setVisible(true);
}

void exploration_dialog::button_candy(int i)
{
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
    buttons[i]->hide();
    dice::show_dice_result(blanks[i], numbers[i]);
    bool flag = true;
    for (auto p : numbers) if (p == 0) flag = false;
    if (flag)
    {
        int expl_result = 100 * (numbers[0] - numbers[3]) + 10 * (numbers[1] - numbers[4]) + (numbers[2] - numbers[5]);
        if (expl_result <= 0)
        {
            done(expl_result);
            return;
        }
        if (game->tool_available(1) and expl_result <= 99)
        {
            QMessageBox* msg = new QMessageBox(this);
            msg->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msg->setText("你的探索手杖可以使用，会将本次探索结果变为1。\n你是否想要使用？");
            msg->setWindowTitle("是否使用探索手杖？");
            if (msg->exec() == QMessageBox::Ok)
            {
                game->use_tool(1);
                done(1);
                return;
            }
        }
        if (game->event_location(2) == location_id)
        {
            QMessageBox* msg = new QMessageBox(this);
            msg->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

            msg->setText(QString("触发了本地点的事件：好运气，可以至多将探索结果减少10。\n当前探索结果是") + QString::number(expl_result) +
                         QString("，你是否想要减少到") + QString::number(expl_result - 10 < 0 ? 0 : expl_result - 10) + QString("？"));
            msg->setWindowTitle("是否使用好运气？");
            if (msg->exec() == QMessageBox::Ok)
            {
                expl_result -= 10;
                if (expl_result <= 0)
                {
                    done(0);
                    return;
                }
            }
        }
        if (game->artifact_status(1) == 2 and (location_id == 0 or location_id == 5))
        {
            QMessageBox* msg = new QMessageBox(this);
            msg->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

            msg->setText(QString("你的神器隐士之镜已经激活，可以至多将探索结果减少10。\n当前探索结果是") + QString::number(expl_result) +
                         QString("，你是否想要减少到") + QString::number(expl_result - 10 < 0 ? 0 : expl_result - 10) + QString("？"));
            msg->setWindowTitle("是否使用隐士之镜？");
            if (msg->exec() == QMessageBox::Ok)
            {
                expl_result -= 10;
                if (expl_result <= 0)
                {
                    done(0);
                    return;
                }
            }
        }
        if (game->artifact_status(4) == 2 and (location_id == 2 or location_id == 3))
        {
            QMessageBox* msg = new QMessageBox(this);
            msg->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

            msg->setText(QString("你的神器预示棱镜已经激活，可以至多将探索结果减少10。\n当前探索结果是") + QString::number(expl_result) +
                         QString("，你是否想要减少到") + QString::number(expl_result - 10 < 0 ? 0 : expl_result - 10) + QString("？"));
            msg->setWindowTitle("是否使用预示棱镜？");
            if (msg->exec() == QMessageBox::Ok)
            {
                expl_result -= 10;
                if (expl_result <= 0)
                {
                    done(0);
                    return;
                }
            }
        }
        done(expl_result);
        return;
    }
    else
    {
        if (result_1 == 0 and result_2 == 0)
        {
            ui->roll_button->show();
            ui->die_result_1->hide();
            ui->die_result_2->hide();
            for (auto& button : buttons) button->hide();
        }
    }
}

void exploration_dialog::on_pushButton_1_clicked() {button_candy(0);}
void exploration_dialog::on_pushButton_2_clicked() {button_candy(1);}
void exploration_dialog::on_pushButton_3_clicked() {button_candy(2);}
void exploration_dialog::on_pushButton_4_clicked() {button_candy(3);}
void exploration_dialog::on_pushButton_5_clicked() {button_candy(4);}
void exploration_dialog::on_pushButton_6_clicked() {button_candy(5);}


