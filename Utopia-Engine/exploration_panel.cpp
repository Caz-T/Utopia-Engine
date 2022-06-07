#include "exploration_panel.h"
#include "ui_exploration_panel.h"
#include <QDebug>
#include <QInputDialog>

exploration_panel::exploration_panel(game_controller* gm, QWidget *parent) :
    panel(gm, parent),
    ui(new Ui::exploration_panel)
{
    ui->setupUi(this);
    this->hide();
}

exploration_panel::~exploration_panel()
{
    delete ui;
}

void exploration_panel::refresh_panel()
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

    // show artifacts and treasures
    QLabel* treasure_labels[6] = {ui->peak_treasure, ui->wilds_treasure, ui->marshes_treasure, ui->canyon_treasure, ui->city_treasure, ui->maw_treasure};
    for (i = 0; i < 6; i++)
    {
        treasure_labels[i]->setText(treasure_names_zh[i]);
        treasure_labels[i]->setStyleSheet(QString("QLabel {color: " + QString(game->treasure_found(i) ? "black}" : "grey}")));
    }
    QLabel* arti_labels[6] = {ui->peak_artifact, ui->wilds_artifact, ui->marshes_artifact, ui->canyon_artifact, ui->city_artifact, ui->maw_artifact};
    for (i = 0; i < 6; i++)
    {
        arti_labels[i]->setText(artifact_names_zh[i]);
        QString temp_stylesheet = "QLabel {color: ";
        switch(game->artifact_status(i))
        {
        case 0:
            temp_stylesheet += "grey";
            break;
        case 1:
            temp_stylesheet += "black";
            break;
        case 2:
            temp_stylesheet += "green";
            break;
        default:
            qDebug() << "artifact status wrong!";
            temp_stylesheet += "white";
        }
        temp_stylesheet += "}";
        arti_labels[i]->setStyleSheet(temp_stylesheet);
    }
    if (game->seal_of_balance_available()) ui->use_seal->show();
    else ui->use_seal->hide();

    // show events
    QLabel* events[6] = {ui->peak_event, ui->wilds_event, ui->marshes_event, ui->canyon_event, ui->city_event, ui->maw_event};
    int event_style[6] = {0};
    QLabel* spare_events[6][4] = {
        {ui->label_25, ui->label_26, ui->label_27, ui->label_28},
        {ui->label_29, ui->label_30, ui->label_31, ui->label_32},
        {ui->label_39, ui->label_40, ui->label_33, ui->label_34},
        {ui->label_37, ui->label_38, ui->label_35, ui->label_36},
        {ui->label_47, ui->label_48, ui->label_41, ui->label_42},
        {ui->label_45, ui->label_46, ui->label_43, ui->label_44}
    }; // hard-coded.
    for (i = 0; i < 4; i++)
        if (game->event_location(i) == -1) continue;
        else event_style[game->event_location(i)] += std::exp2(i);
    for (i = 0; i < 6; i++)
    {
        int k = event_style[i];
        if (k == 1 or k == 2 or k == 4 or k == 8)
        {
            for (auto& label : spare_events[i]) label->hide();
            events[i]->setPixmap(QPixmap(QString(":/event/") + QString::number(std::log2(k))));
            events[i]->setScaledContents(true);
            events[i]->show();
        }
        else
        {
            events[i]->hide();
            for (int j = 0; j < 4; j++)
                if (k & (int)exp2(j)) spare_events[i][j]->setPixmap(QPixmap(QString(":/event/") + QString::number(j)));
                else spare_events[i][j]->setPixmap(QPixmap());
            for (auto& label : spare_events[i])
            {
                label->setScaledContents(true);
                label->show();
            }
        }
    }

    // show exploration status
    QProgressBar* prog[6] = {ui->peak_bar, ui->peak_bar_2, ui->peak_bar_3, ui->peak_bar_4, ui->peak_bar_5, ui->peak_bar_6};
    for (i = 0; i < 6; i++) prog[i]->setValue(game->expl_progress(i));

    panel::refresh_panel();
}

