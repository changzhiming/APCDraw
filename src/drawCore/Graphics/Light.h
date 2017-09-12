#ifndef TLIGHT_H
#define TLIGHT_H

#include "../Graphics/Graphics.h"

class TLight : public TGraphics
{
    Q_OBJECT
public:
    TLight(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(40, 40)), QPen pen =QPen(Qt::black),
           QBrush brush = QBrush(Qt::white));

    virtual ~TLight();
    virtual TItem *fCopy();
    virtual void fCopy(TLight *LightFrom);
    virtual void fDraw(QPainter *painter);
};

#endif // TLIGHT_H
