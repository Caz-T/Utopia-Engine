#ifndef PANEL_H
#define PANEL_H

#include <QWidget>
#include <QProgressBar>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include "game_controller.h"

class panel : public QWidget
{
    Q_OBJECT
public:
    explicit panel(game_controller* gm, QWidget *parent = nullptr);
    ~panel() = default;

public slots:
    // we require all panels' refreshing and closing to be slots
    virtual void refresh_panel(); // This is to be triggered whenever the subclass is shown or refreshed.
    virtual void close_panel(); // This is to be triggered whenever the subclass is to be hidden.

protected:
    game_controller* game;
    void show_menu();

signals:
    void switch_panel_signal(int target, panel* sender);
};

#endif // PANEL_H
