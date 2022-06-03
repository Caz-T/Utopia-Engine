#include "dice.h"

dice::dice(QObject *parent)
    : QObject{parent}, random(QRandomGenerator::securelySeeded())
{
}

int dice::roll(int sides)
{
    return random.generate() % sides + 1;
}

void dice::show_dice_result(QLabel* lbl, int result)
{
    QString path = ":/dice/";
    path.append(QChar(result + '0'));
    lbl->setPixmap(QPixmap(path));
    lbl->show();
}
