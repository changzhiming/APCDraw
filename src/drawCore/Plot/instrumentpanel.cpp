#include "instrumentpanel.h"
#include <QFontMetricsF>
#include <qmath.h>
#include <QTime>
#include <QTimer>
#include "drawCore/Item/ItemFactory.h"
InstrumentPanel::InstrumentPanel(QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush) :TItemEx(atScenePos, bounDingRect, pen, brush)
{
    mType = TItemFactory::_Instrument;
    m_startAngle = 0;
    m_endAngle = 180;
    m_title = tr("时速表");
    QTimer *dataTimer= new QTimer(this);
    connect(dataTimer, QTimer::timeout, this, [this](){ fSetValue(qrand() % 100);});
    dataTimer->start(500); // Interval 0 means to refresh as fast as possible
}
TItem *InstrumentPanel::fCopy()
{
    InstrumentPanel *pieChart = new InstrumentPanel();
    pieChart->fCopy(this);
    return pieChart;
}

void InstrumentPanel::fCopy(InstrumentPanel *PieForm)
{
    TItemEx::fCopy(PieForm);
}
void InstrumentPanel::fDraw(QPainter *painter)
{
    drawCrown(painter);                                 /* 画表盘边框 */
    drawScaleNum(painter);                          /* 画刻度数值值 */
    drawScale(painter);                                 /* 画刻度线 */
    drawTitle(painter);                                     /* 画单位 */
    drawNumericValue(painter);                      /* 画数字显示 */
    drawIndicator(painter);                             /* 画表针 */
}
void InstrumentPanel::fSetValue(double value)
{
    m_Value = value;
    fUpdate();
}

