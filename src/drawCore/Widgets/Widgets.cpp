#include "Widgets.h"

TWidgets::TWidgets(QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush) :
    TItemEx(atScenePos, bounDingRect, pen, brush)
{}

TWidgets::~TWidgets()
{}


void TWidgets::fCopy(TWidgets *WidgetsFrom)
{
    if(NULL == WidgetsFrom){
        return;
    }

    TItemEx::fCopy(WidgetsFrom);
}


