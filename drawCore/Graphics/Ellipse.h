#ifndef TELLIPSE_H
#define TELLIPSE_H

#include "../Graphics/Graphics.h"

/////////////////////////////////////////////////  圆形  ////////////////////////////////////////////////////
class TEllipse : public TGraphics
{
    Q_OBJECT
public:
    TEllipse(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(40, 40)), QPen pen =QPen(Qt::black),
             QBrush brush = QBrush(QColor(Qt::white)));

    virtual ~TEllipse();
    virtual TItem *fCopy();
    virtual void fCopy(TEllipse *EllipseFrom);
    virtual void fDraw(QPainter *painter);
};

#endif // TELLIPSE_H
