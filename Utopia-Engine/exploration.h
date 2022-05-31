#ifndef EXPLORATION_H
#define EXPLORATION_H

#include <QWidget>

namespace Ui {
class exploration;
}

class exploration : public QWidget
{
    Q_OBJECT

public:
    explicit exploration(QWidget *parent = nullptr);
    ~exploration();

private:
    Ui::exploration *ui;
};

#endif // EXPLORATION_H
