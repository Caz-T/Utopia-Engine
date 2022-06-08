#include "battle_dialog.h"
#include "ui_battle_dialog.h"

battle_dialog::battle_dialog(game_controller* gm, int rg, int lv, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::battle_dialog),
    game(gm),
    level(lv),
    region(rg),
    monster_atk(monster_attack[level]),
    player_atk(player_attack[level]),
    d6(new dice)
{
    ui->setupUi(this);

    setWindowTitle(QString("遭遇战！"));
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    update_hearts();

    QString monster_info = "怪物信息：\n";
    if (is_spirit_monster[region][level])
    {
        ui->enemy_name->setStyleSheet("QLabel {color: blue}");
        monster_info.append(monster_names_zh[region][level] + QString("是灵魂怪物。\n"));
    }
    else ui->enemy_name->setStyleSheet("QLabel {color: black}");
    ui->enemy_name->setText(monster_names_zh[region][level]);


    // deals with events, artifacts and treasures.
    if (game->event_location(0) == region)
    {
        monster_info.append(event_names_zh[1] + QString("——此区域遭遇战等级已+2\n"));
    }
    if (game->artifact_status(3) == 2 and is_spirit_monster[region][level])
    {
        monster_info.append(artifact_names_zh[3] + QString("——对阵灵魂怪物时，掷骰结果+1\n"));
        dice_modification ++;
    }
    if (game->treasure_found(0))
    {
        monster_info.append(treasure_names_zh[0] + QString("——怪物的攻击范围-1\n"));
        monster_atk --;
    }
    if (game->treasure_found(5))
    {
        monster_info.append(treasure_names_zh[5] + QString("——你的攻击范围+1\n"));
        player_atk --;
    }
    if (monster_atk < 1) monster_atk = 1;
    if (monster_atk > 6) monster_atk = 6;
    if (player_atk < 1) player_atk = 1;
    if (player_atk > 6) player_atk = 6;
    ui->enemy_info->setText(monster_info);

    // shows both attacks, fancily
    QString monster_data;
    monster_data.append("怪物攻击范围：");
    if (monster_atk > 1) monster_data.append("1-");
    monster_data.append(QString::number(monster_atk));
    monster_data.append("\t你的攻击范围：");
    monster_data.append(QString::number(player_atk));
    if (player_atk < 6) monster_data.append("-6");
    ui->enemy_data->setText(monster_data);

    // decides which buttons to show
    if (game->tool_available(2))
    {
        ui->para_hint->setText(QString("你的") + tool_names_zh[2] + QString("可以使用。"));
        ui->use_para->setText(QString("使用") + tool_names_zh[2]);
    }
    ui->para_hint->hide();
    ui->use_para->hide();
    ui->roll_dice->show();
    ui->proceed_button->hide();
    ui->loot_roll->hide();
}

battle_dialog::~battle_dialog()
{
    delete ui;
}

void battle_dialog::update_hearts()
{
    QLabel* hearts[6] = {ui->heart_1, ui->heart_2, ui->heart_3, ui->heart_4, ui->heart_5, ui->heart_6};
    for (auto& label : hearts) label->setScaledContents(true);
    int i;
    for (i = 0; i < game->hp(); i++) hearts[i]->setPixmap(QPixmap(":/full_heart"));
    for (; i < 6; i++) hearts[i]->setPixmap(QPixmap(":/empty_heart"));
}

void battle_dialog::on_roll_dice_clicked()
{
    result_1 = d6->roll();
    result_2 = d6->roll();
    dice::show_dice_result(ui->die_result_1, result_1);
    dice::show_dice_result(ui->die_result_2, result_2);
    ui->roll_dice->hide();
    ui->proceed_button->show();
    if (game->tool_available(2))
    {
        ui->use_para->show();
        ui->para_hint->show();
    }
}


void battle_dialog::on_use_para_clicked()
{
    game->use_tool(2);
    result_1 += 2;
    result_2 += 2;
    if (result_1 > 6) result_1 = 6;
    if (result_2 > 6) result_2 = 6;
    ui->para_hint->hide();
    ui->use_para->hide();
    dice::show_dice_result(ui->die_result_1, result_1);
    dice::show_dice_result(ui->die_result_2, result_2);
}


void battle_dialog::on_proceed_button_clicked()
{
    ui->proceed_button->hide();
    ui->para_hint->hide();
    ui->use_para->hide();
    ui->die_result_1->hide();
    ui->die_result_2->hide();
    hp_lost = 0;
    if (result_1 <= monster_atk) hp_lost ++;
    if (result_2 <= monster_atk) hp_lost ++;
    if (result_1 >= player_atk or result_2 >= player_atk)
    {
        if (game->hp() < hp_lost) // death
        {
            game->change_hp(-hp_lost);
            update_hearts();
            done(-1);
        }
        else
        {
            ui->loot_roll->show();
            if (game->hp() > hp_lost)
            {
                game->change_hp(-hp_lost);
                hp_lost = 0;
            }
            else
            {
                ui->heart_1->setPixmap(QPixmap(":/empty_heart"));
                ui->heart_2->setPixmap(QPixmap(":/empty_heart"));
            }
            QMessageBox msg;
            msg.setText(QString("你击败了") + monster_names_zh[region][level] + QString("!\n请再次掷骰判定掉落。"));
            msg.exec();
        }
    }
    else
    {
        ui->roll_dice->show();
        if (game->change_hp(-hp_lost)) done(-1);
    }
    update_hearts();
}


void battle_dialog::on_loot_roll_clicked()
{
    int loot = d6->roll();
    dice::show_dice_result(ui->die_result_1, loot);
    QMessageBox msg;
    msg.setText(QString("掷骰结果为") + QString::number(loot) + QString(loot <= level + 1 ? "，有掉落物！" : "，没有掉落物。"));
    if (loot <= level)
    {
        if (level == 4)
        {
            msg.setText(msg.text() + QString("\n你击败了传说级怪物，获得了宝藏" + treasure_names_zh[region] + QString("!")));
            game->find_treasure(region);
        }
        else
        {
            msg.setText(msg.text() + QString("获得了组件：") + component_names_zh[region]);
            game->find_component(region);
        }
        setResult(2);
    }
    else setResult(1);
    msg.exec();
    if (hp_lost > 0) game->change_hp(-hp_lost);
    done(result());
}

