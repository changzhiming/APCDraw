#include "graph.h"
#include "qcustomplot.h"
#include "drawCore/Item/ItemFactory.h"
Graph::Graph(QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush) :AbstractPlot(atScenePos, bounDingRect, pen, brush)
{
    mType = TItemFactory::Graph;

    customPlot->addGraph(); // blue line
    customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    customPlot->graph()->setName("实时曲线");
    customPlot->legend->setVisible(true);
    customPlot->legend->setFont(QFont("Helvetica", 7));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    customPlot->xAxis->setTicker(timeTicker);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->yAxis->setRange(0, 0);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
    customPlot->graph()->rescaleAxes(true);

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, &QTimer::timeout, this, [=](){ fSetValue(1);});
    dataTimer.start(100); // Interval 0 means to refresh as fast as possible
}
Graph::~Graph()
{
}

TItem *Graph::fCopy()
{
    Graph *Graphs = new Graph();
    Graphs->fCopy(this);
    return Graphs;
}

void Graph::fCopy(Graph *GraphForm)
{
    if(nullptr == GraphForm)
        return;
    AbstractPlot::fCopy(GraphForm);

}
/*!
 * \brief Graph::addGraph  增加一条曲线
 */
void Graph::addGraph()
{
    customPlot->addGraph();
}

int Graph::graphCount()
{
    return customPlot->graphCount();
}

void Graph::addData(int index, QVector<double> x, QVector<double> y)
{
    customPlot->graph(index)->addData(x, y);
}
void Graph::setName(int index, QString name)
{
    customPlot->graph(index)->setName(name);
    m_GraphName.append(name);
}
void Graph::setRange(AXIS axis, double lower, double upper)
{

}

void Graph::moveRange(AXIS axis, int diff)
{

}

void Graph::setLabel(AXIS axis, QString label)
{

}

void Graph::AsetVisible(AXIS axis, bool show)
{

}
void Graph::fSetValue(double value)
{  
    AbstractPlot::fSetValue(value);

    double key = QTime::currentTime().msecsSinceStartOfDay()/1000.0; // time elapsed since start of demo, in seconds
    value = key/10000;

      // add data to lines:
    customPlot->graph(0)->addData(key, qCos(value)+qrand()/(double)RAND_MAX*0.5*qSin(value/0.4364));

    // make key axis range scroll with the data (at a constant range size of 8):
    customPlot->xAxis->setRange(key, 10, Qt::AlignRight);
    if(value < customPlot->yAxis->range().lower) {
        customPlot->yAxis->setRange(value,  customPlot->yAxis->range().upper);
    } else if(value > customPlot->yAxis->range().upper) {
        customPlot->yAxis->setRange(customPlot->yAxis->range().lower, value);
    }
    bool foundRange;
    QCPRange keyRange = customPlot->graph(0)->data()->keyRange(foundRange);

    if(keyRange.size() > 10)
        customPlot->graph(0)->data()->removeBefore(keyRange.upper - 10);

    fUpdate();
}

void Graph::fDraw(QPainter *painter)
{
    painter->drawPixmap(m_boundingRect.toRect(), customPlot->toPixmap(m_boundingRect.width(), m_boundingRect.height(), painter->transform().m11()));
}
