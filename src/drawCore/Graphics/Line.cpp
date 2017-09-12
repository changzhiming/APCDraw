#include "Line.h"
#include "../Item/ItemFactory.h"

#include <QCursor>
#include <QGraphicsSceneEvent>

TLine::TLine(QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush) :
        TGraphics(atScenePos, bounDingRect, pen, brush)
{
    mType = TItemFactory::Line;
    m_LineDirect = LeftTopToRightBottom;

    m_start = m_boundingRect.topLeft();
    m_stop = m_boundingRect.bottomRight();
}

TLine::~TLine()
{}


TItem *TLine::fCopy()
{
    TLine *Line = new TLine();

    Line->fCopy(this);

    return Line;
}

void TLine::fCopy(TLine *LineFrom)
{
    if(NULL == LineFrom)
    {
        return;
    }

    TGraphics::fCopy(LineFrom);
}


void TLine::fDraw(QPainter *painter)
{
    painter->drawLine(m_start, m_stop);
}

void TLine::fSetLineDirect(LineDirect lineDiract)
{
    m_LineDirect = lineDiract;

    m_start = m_boundingRect.bottomRight();
    m_stop =  m_boundingRect.topLeft();
}

TLine::LineDirect TLine::fGetLineDirect()
{
    return m_LineDirect;
}
