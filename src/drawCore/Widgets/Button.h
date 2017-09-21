
#ifndef TBUTTON_H
#define TBUTTON_H

#include "Widgets.h"
///////////////////////  控件基类 /////////////////////////////////////
class TButton : public TWidgets
{
    Q_OBJECT
public:
    TButton(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(40, 40)), QPen pen =QPen(Qt::white), QBrush brush = QBrush(Qt::black));
    virtual ~TButton();

    virtual TItem *fCopy();
    virtual void fCopy(TButton *ButtonFrom);

public slots:
    void fSetFontSize(int Size);
    int fGetFontSize() const;
    void fSetText(QString Text);
    QString fGetText();
private:
    bool mPressed;

    QString mText;
    int mFontSize;
    void fDraw(QPainter *painter);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // TBUTTON_H
