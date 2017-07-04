#ifndef TRECT_H
#define TRECT_H

#include "../Graphics/Graphics.h"

/////////////////////////////////////////////////  矩形  /////////////////////////////////////////////////////
class TRect : public TGraphics
{
    Q_OBJECT
public:
    TRect(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(40, 40)), QPen pen =QPen(Qt::black),
          QBrush brush = QBrush(Qt::white));

    virtual ~TRect();

    virtual TItem *fCopy();
    virtual void fCopy(TRect *RectFrom);
    virtual void fDraw(QPainter *painter);
};

#endif // TRECT_H
