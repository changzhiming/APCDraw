#include "ItemEx.h"
#include <QMenu>
#include "QHBoxLayout"
#include <QDialog>
#include <QInputDialog>


TItemEx::TItemEx(QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush) :
    TItem(atScenePos, bounDingRect, pen, brush)
{}

TItemEx::~TItemEx()
{}

void TItemEx::fCopy(TItemEx *ItemExFrom)
{
    TItem::fCopy(ItemExFrom);

    this->setToolTip(ItemExFrom->toolTip());
    this->fSetMousePressJS(ItemExFrom->fGetMousePressJS());

    this->fSetLinkScene(ItemExFrom->fGetLinkScene());
    this->fSetDisconnect(ItemExFrom->fGetDisconnect());
}
