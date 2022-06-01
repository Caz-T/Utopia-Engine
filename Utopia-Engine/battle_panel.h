#ifndef BATTLE_PANEL_H
#define BATTLE_PANEL_H

#include <QWidget>
#include "panel.h"

namespace Ui {
class battle_panel;
}

class battle_panel : public panel
{
    Q_OBJECT

public:
    explicit battle_panel(game_controller* gm, QWidget *parent = nullptr);
    ~battle_panel();

public slots:
    void refresh_panel();

private:
    Ui::battle_panel *ui;
};

#endif // BATTLE_PANEL_H
