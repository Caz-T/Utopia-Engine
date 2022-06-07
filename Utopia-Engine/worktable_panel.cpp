#include "worktable_panel.h"
#include "ui_worktable_panel.h"

#include "link_dialog.h"
#include "activation_dialog.h"

#include <QInputDialog>

worktable_panel::worktable_panel(game_controller* gm, QWidget *parent) :
    panel(gm, parent),
    ui(new Ui::worktable_panel)
{
    ui->setupUi(this);


    refresh_panel();
    this->hide(); // by default everything is hidden when created
}

worktable_panel::~worktable_panel()
{
    delete ui;
}

void worktable_panel::refresh_panel()
{
    int i;

    // show hitpoints
    QLabel* hearts[6] = {ui->heart_1, ui->heart_2, ui->heart_3, ui->heart_4, ui->heart_5, ui->heart_6};
    for (i = 0; i < game->hp(); i++) hearts[i]->setPixmap(QPixmap(":/full_heart"));
    for (; i < 6; i++) hearts[i]->setPixmap(QPixmap(":/empty_heart"));

    // show calendar-related stuff
    ui->calendar_bar_upper->setValue(game->date() > 11 ? 11 : game->date());
    ui->calendar_bar_lower->setValue(game->date() > 11 ? game->date() - 11 : 0);
    QLabel* skulls[8] = {ui->skull_1, ui->skull_2, ui->skull_3, ui->skull_4, ui->skull_5, ui->skull_6, ui->skull_7, ui->skull_8};
    for (i = 15; i < game->doomsday(); i++) skulls[i - 15]->setPixmap(QPixmap("://skull_crossed"));
    for (; i <= 22; i++) skulls[i - 15]->setPixmap(QPixmap(":/skull"));
    ui->days_left->display((int) game->doomsday() - game->date());

    // show storage
    QLCDNumber* components[6] = {ui->compo_count_1, ui->compo_count_2, ui->compo_count_3, ui->compo_count_4, ui->compo_count_5, ui->compo_count_6 };
    for (i = 0; i < 6; i++) components[i]->display(game->storage(i));

    // show artifacts
    QLabel* arti_labels[6] = {ui->artifact_label_1, ui->artifact_label_2, ui->artifact_label_3, ui->artifact_label_4, ui->artifact_label_5, ui->artifact_label_6};
    QPushButton* arti_buttons[6] = {ui->artifact_button_1, ui->artifact_button_2, ui->artifact_button_3, ui->artifact_button_4, ui->artifact_button_5, ui->artifact_button_6};
    for (i = 0; i < 6; i++)
    {
        arti_buttons[i]->setText(artifact_names_zh[i]);
        QString arti_text;
        switch (game->artifact_status(i))
        {
        case 0:
            arti_buttons[i]->hide();
            arti_text = artifact_names_zh[i] + QString("尚未找到");
            break;
        case 1:
            arti_buttons[i]->show();
            arti_text = artifact_names_zh[i] + QString("激活进度：") + QString::number(game->activation_attempt(i)) + QString("/2\n");
            arti_text.append(QString("能量槽中有") + QString::number(game->activation_energy(i)) + QString("点能量。"));
            break;
        case 2:
            arti_buttons[i]->hide();
            arti_text = artifact_names_zh[i] + QString("已经激活！");
            break;
        default:
            qDebug() << "error status";
            break;
        }
        arti_labels[i]->setText(arti_text);
    }

    // show links, only after all artifacts are activated.
    bool flag = true;
    for (i = 0; i < 6; i++)
        if (game->artifact_status(i) != 2)
        {
            flag = false;
            break;
        }
    QLabel* link_labels[6] = {ui->link_label_1, ui->link_label_2, ui->link_label_3, ui->link_label_4, ui->link_label_5, ui->link_label_6};
    QPushButton* link_buttons[6] = {ui->link_button_1, ui->link_button_2, ui->link_button_3, ui->link_button_4, ui->link_button_5, ui->link_button_6};
    if (flag)
    {
        for (i = 0; i < 6; i++)
        {
            if (game->link_value(i) == 0)
            {
                link_buttons[i]->show();
                link_labels[i]->setText(QString("需要") + component_names_zh[i] + QString("进行链接。"));
            }
            else
            {
                link_buttons[i]->hide();
                link_labels[i]->setText(QString("此处已经链接，链接值为") + QString::number(game->link_value(i)));
            }
        }
    }
    else
    {
        for (auto& button : link_buttons) button->hide();
        for (auto& label : link_labels) label->hide();
    }

    panel::refresh_panel();
}

void worktable_panel::on_leave_worktable_clicked()
{
    QMessageBox msg;
    msg.setText("是否确定离开工作台？");
    msg.setStandardButtons(QMessageBox::StandardButton::Ok | QMessageBox::StandardButton::Cancel);
    if (msg.exec() == QMessageBox::StandardButton::Ok) emit switch_panel_signal(1, this);
}


void worktable_panel::on_sleep_button_clicked()
{
    QInputDialog msg(this);
    msg.setWindowTitle("诡谲的日光映在窗框上....");
    msg.setLabelText("末日将近，你担心自己会和这个世界一同沉沉睡去。（或许这样也挺好？）\n感谢现代文明，你的工作室颇为舒适。\n如果你连续休息3天以上，可以额外回复一点生命值。\n你希望休息几天？");
    msg.setIntMinimum(0);
    msg.setIntMaximum(game->doomsday() - game->date());
    msg.setInputMode(QInputDialog::IntInput);
    msg.setOkButtonText("入睡");
    msg.setCancelButtonText("起身");
    msg.exec();
    game->rest(msg.intValue(), true);
}


void worktable_panel::on_menu_button_clicked()
{
    show_menu();
}

void worktable_panel::activate(int i)
{
    if (game->treasure_found(1) and game->activation_attempt(i) == 0) // bracelet of Ios
    {
        QMessageBox msg;
        msg.setText(QString("你持有") + treasure_names_zh[1] + QString("，且这是此处的初次链接。\n你发现能量槽里已经有1点能量了。"));
        msg.exec();
        game->increase_activate_energy(i, 1);
    }
    activation_dialog act_dlg(game, i, this);
    game->increase_activate_energy(i, act_dlg.exec());
    if (game->activation_attempt(i) == 2 and game->artifact_status(i) == 1) // two tries but no activation
    {
        QMessageBox msg;
        msg.setText("两次过后，你仍然没能启动此神器。好在拼拼凑凑，你发现有种蛮力方法可以强行激活它。\n你花了一整天，让神器焕发出了它应有的光芒。");
        msg.setWindowTitle("强行激活");
        game->day_progress();
        game->activate_artifact(i);
    }
}

void worktable_panel::link(int i)
{
    link_dialog dlg(game, i, this);
    dlg.exec();
}
