#ifndef BACKPACK_PANEL_H
#define BACKPACK_PANEL_H

#include <QWidget>
#include "panel.h"

namespace Ui {
class backpack_panel;
}

class backpack_panel : public panel
{
    Q_OBJECT

public:
    explicit backpack_panel(QWidget *parent = nullptr);
    ~backpack_panel();

public slots:
    void refresh_panel();
private:
    Ui::backpack_panel *ui;
};

#endif // BACKPACK_PANEL_H
