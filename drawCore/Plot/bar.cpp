#include "bar.h"
#include "qcustomplot.h"

Bar::Bar(QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush) :AbstractPlot(atScenePos, bounDingRect, pen, brush)
{
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    customPlot->setBackground(QBrush(gradient));

    // create empty bar chart objects:
    QCPBars *regen = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    regen->setWidth(3600*24*12);
    regen->setAntialiased(false); // gives more crisp, pixel aligned bar borders
    regen->setStackingGap(1);
    // set names and colors:
    regen->setName("柱形图");
    regen->setPen(QPen(QColor(111, 9, 176).lighter(170)));
    regen->setBrush(QColor(111, 9, 176));

    // prepare x axis with country labels:

    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("yyyy:MM");
    dateTicker->setTickCount(12);
    customPlot->xAxis->setTicker(dateTicker);
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 9));
    customPlot->xAxis->setSubTicks(false);
    customPlot->xAxis->setTickLength(0, 4);

    customPlot->xAxis->setBasePen(QPen(Qt::white));
    customPlot->xAxis->setTickPen(QPen(Qt::white));
    customPlot->xAxis->grid()->setVisible(true);
    customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot->xAxis->setTickLabelColor(Qt::white);
    customPlot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    customPlot->yAxis->setRange(0, 12.1);
    customPlot->yAxis->setPadding(5); // a bit more space to the left border
    customPlot->yAxis->setLabel("2017年参数");
    customPlot->yAxis->setBasePen(QPen(Qt::white));
    customPlot->yAxis->setTickPen(QPen(Qt::white));
    customPlot->yAxis->setSubTickPen(QPen(Qt::white));
    customPlot->yAxis->grid()->setSubGridVisible(true);
    customPlot->yAxis->setTickLabelColor(Qt::white);
    customPlot->yAxis->setLabelColor(Qt::white);
    customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));


    // setup legend:
    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    customPlot->legend->setBorderPen(Qt::NoPen);

    double now =  QDateTime::currentDateTime().toTime_t();
    double last = QDateTime::currentDateTime().addYears(-1).toTime_t();
    customPlot->xAxis->setRange(last, now + 30*3600*24);



    connect(&dataTimer, &QTimer::timeout, this, [=](){ fSetValue(1);});
    dataTimer.start(100); // Interval 0 means to refresh as fast as possible
}
TItem *Bar::fCopy()
{
    Bar *bar = new Bar();
    bar->fCopy(this);
    return bar;
}

void Bar::fCopy(Bar *BarForm)
{
    if(nullptr == BarForm)
        return;
    AbstractPlot::fCopy(BarForm);

}
void Bar::fDraw(QPainter *painter)
{
    painter->drawPixmap(m_boundingRect.toRect(), customPlot->toPixmap(m_boundingRect.width(), m_boundingRect.height(), painter->transform().m11()));
}
void Bar::setcurrentYear(int currentYear)
{

}

void Bar::fSetValue(double value)
{
    Q_UNUSED(value)
    if(!(QDateTime::currentDateTime().date().day() == 1) || !(QDateTime::currentDateTime().time() == QTime(8, 0, 0)))
        return;

    double last =  QDateTime::currentDateTime().toTime_t();
    double now = QDateTime::currentDateTime().addYears(-1).toTime_t();

    QCPAbstractPlottable * plottable = customPlot->plottable(0);

    if(plottable) {
        QCPBars *regen = static_cast<QCPBars *>(plottable);
        if(regen) {
            regen->addData(QDateTime::currentDateTime().toTime_t(), value);

            if(value < customPlot->yAxis->range().lower) {
                customPlot->yAxis->setRange(value,  customPlot->yAxis->range().upper);
            } else if(value > customPlot->yAxis->range().upper) {
                customPlot->yAxis->setRange(customPlot->yAxis->range().lower, value);
            }
            bool foundRange;
            QCPRange keyRange = regen->data()->keyRange(foundRange);
            qDebug()<<regen->dataCount();

            if(keyRange.size() > (last - now))
                regen->data()->removeBefore(keyRange.upper - (last - now));
            fUpdate();
        }
    }
}
