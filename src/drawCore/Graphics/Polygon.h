
#ifndef TPOLYGON_H
#define TPOLYGON_H

#include "../Graphics/Graphics.h"

/////////////////////////////////////////////////  多边形  /////////////////////////////////////////////////////
class TPolygon : public TGraphics
{
    Q_OBJECT
public:
    TPolygon(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(40, 40)), QPen pen =QPen(Qt::black),
             QBrush brush = QBrush(Qt::white));

    virtual ~TPolygon();

    virtual TItem *fCopy();
    virtual void fCopy(TPolygon *PolygonFrom);

    bool fSetDragAble(bool Able);

    void fSetPolygonPoints(const QPolygonF &PolygonPoints);
    QPolygonF fGetPolygonPoints() const;

private:
    QPolygonF mPolygonPoints;
    void fDraw(QPainter *painter);

    void UpdateData(double X, double Y);
};
#endif // TPOLYGON_H
