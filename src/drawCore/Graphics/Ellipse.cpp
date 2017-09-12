#include "Ellipse.h"
#include "../Item/ItemFactory.h"

TEllipse::TEllipse(QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush) :
    TGraphics(atScenePos, bounDingRect, pen, brush)
{
    mType = (TItemFactory::Ellipse);
}

TEllipse::~TEllipse()
{}

TItem *TEllipse::fCopy()
{
    TEllipse *Ellipse = new TEllipse();

    Ellipse->fCopy(this);

    return Ellipse;
}

void TEllipse::fCopy(TEllipse *EllipseFrom)
{
    if(NULL == EllipseFrom)
    {
        return;
    }

    TGraphics::fCopy(EllipseFrom);
}

void TEllipse::fDraw(QPainter *painter)
{
    painter->drawEllipse(m_boundingRect);
}

/*void TEllipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    fBeforePaint(painter, option, widget)->drawEllipse(mStartX, mStartY, mStopX - mStartX, mStopY - mStartY);
}*/
