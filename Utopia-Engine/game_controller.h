#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <QObject>

class game_controller : public QObject
{
    Q_OBJECT
public:
    explicit game_controller(QObject *parent = nullptr);

signals:

};

#endif // GAME_CONTROLLER_H
