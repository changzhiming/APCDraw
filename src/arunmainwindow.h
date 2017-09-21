#ifndef ARUNMAINWINDOW_H
#define ARUNMAINWINDOW_H

#include <QWidget>

namespace Ui {
class ARunMainWindow;
}

class ARunMainWindow : public QWidget
{
    Q_OBJECT

public:
    static ARunMainWindow *getInstance();
    ~ARunMainWindow();

private:
    explicit ARunMainWindow(QWidget *parent = 0);
    Ui::ARunMainWindow *ui;
};

#endif // ARUNMAINWINDOW_H
