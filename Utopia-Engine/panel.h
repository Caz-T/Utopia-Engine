#ifndef PANEL_H
#define PANEL_H

#include <QWidget>
#include "game_controller.h"

class panel : public QWidget
{
    Q_OBJECT
public:
    explicit panel(game_controller* gm, QWidget *parent = nullptr);

public slots:
    // we require all panels' refreshing and closing to be slots
    virtual void refresh_panel(); // This is to be triggered whenever the subclass is shown or refreshed.
    virtual void close_panel(); // This is to be triggered whenever the subclass is to be hidden.

protected:
    game_controller* game;

signals:

};

#endif // PANEL_H
