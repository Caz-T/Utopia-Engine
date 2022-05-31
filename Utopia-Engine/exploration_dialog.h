#ifndef EXPLORATION_DIALOG_H
#define EXPLORATION_DIALOG_H

#include <QDialog>

namespace Ui {
class exploration_dialog;
}

class exploration_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit exploration_dialog(QWidget *parent = nullptr);
    ~exploration_dialog();

private:
    Ui::exploration_dialog *ui;
};

#endif // EXPLORATION_DIALOG_H
