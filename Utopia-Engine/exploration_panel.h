#ifndef EXPLORATION_PANEL_H
#define EXPLORATION_PANEL_H

#include <QWidget>
#include "panel.h"

namespace Ui {
class exploration_panel;
}

class exploration_panel : public panel
{
    Q_OBJECT

public:
    explicit exploration_panel(QWidget *parent = nullptr);
    ~exploration_panel();

public slots:
    void refresh_panel();

private:
    Ui::exploration_panel *ui;
};

#endif // EXPLORATION_PANEL_H
