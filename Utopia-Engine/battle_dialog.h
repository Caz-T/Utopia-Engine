#ifndef BATTLE_DIALOG_H
#define BATTLE_DIALOG_H

#include <QDialog>

namespace Ui {
class battle_dialog;
}

class battle_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit battle_dialog(QWidget *parent = nullptr);
    ~battle_dialog();

private:
    Ui::battle_dialog *ui;
};

#endif // BATTLE_DIALOG_H
