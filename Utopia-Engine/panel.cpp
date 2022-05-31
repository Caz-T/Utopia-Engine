#include "panel.h"

panel::panel(QWidget *parent)
    : QWidget{parent}
{

}

void panel::close_panel()
{
    this->close();
}
