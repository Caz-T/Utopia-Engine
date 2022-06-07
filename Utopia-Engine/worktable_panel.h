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
    explicit worktable_panel(game_controller* gm, QWidget *parent = nullptr);
    ~worktable_panel();

public slots:
    void refresh_panel();

private slots:
    void on_leave_worktable_clicked();

    void on_sleep_button_clicked();

    void on_menu_button_clicked();

private:
    Ui::worktable_panel *ui;

    void activate(int code);
    void link(int code);

};

#endif // WORKTABLE_PANEL_H
