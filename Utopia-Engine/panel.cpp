#include "panel.h"

panel::panel(game_controller* gm, QWidget *parent)
    : QWidget{parent}, game(gm)
{

}

void panel::close_panel()
{
    this->hide();
}

void panel::refresh_panel()
{
    this->show();
}

void panel::show_menu()
{
    QMessageBox msg;
    msg.setWindowTitle("存档并退出");
    msg.setText("你确定要存档并退出游戏？\n如果存档创建成功，所有数据都将保留。");
    msg.addButton(QMessageBox::StandardButton::Yes);
    msg.addButton(QMessageBox::StandardButton::Cancel);
    if (msg.exec() == QMessageBox::StandardButton::Yes)
    {
        game->save_game();
        emit switch_panel_signal(0, this);
    }
}