void exploration_panel::explore(int id)
{
    game->proceed_exploration(id);
    exploration_dialog* dlg = new exploration_dialog(game, id, this);
    int r = dlg->exec();;
    qDebug() << "result=" << r;
    if (r == 0) // perfect search
    {
        game->find_artifact(id);
        game->activate_artifact(id);
        game->charge_god_hand(5);
        QMessageBox msg;
        msg.setText("完美的探索！你找到了已经激活的神器，外加五点神之手能量！");
        msg.exec();
    }
    else if (r >= 1 and r <= 10)
    {
        game->find_artifact(id);
        QMessageBox msg;
        msg.setText("很棒的探索！你找到了此区域的神器！");
        msg.exec();
    }
    else if (r >= 11 and r <= 99)
    {
        game->find_component(id);
        QMessageBox msg;
        msg.setText("不错的探索！你找到了此区域的资源组件。");
        msg.exec();
    }
    else
    {
        QMessageBox msg;
        QString msg_text = "是遭遇战！\n";
        // IMPLEMENT battle hint
        if (r < 0) r = -r + 99;
        if (r > 555) r = 555;
        int encounter_level = r / 100;
        if (game->event_location(0) == id)
        {
            encounter_level += 2;
            if (encounter_level > 5) encounter_level = 5;
        }
        msg.setText(msg_text);
        msg.exec();
        bool into_fight = true;
        if (game->treasure_found(2))
        {
            QMessageBox shimmer_judge;
            shimmer_judge.setText("是遭遇战！\n你的烁影月链熠熠发光，似乎可以用它逃脱怪物的追猎。\n你是否要避免这场遭遇战？");
            shimmer_judge.exec();
            shimmer_judge.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            into_fight = shimmer_judge.result() == QMessageBox::Cancel;
        }
        if (into_fight)
        {
            battle_dialog battle(game, id, encounter_level, this);
            battle.exec();
        }
    }
    refresh_panel();
    delete dlg;
}
void exploration_panel::on_peak_button_clicked() {explore(0);}
void exploration_panel::on_wilds_button_clicked() {explore(1);}
void exploration_panel::on_marshes_button_clicked() {explore(2);}
void exploration_panel::on_canyon_button_clicked() {explore(3);}
void exploration_panel::on_city_button_clicked() {explore(4);}
void exploration_panel::on_maw_button_clicked() {explore(5);}

void exploration_panel::on_use_seal_clicked()
{
    QMessageBox msg;
    msg.setWindowTitle(QString("使用") + artifact_names_zh[0]);
    msg.setText(QString("在哪里使用") + artifact_names_zh[0] + QString("？"));
    msg.setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    QPushButton* dlgbuttons[7];
    for (int i = 0; i < 6; i++) dlgbuttons[i] = msg.addButton(location_names_zh[i], (QMessageBox::ButtonRole)5);
    dlgbuttons[6] = msg.addButton("取消", (QMessageBox::ButtonRole)6);
    msg.setDefaultButton(dlgbuttons[6]);
    msg.exec();
    for (int i = 0; i < 6; i++)
    {
        if (msg.clickedButton() == dlgbuttons[i])
        {
            game->use_seal_of_balance(i);
            ui->use_seal->hide();
            refresh_panel();
            return;
        }
    }
}


void exploration_panel::on_return_to_worktable_clicked()
{
    QMessageBox msg;
    msg.setText("是否确定离开探索区域？\n目前的探索进度将被清空。");
    msg.setStandardButtons(QMessageBox::StandardButton::Ok | QMessageBox::StandardButton::Cancel);
    if (msg.exec() == QMessageBox::StandardButton::Ok)
    {
        for (int i = 0; i < 6; i++) game->clean_exploration_progress();
        emit switch_panel_signal(2, this);
    }
}



void exploration_panel::on_camp_button_clicked()
{
    QInputDialog msg(this);
    msg.setWindowTitle("容身之地");
    msg.setLabelText("略感疲乏，你寻找到一处安全的地方。这里并不舒适，但至少足以歇脚。\n你希望休息几天？");
    msg.setIntMinimum(0);
    msg.setIntMaximum(game->doomsday() - game->date());
    msg.setInputMode(QInputDialog::IntInput);
    msg.setOkButtonText("休息");
    msg.setCancelButtonText("起身离开");
    msg.exec();
    game->rest(msg.intValue(), false);
}


void exploration_panel::on_menu_button_clicked()
{
    show_menu();
}