void InstrumentPanel::drawCrown(QPainter *painter) //绘制表冠
{
    painter->save();

//    QLinearGradient lg1(m_boundingRect.x(), m_boundingRect.y(), m_boundingRect.width(), m_boundingRect.height());

//    lg1.setColorAt(0, Qt::white); //设置渐变的颜色和路径比例
//    lg1.setColorAt(1, Qt::gray); //只是粗略的颜色，具体的可以参考RGB颜色查询对照表

//    painter->setBrush(lg1); // 创建QBrush对象,把这个渐变对象传递进去：
//    painter->setPen(Qt::NoPen); //边框线无色

//    painter->drawRect(m_boundingRect);
    painter->setPen(m_Pen);
    painter->setBrush(m_Brush);
    int side = qMin(m_boundingRect.width() , m_boundingRect.height());
    painter->drawEllipse(m_boundingRect.x() + 25, m_boundingRect.y() + 25, side - 50, side - 50);
    painter->restore();
}
void InstrumentPanel::drawScaleNum(QPainter *painter) //绘制刻度数字
{
    painter->save();
    painter->setPen(m_Pen);

    int radius = (qMin(m_boundingRect.width() , m_boundingRect.height()) -50) / 2;
    //m_startAngle是起始角度，m_endAngle是结束角度，m_scaleMajor在一个量程中分成的刻度数
    //double startRad = (((180 - m_startAngle + 360)%360));
    int deltaRad = (m_endAngle - m_startAngle) / m_scaleMajor;

    double tmpVal, w, h, x, y, sina, cosa;
    QFontMetricsF fm(painter->font());
    Q_UNUSED(h)

    for (int i = 0; i <= m_scaleMajor; i++)
    {
        sina = sin(((180 - (m_startAngle + i*deltaRad) + 360)%360)* (3.14 / 180));
        cosa = cos(((180 - (m_startAngle + i*deltaRad) + 360)%360)* (3.14 / 180));
        tmpVal = 1.0 * i *((m_maxValue - m_minValue) / m_scaleMajor) + m_minValue;
        QString str = QString("%1").arg(tmpVal);
        w = fm.size(Qt::TextSingleLine, str).width();
        h = fm.size(Qt::TextSingleLine, str).height();

        if(cosa >= 0)
            x = m_boundingRect.x() + 25 + radius+ (radius + 15) * cosa;
        else
            x = m_boundingRect.x() + 25 + radius+ (radius + 15 + w/2) * cosa;

        y = m_boundingRect.y() + 25 +radius - (radius + 15) * sina ;

        painter->drawText(x, y, str); //函数的前两个参数是显示的坐标位置，后一个是显示的内容，是字符类型""
    }
    painter->restore();
}
void InstrumentPanel::drawScale(QPainter *painter) //绘制刻度线
{
    painter->save();

    int radius = (qMin(m_boundingRect.width() , m_boundingRect.height()) -50) / 2;
    painter->translate(m_boundingRect.x() + 25 + radius, m_boundingRect.y() + 25 + radius);   /* 坐标变换为窗体中心 */
    painter->rotate(m_startAngle);
    double steps = (m_scaleMajor * m_scaleMinor); //相乘后的值是分的份数
    double angleStep = (m_endAngle - m_startAngle) / steps; //每一个份数的角度

    // painter->setPen(m_foreground); //m_foreground是颜色的设置
    // QPen pen = painter->pen(); //第一种方法
    QPen pen ;
    pen.setColor(Qt::green); //推荐使用第二种方式
    for (int i = 0; i <= steps; i++)
    {
        if (i % m_scaleMinor == 0)//整数刻度显示加粗
        {
            pen.setWidth(2); //设置线宽
            painter->setPen(m_Pen); //使用面向对象的思想，把画笔关联上画家。通过画家画出来
            painter->drawLine(-radius - 10, 0,  -radius, 0); //两个参数应该是两个坐标值
        }
        else
        {
           pen.setWidth(0);
           painter->setPen(pen);
           painter->drawLine(-radius - 8, 0,  -radius, 0); //两个参数应该是两个坐标值
        }
        painter->rotate(angleStep);
    }
    painter->restore();
}
void InstrumentPanel::drawTitle(QPainter *painter)
{
    painter->save();
    painter->setPen(m_Pen);

    painter->setFont(m_font);
    int radius = (qMin(m_boundingRect.width() , m_boundingRect.height()) -50) / 2;
    QString str(m_title); //显示仪表的功能
    QFontMetricsF fm(m_font);
    double w = fm.size(Qt::TextSingleLine,str).width();
    painter->drawText(m_boundingRect.x() + 25 + radius - w / 2, m_boundingRect.y() + 25 + radius - 30, m_title);
    painter->restore();
}
void InstrumentPanel::drawNumericValue(QPainter *painter)
{
    QString str = QString("%1 %2").arg(m_Value, 0, 'f', m_precision).arg(m_units);
    QFontMetricsF fm(m_font);

    double w = fm.size(Qt::TextSingleLine,str).width();

    int radius = (qMin(m_boundingRect.width() , m_boundingRect.height()) -50) / 2;
    painter->drawText(m_boundingRect.x() + 25 + radius - w / 2, m_boundingRect.y() + 25 + radius + 30, str);
}
void InstrumentPanel::drawIndicator(QPainter *painter)
{
    painter->save();

    int radius = (qMin(m_boundingRect.width() , m_boundingRect.height()) -50) / 2;
    QPolygon pts;
    pts.setPoints(3, 0, -2, 0, 2, - (radius - 10), 0); /* (-2,0)/(2,0)/(0,60) *///第一个参数是 ，坐标的个数。后边的是坐标
    painter->translate(m_boundingRect.x() + 25 + radius, m_boundingRect.y() + 25 + radius);   /* 坐标变换为窗体中心 */

    painter->rotate(m_startAngle);
    double degRotate =  (m_endAngle - m_startAngle)/(m_maxValue - m_minValue)*(m_Value - m_minValue);
    //画指针
    painter->rotate(degRotate);  //顺时针旋转坐标系统
    QRadialGradient haloGradient(0, 0, radius - 10, 0, 0);  //辐射渐变
    haloGradient.setColorAt(0, QColor(60, 60, 60));
    haloGradient.setColorAt(1, QColor(160, 160, 160)); //灰
    painter->setPen(Qt::white); //定义线条文本颜色  设置线条的颜色
    painter->setBrush(haloGradient);//刷子定义形状如何填满 填充后的颜色
    painter->drawConvexPolygon(pts); //这是个重载函数，绘制多边形。

    //画中心点
    QColor niceBlue(150, 150, 200);
    QConicalGradient coneGradient(0, 0, -90.0);  //角度渐变
    coneGradient.setColorAt(0.0, Qt::darkGray);
    coneGradient.setColorAt(0.2, niceBlue);
    coneGradient.setColorAt(0.5, Qt::white);
    coneGradient.setColorAt(1.0, Qt::darkGray);
    painter->setPen(Qt::NoPen);  //没有线，填满没有边界
    painter->setBrush(coneGradient);
    painter->drawEllipse(-5, -5, 10, 10);

    painter->restore();
}
