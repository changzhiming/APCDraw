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


void TPixmap::fDraw(QPainter *painter)
{
    painter->drawPixmap(m_boundingRect.toRect(), QPixmap(m_CurrentPixmapPath));
}
