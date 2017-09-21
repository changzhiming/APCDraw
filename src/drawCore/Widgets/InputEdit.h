#ifndef TINPUT_EDIT_H
#define TINPUT_EDIT_H

#include "Widgets.h"

///////////////////////  控件基类 /////////////////////////////////////
class TInputEdit : public TWidgets
{
    Q_OBJECT
public:
    TInputEdit(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(40, 40)), QPen pen =QPen(Qt::white), QBrush brush = QBrush(Qt::black));
    virtual ~TInputEdit();

    virtual TItem *fCopy();
    virtual void fCopy(TInputEdit *InputEditFrom);
protected:
    virtual void keyReleaseEvent(QKeyEvent *event);
    virtual void focusInEvent(QFocusEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);
    virtual void inputMethodEvent(QInputMethodEvent *event);
    QVariant inputMethodQuery(Qt::InputMethodQuery query) const;
    virtual void fDraw(QPainter *painter);
public slots:

    void fSetText(const QString &Text);
    QString fGetText();

Q_SIGNALS:
    void mTextChange(QString Text);

private:
    QString mText;
    bool m_showCursor = false;
    QTimer *timer = nullptr;
};

#endif // TINPUT_EDIT_H
