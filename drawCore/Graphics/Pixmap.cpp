#include "Pixmap.h"
#include "../Item/ItemFactory.h"

#include <QDebug>

TPixmap::TPixmap(QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush, QString &FileDir) :
        TGraphics(atScenePos, bounDingRect, pen, brush)
{
    mType = TItemFactory::Pixmap;
    m_CurrentPixmapPath = FileDir;
}

TPixmap::~TPixmap()
{ qDebug()<<"Pixmap delete";}

TItem *TPixmap::fCopy()
{
    TPixmap *Pixmap = new TPixmap();
    Pixmap->fCopy(this);
    return Pixmap;
}

void TPixmap::fCopy(TPixmap *PixmapFrom)
{
    if(NULL == PixmapFrom) {
        return;
    }
    TGraphics::fCopy(PixmapFrom);
    this->fSetPixmapPath(PixmapFrom->fGetPixmapPath());
}
inline void TPixmap::fSetPixmapPath(const QString &FileDir)
{
    m_CurrentPixmapPath = FileDir;
}

inline QString TPixmap::fGetPixmapPath()
{
    return m_CurrentPixmapPath;
}


void TPixmap::fDraw(QPainter *painter)
{
    painter->drawPixmap(m_boundingRect.x(), m_boundingRect.y(), m_boundingRect.width(), m_boundingRect.height(), QPixmap(m_CurrentPixmapPath));
}
