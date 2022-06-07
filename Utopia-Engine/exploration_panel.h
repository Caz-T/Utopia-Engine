#ifndef EXPLORATION_PANEL_H
#define EXPLORATION_PANEL_H

#include <QWidget>
#include "panel.h"
#include "exploration_dialog.h"
#include "battle_dialog.h"

namespace Ui {
class exploration_panel;
}

class exploration_panel : public panel
{
    Q_OBJECT

public:
    explicit exploration_panel(game_controller* gm, QWidget *parent = nullptr);
    ~exploration_panel();

public slots:
    void refresh_panel();

private slots:
    void on_peak_button_clicked();
    void on_wilds_button_clicked();
    void on_marshes_button_clicked();
    void on_canyon_button_clicked();
    void on_city_button_clicked();
    void on_maw_button_clicked();

    void on_use_seal_clicked();


    void on_return_to_worktable_clicked();

    void on_camp_button_clicked();

    void on_menu_button_clicked();

    void on_recharge_tool_clicked();

private:
    Ui::exploration_panel *ui;

    void explore(int id); // candy!

};

#endif // EXPLORATION_PANEL_H
