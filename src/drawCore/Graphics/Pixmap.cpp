#include "Pixmap.h"
#include "../Item/ItemFactory.h"

#include <QDebug>

TPixmap::TPixmap(QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush, QString FileDir) :
        TGraphics(atScenePos, bounDingRect, pen, brush)
{
    mType = TItemFactory::Pixmap;
    m_CurrentPixmapPath = FileDir;
}

TPixmap::~TPixmap()
{ }

TItem *TPixmap::fCopy()
{
    TPixmap *Pixmap = new TPixmap();
    Pixmap->fCopy(this);
    return Pixmap;
}

void TPixmap::fCopy(TPixmap *PixmapFrom)
{
    TGraphics::fCopy(PixmapFrom);
    fSetPixmapPath(PixmapFrom->fGetPixmapPath());
}
QDataStream & TPixmap::serialize(QDataStream &out)
{
    out<<mType<<mRotateAngle<<m_MoveEnable<<m_SelectEnable<<m_DragEnable<<
         m_FocusEnable<<m_Pen<<m_Brush<<m_boundingRect<<m_MouseHand<<pos();
    return out;
}

QDataStream & TPixmap::desserialize(QDataStream &in)
{
    in>>mType>>mRotateAngle>>m_MoveEnable>>m_SelectEnable>>m_DragEnable>>
         m_FocusEnable>>m_Pen>>m_Brush>>m_boundingRect>>m_MouseHand;
    QPointF posPoint;
    in>>posPoint;
    setPos(posPoint);

    fSetMoveAble(m_MoveEnable);
    fSetSelectAble(m_SelectEnable);
    fSetDragAble(m_DragEnable);
    return in;
}

void TPixmap::fDraw(QPainter *painter)
{
    painter->drawPixmap(m_boundingRect.toRect(), QPixmap(m_CurrentPixmapPath));
}
