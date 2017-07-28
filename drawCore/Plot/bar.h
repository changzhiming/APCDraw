#ifndef BAR_H
#define BAR_H
#include "abstractplot.h"
#include <QTimer>

class Bar : public AbstractPlot
{
    Q_OBJECT

public:
    explicit Bar(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(0, 0)), QPen pen =QPen(QColor(0, 0, 0)), QBrush brush = QBrush(QColor(0, 0, 0)));

    virtual TItem *fCopy();
    virtual void fCopy(Bar *BarForm);
    virtual void fDraw(QPainter *painter);



public slots:
    virtual void fSetValue(double value);
    void setcurrentYear(int currentYear);
private:
    QTimer dataTimer;


};

#endif // BAR_H
