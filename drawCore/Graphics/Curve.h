#ifndef TCURVE_H
#define TCURVE_H

#include "../Graphics/Graphics.h"
#include <aglobal.h>

class TDataPoint
{
public:
    double mValue;  // 实时值
    double mValid;  // 有效值
};

/////////////////////////////////////////////////  实时曲线  /////////////////////////////////////////////////////
class TCurve : public TGraphics
{
    Q_OBJECT
public:
    TCurve(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(40, 40)), QPen pen =QPen(Qt::black),
           QBrush brush = QBrush(QColor(Qt::white)));

    virtual ~TCurve();

    virtual TItem *fCopy();
    virtual void fCopy(TCurve *CurveFrom);
    virtual void fDraw(QPainter *painter);
    virtual void fSetValue(const double Value);

    void fSetDataSum(int DataSum);
    int fGetDataSum();
    void fSetInterval(int Interval);
    int fGetInterval();
    void fSetTime(int Time);
    int fGetTime();

private:
    int mDataSum;               // 点数
    int mInterval;           // 间隔，隔几个数 取一个数显示
    QList<TDataPoint *> mDataList;

    QTimer *mTimer;
    int mTime;                  // 刷新间隔ms   
};

#endif // TCURVE_H
