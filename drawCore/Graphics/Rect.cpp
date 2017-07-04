#include "Rect.h"
#include "../Graphics/Graphics.h"
#include "../Item/ItemFactory.h"

TRect::TRect(QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush) :
        TGraphics(atScenePos, bounDingRect, pen, brush)
{
    mType = TItemFactory::Rect;
}

TRect::~TRect()
{}

TItem *TRect::fCopy()
{
    TRect *Rect = new TRect();

    Rect->fCopy(this);

    return Rect;
}

void TRect::fCopy(TRect *RectFrom)
{
    if(NULL == RectFrom)
    {
        return;
    }

    TGraphics::fCopy(RectFrom);
}

void TRect::fDraw(QPainter *painter)
{
    painter->drawRect(m_boundingRect);
}

/*void TRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    fBeforePaint(painter, option, widget)->drawRect(mStartX, mStartY, mStopX - mStartX, mStopY - mStartY);
}*/
