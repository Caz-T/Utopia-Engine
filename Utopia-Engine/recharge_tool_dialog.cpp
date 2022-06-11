#include "recharge_tool_dialog.h"
#include "ui_recharge_tool_dialog.h"

recharge_tool_dialog::recharge_tool_dialog(game_controller* gm, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::recharge_tool_dialog),
    game(gm)
{
    ui->setupUi(this);
    ui->icon_label_1->setPixmap(QPixmap(":/resource/silver"));
    ui->icon_label_2->setPixmap(QPixmap(":/resource/quartz"));
    ui->icon_label_3->setPixmap(QPixmap(":/resource/gum"));
    ui->icon_label_4->setPixmap(QPixmap(":/resource/silica"));
    ui->icon_label_5->setPixmap(QPixmap(":/resource/wax"));
    ui->icon_label_6->setPixmap(QPixmap(":/resource/lead"));

    QPushButton* buttons[6] = {ui->choice_button_1, ui->choice_button_2, ui->choice_button_3, ui->choice_button_4, ui->choice_button_5, ui->choice_button_6};
    for (int i = 0; i < 6; i++)
        if (game->storage(i) == 0) buttons[i]->hide();

    ui->confirm_button_1->hide();
    ui->confirm_button_2->hide();
    ui->confirm_button_3->hide();
}

recharge_tool_dialog::~recharge_tool_dialog()
{
    delete ui;
}

void recharge_tool_dialog::button_candy(int i)
{
    QPushButton* buttons[6] = {ui->choice_button_1, ui->choice_button_2, ui->choice_button_3, ui->choice_button_4, ui->choice_button_5, ui->choice_button_6};
    chosen_comp[chosen] = i;
    chosen++;
    chosen_times[i]++;
    if (chosen == 3)
    {
        for (auto& button : buttons) button->hide();
        QPushButton* confirm_buttons[3] = {ui->confirm_button_1, ui->confirm_button_2, ui->confirm_button_3};
        for (int i = 0; i < 3; i++) if (!game->tool_available(i)) confirm_buttons[i]->show();
    }
    else if (game->storage(i) == chosen_times[i]) buttons[i]->hide();
    ui->component_list->setText(ui->component_list->text() + " " + component_names_zh[i]);
}


void recharge_tool_dialog::on_cancel_button_clicked() {reject();}

void recharge_tool_dialog::on_confirm_button_1_clicked() {confirm_candy(0);}
void recharge_tool_dialog::on_confirm_button_2_clicked() {confirm_candy(1);}
void recharge_tool_dialog::on_confirm_button_3_clicked() {confirm_candy(2);}

void recharge_tool_dialog::confirm_candy(int i)
{
    game->use_tool(i, true);
    for (auto& j : chosen_comp) game->use_component(j);
    accept();
}

void recharge_tool_dialog::on_choice_button_1_clicked() {button_candy(0);}
void recharge_tool_dialog::on_choice_button_2_clicked() {button_candy(1);}
void recharge_tool_dialog::on_choice_button_3_clicked() {button_candy(2);}
void recharge_tool_dialog::on_choice_button_4_clicked() {button_candy(3);}
void recharge_tool_dialog::on_choice_button_5_clicked() {button_candy(4);}
void recharge_tool_dialog::on_choice_button_6_clicked() {button_candy(5);}
