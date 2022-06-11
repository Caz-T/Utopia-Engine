#include "worktable_panel.h"
#include "ui_worktable_panel.h"

#include "link_dialog.h"
#include "activation_dialog.h"
#include "recharge_tool_dialog.h"
#include "final_activation_dialog.h"

#include <QInputDialog>
#include <QStringList>

worktable_panel::worktable_panel(game_controller* gm, QWidget *parent) :
    panel(gm, parent),
    ui(new Ui::worktable_panel)
{
    ui->setupUi(this);

    worktable_panel::refresh_panel();
    this->hide(); // by default everything is hidden when created

    ui->use_ancient_record->setText(QString("使用") + treasure_names_zh[4]);

    QLabel* arti_labels[6] = {ui->artifact_label_1, ui->artifact_label_2, ui->artifact_label_3, ui->artifact_label_4, ui->artifact_label_5, ui->artifact_label_6};
    for (auto& lbl : arti_labels) lbl->setStyleSheet("QLabel {color: white}");
    QLabel* link_labels[6] = {ui->link_label_1, ui->link_label_2, ui->link_label_3, ui->link_label_4, ui->link_label_5, ui->link_label_6};
    for (auto& lbl : link_labels) lbl->setStyleSheet("QLabel {color: white}");
    ui->calendar_label->setStyleSheet("QLabel {color: white}");
    QLCDNumber* lcds[6] = {ui->compo_count_1, ui->compo_count_2, ui->compo_count_3, ui->compo_count_4, ui->compo_count_5, ui->compo_count_6};
    for (auto& num : lcds) num->setStyleSheet("QLCDNumber {color: white}");

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
            if (game->link_value(i) == -1)
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
        // also show ancient_record, if applicable
        if (game->the_ancient_record_available()) ui->use_ancient_record->show();
        else ui->use_ancient_record->hide();
    }
    else
    {
        for (auto& button : link_buttons) button->hide();
        for (auto& label : link_labels) label->hide();
    }

    // show recharge tool belt button
    if (game->artifact_status(5) == 2) ui->recharge_tool->show();
    else ui->recharge_tool->hide();

    // show final button.
    flag = true;
    for (int i = 0; i < 6; i++)
        if (game->link_value(i) == -1)
        {
            flag = false;
            break;
        }
    if (flag) ui->final_button->show();
    else ui->final_button->hide();

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
    if (game->activation_attempt(i) == 1) game->day_progress();
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
    refresh_panel();
}

void worktable_panel::link(int i)
{
    if (game->storage(i) < 1)
    {
        QMessageBox msg;
        msg.setWindowTitle("资源组件不足！");
        msg.setText(QString("你需要寻找至少一份") + component_names_zh[i] + QString("才能开始链接！"));
        msg.exec();
    }
    else
    {
        link_dialog dlg(game, i, this);
        dlg.exec();
    }
    qDebug() << "Link value:";
    for (int i = 0; i < 5; i++) qDebug() << game->link_value(i);
    refresh_panel();
}

void worktable_panel::on_artifact_button_1_clicked() {activate(0);}
void worktable_panel::on_artifact_button_2_clicked() {activate(1);}
void worktable_panel::on_artifact_button_3_clicked() {activate(2);}
void worktable_panel::on_artifact_button_4_clicked() {activate(3);}
void worktable_panel::on_artifact_button_5_clicked() {activate(4);}
void worktable_panel::on_artifact_button_6_clicked() {activate(5);}


void worktable_panel::on_link_button_1_clicked() {link(0);}
void worktable_panel::on_link_button_2_clicked() {link(1);}
void worktable_panel::on_link_button_3_clicked() {link(2);}
void worktable_panel::on_link_button_4_clicked() {link(3);}
void worktable_panel::on_link_button_5_clicked() {link(4);}
void worktable_panel::on_link_button_6_clicked() {link(5);}


void worktable_panel::on_recharge_tool_clicked()
{
    recharge_tool_dialog dlg(game, this);
    dlg.exec();
    refresh_panel();
}


void worktable_panel::on_final_button_clicked()
{
    QMessageBox msg;
    msg.setText("乌托邦引擎的六个组件和六处链接静静立在工作室内。\n你准备好开始最后的激活了吗？\n一旦激活开始就无法终止，直到乌托邦引擎被成功激活或者你死去。");
    msg.setWindowTitle("最终确认");
    msg.setStandardButtons(QMessageBox::StandardButton::Ok | QMessageBox::StandardButton::Cancel);
    if (msg.exec() == QMessageBox::StandardButton::Ok)
    {
        final_activation_dialog dlg(game, this);
        dlg.exec();
    }
}


void worktable_panel::on_use_ancient_record_clicked()
{
    QInputDialog dlg;
    dlg.setInputMode(QInputDialog::TextInput);
    dlg.setLabelText("请选择一处链接点，将它的链接值设为1:");
    dlg.setOption(QInputDialog::UseListViewForComboBoxItems);
    QStringList lst;
    for (int i = 0; i < 6; i++)
    {
        if (game->link_value(i) > 1)
        {
            QString temp;
            temp.append(QString::number(i + 1));
            temp.append(component_names_zh[i]);
            temp.append("链接，目前链接值：");
            temp.append(QString::number(game->link_value(i)));
            lst << temp;
        }
    }
    dlg.setComboBoxItems(lst);
    if (dlg.exec())
    {
        QString str = dlg.textValue();
        int order = str[0].digitValue() - 1;
        qDebug() << "selected" << order;
        game->add_link_value(order, 1 - game->link_value(order));
        game->use_the_ancient_record();
    }
    refresh_panel();
}
