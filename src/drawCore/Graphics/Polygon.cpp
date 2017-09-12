#include "Polygon.h"
#include "../Item/ItemFactory.h"

TPolygon::TPolygon(QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush) :
        TGraphics(atScenePos, bounDingRect, pen, brush)
{
    mType = TItemFactory::Polygon;

    TItem::fSetMoveAble(true);
    TItem::fSetDragAble(false);
}

TPolygon::~TPolygon()
{}

TItem *TPolygon::fCopy()
{
    TPolygon *Polygon = new TPolygon();

    Polygon->fCopy(this);

    return Polygon;
}

void TPolygon::fCopy(TPolygon *PolygonFrom)
{
    if(NULL == PolygonFrom)
    {
        return;
    }

    TGraphics::fCopy(PolygonFrom);

    this->fSetPolygonPoints(PolygonFrom->fGetPolygonPoints());
}

void TPolygon::UpdateData(double X, double Y)
{
    double dx = (X - m_boundingRect.x()) / 2;
    double dy = (Y - m_boundingRect.y()) / 2;

    QPolygonF PolygonPoints;

    foreach(QPointF Point, mPolygonPoints)
    {
        PolygonPoints.push_back(QPointF((Point.x() + dx), (Point.y() + dy)));
    }

    fSetPolygonPoints(PolygonPoints);
}

void TPolygon::fSetPolygonPoints(const QPolygonF &PolygonPoints)
{
    mPolygonPoints = PolygonPoints;
}

QPolygonF TPolygon::fGetPolygonPoints() const
{
    QPolygonF SceneF;

    for(int i = 0; i < mPolygonPoints.count(); ++i)
    {
        SceneF.push_back(mapToScene(mPolygonPoints.at(i)));
    }

    return SceneF;
}

bool TPolygon::fSetDragAble(bool Able)
{
    Q_UNUSED(Able);
    return false;
}

void TPolygon::fDraw(QPainter *painter)
{
    painter->drawPolygon(mPolygonPoints);
}

/*void TPolygon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    fBeforePaint(painter, option, widget)->drawPolygon(mPolygonPoints);
}*/

