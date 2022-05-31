#ifndef WORKTABLE_PANEL_H
#define WORKTABLE_PANEL_H

#include <QWidget>
#include "panel.h"

namespace Ui {
class worktable_panel;
}

class worktable_panel : public panel
{
    Q_OBJECT

public:
    explicit worktable_panel(QWidget *parent = nullptr);
    ~worktable_panel();

public slots:
    void refresh_panel();

private:
    Ui::worktable_panel *ui;
};

#endif // WORKTABLE_PANEL_H
