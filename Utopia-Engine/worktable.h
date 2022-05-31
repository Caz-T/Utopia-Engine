#ifndef WORKTABLE_H
#define WORKTABLE_H

#include <QWidget>

namespace Ui {
class worktable;
}

class worktable : public QWidget
{
    Q_OBJECT

public:
    explicit worktable(QWidget *parent = nullptr);
    ~worktable();

private:
    Ui::worktable *ui;
};

#endif // WORKTABLE_H
