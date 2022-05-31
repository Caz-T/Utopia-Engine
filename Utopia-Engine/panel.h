#ifndef PANEL_H
#define PANEL_H

#include <QWidget>

class panel : public QWidget
{
    Q_OBJECT
public:
    explicit panel(QWidget *parent = nullptr);

public slots:
    // we require all panels' refreshing and closing to be slots
    virtual void refresh_panel() = 0; // This is to be triggered whenever the subclass is shown or refreshed.
    virtual void close_panel(); // This is to be triggered whenever the subclass is to be hidden.

signals:

};

#endif // PANEL_H
