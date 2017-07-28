#ifndef JSDESIGNWIDGET_H
#define JSDESIGNWIDGET_H

#include <QWidget>

class TItemEx;
class QTextEdit;
class JSDesignWidget : public QWidget
{
    Q_OBJECT

public:
    explicit JSDesignWidget(TItemEx *item, QWidget *parent = 0);
    ~JSDesignWidget();

protected:
    virtual void closeEvent(QCloseEvent *event);

private:
    TItemEx *m_Item;
    QTextEdit *mousePressTextEdit;
};

#endif // JSDESIGNWIDGET_H
