#include "Graphics.h"
#include <QDebug>

TGraphics::TGraphics(QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush) :
        TItemEx(atScenePos, bounDingRect, pen, brush)
{}

void TGraphics::fCopy(TGraphics *GraphicsFrom)
{
    TItemEx::fCopy(GraphicsFrom);
}

TGraphics::~TGraphics()
{}

void TGraphics::fSetValue(const double Value)
{
    m_Value = Value;
}
double TGraphics::fGetValue() const
{
    return m_Value;
}

