#ifndef CONNECTION_DIALOG_H
#define CONNECTION_DIALOG_H

#include <QDialog>

namespace Ui {
class connection_dialog;
}

class connection_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit connection_dialog(QWidget *parent = nullptr);
    ~connection_dialog();

private:
    Ui::connection_dialog *ui;
};

#endif // CONNECTION_DIALOG_H
