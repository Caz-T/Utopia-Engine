#include "exploration_panel.h"
#include "ui_exploration_panel.h"
#include <QDebug>

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

    // show artifacts and stuff
    QLCDNumber* components[6] = {ui->compo_count_1, ui->compo_count_2, ui->compo_count_3, ui->compo_count_4, ui->compo_count_5, ui->compo_count_6 };
    for (i = 0; i < 6; i++) components[i]->display(game->storage(i));
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
            // IMPLEMENT battle
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
