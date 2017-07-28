#ifndef GRAPH_H
#define GRAPH_H

#include <QTimer>
#include "abstractplot.h"

class Graph : public AbstractPlot
{
    Q_OBJECT
    enum AXIS{
        X1,
        Y1,
        X2,
        Y2,
    };

public:
    explicit Graph(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(0, 0)), QPen pen =QPen(QColor(0, 0, 0)), QBrush brush = QBrush(QColor(0, 0, 0)));

    virtual ~Graph();

    virtual TItem *fCopy();
    virtual void fCopy(Graph *GraphForm);
    virtual void fDraw(QPainter *painter);

    void addGraph();
    int graphCount();
    void addData(int index, QVector<double> x, QVector<double> y);
    void setName(int index, QString name);

    void setRange(AXIS axis, double lower, double upper);
    void moveRange(AXIS axis, int diff);
    void setLabel(AXIS axis, QString label);
    void AsetVisible(AXIS axis, bool show);

    void setNumberPrecision(AXIS axis, int precision);
    void setTickCount(AXIS axis, int tick);

public slots:
    virtual void fSetValue(double value);

private:
    QStringList m_GraphName;
    QTimer dataTimer;
};

#endif // GRAPH_H
