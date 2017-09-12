#ifndef ABSTRACTPLOT_H
#define ABSTRACTPLOT_H

#include "../Item/ItemEx.h"
#include <aglobal.h>

class QCustomPlot;
class AbstractPlot : public TItemEx
{
    Q_OBJECT
public:
    AbstractPlot(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(0, 0)), QPen pen =QPen(QColor(0, 0, 0)), QBrush brush = QBrush(QColor(0, 0, 0)));
    virtual ~AbstractPlot();

    virtual void fCopy(AbstractPlot *PlotFrom);
    void moveBy(qreal dx, qreal dy);

public slots:
    virtual void fSetValue(double value);
    virtual double fGetValue();

protected:
    QCustomPlot *customPlot;
    double m_Value;
};

#endif // ABSTRACTPLOT_H
