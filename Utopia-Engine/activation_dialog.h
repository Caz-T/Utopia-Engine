#ifndef ACTIVATION_DIALOG_H
#define ACTIVATION_DIALOG_H

#include <QDialog>

namespace Ui {
class activation_dialog;
}

class activation_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit activation_dialog(QWidget *parent = nullptr);
    ~activation_dialog();

private:
    Ui::activation_dialog *ui;
};

#endif // ACTIVATION_DIALOG_H
