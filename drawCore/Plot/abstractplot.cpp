#include "abstractplot.h"
#include "qcustomplot.h"

AbstractPlot::AbstractPlot(QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush) :
        TItemEx(atScenePos, bounDingRect, pen, brush)
{
     customPlot = new QCustomPlot(bounDingRect.size().toSize(), this);
     customPlot->setViewport(QRect(atScenePos.x(), atScenePos.y(), bounDingRect.width(), bounDingRect.height()));
}

void AbstractPlot::fCopy(AbstractPlot *PlotFrom)
{
    if(NULL == PlotFrom)
        return;

    TItemEx::fCopy(PlotFrom);
}
void AbstractPlot::fSetValue(double value)
{
    m_Value = value;
}

double AbstractPlot::fGetValue()
{
    return m_Value;
}

void AbstractPlot::moveBy(qreal dx, qreal dy)
{
    TItemEx::moveBy(dx, dy);
    customPlot->setViewport(QRect(0, 0, m_boundingRect.width(), m_boundingRect.height()));
}

AbstractPlot::~AbstractPlot()
{
    delete customPlot;
}
