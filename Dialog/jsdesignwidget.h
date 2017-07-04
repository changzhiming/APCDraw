#ifndef JSDESIGNWIDGET_H
#define JSDESIGNWIDGET_H

#include <QWidget>

namespace Ui {
class JSDesignWidget;
}

class JSDesignWidget : public QWidget
{
    Q_OBJECT

public:
    explicit JSDesignWidget(QStringList listName, QWidget *parent = 0);
    ~JSDesignWidget();

private:
    Ui::JSDesignWidget *ui;
};

#endif // JSDESIGNWIDGET_H
