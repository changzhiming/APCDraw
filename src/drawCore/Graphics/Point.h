#ifndef TPOINT_H
#define TPOINT_H
#include "../Graphics/Graphics.h"

/////////////////////////////////////////////////  点  /////////////////////////////////////////////////////
class TPoint : public TGraphics
{
    Q_OBJECT
public:
    TPoint(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(40, 40)), QPen pen =QPen(Qt::black),
           QBrush brush = QBrush(Qt::white));

    virtual ~TPoint();
    virtual TItem *fCopy();
    virtual void fCopy(TPoint *PointFrom);
    virtual void fDraw(QPainter *painter);
};

#endif // TPOINT_H
