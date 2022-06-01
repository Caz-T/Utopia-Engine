#include "panel.h"

panel::panel(game_controller* gm, QWidget *parent)
    : QWidget{parent}, game(gm)
{

}

void panel::close_panel()
{
    this->hide();
}
