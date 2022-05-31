#ifndef DICE_H
#define DICE_H

#include <QObject>

// this class is basically a random number generator.

class dice : public QObject
{
    Q_OBJECT
public:
    explicit dice(QObject *parent = nullptr);

signals:

};

#endif // DICE_H
