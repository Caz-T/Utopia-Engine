#ifndef DICE_H
#define DICE_H

#include <QObject>
#include <QRandomGenerator>
#include <QLabel>

// this class is basically a random number generator.

class dice : public QObject
{
    Q_OBJECT
public:
    explicit dice(QObject *parent = nullptr);

    QRandomGenerator random;

    int roll(int sides = 6); // actually, in Utopia Engine, all dice are six-sided.
    static void show_dice_result(QLabel* lbl, int result);
signals:

};

#endif // DICE_H
