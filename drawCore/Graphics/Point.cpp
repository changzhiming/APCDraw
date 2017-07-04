#include "Point.h"
#include "../Item/ItemFactory.h"

TPoint::TPoint(QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush) :
        TGraphics(atScenePos, bounDingRect, pen, brush)
{
    mType = TItemFactory::Point;
}

TPoint::~TPoint()
{}

TItem *TPoint::fCopy()
{
    TPoint *Point = new TPoint();

    Point->fCopy(this);

    return Point;
}

void TPoint::fCopy(TPoint *PointFrom)
{
    if(NULL == PointFrom)
    {
        return;
    }

    TGraphics::fCopy(PointFrom);
}


void TPoint::fDraw(QPainter *painter)
{
    painter->drawPoint(m_boundingRect.x(), m_boundingRect.y());
}
