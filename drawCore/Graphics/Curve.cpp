#include "Curve.h"
#include "../Item/ItemFactory.h"

#include <QTimer>

TCurve::TCurve(QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush) :
        TGraphics(atScenePos, bounDingRect, pen, brush)
{
    mType = TItemFactory::Curve;

    mDataSum = 1024;
    mInterval = 1;
    mTime = 5;

    mTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(fUpdate()));
    mTimer->start(mTime);
}

TCurve::~TCurve()
{}

TItem *TCurve::fCopy()
{
    TCurve *Curve = new TCurve();

    Curve->fCopy(this);

    return Curve;
}

void TCurve::fCopy(TCurve *CurveFrom)
{
    if(NULL == CurveFrom)
    {
        return;
    }

    TGraphics::fCopy(CurveFrom);

    this->fSetDataSum(CurveFrom->fGetDataSum());
    this->fSetInterval(CurveFrom->fGetInterval());
    this->fSetTime(CurveFrom->fGetTime());
}

void TCurve::fSetDataSum(int DataSum)
{
    mDataSum = DataSum;
}

int TCurve::fGetDataSum()
{
    return mDataSum;
}

void TCurve::fSetInterval(int Interval)
{
    mInterval = Interval;
}

int TCurve::fGetInterval()
{
    return mInterval;
}

void TCurve::fSetTime(int Time)
{
    mTime = Time;

    if(mTimer->isActive())
    {
        mTimer->stop();
    }

    mTimer->start(mTime);
}

int TCurve::fGetTime()
{
    return mTime;
}

void TCurve::fDraw(QPainter *painter)
{
    if(mDataSum <= 0)
    {
        return;
    }

    if(mDataList.isEmpty())
    {
        return;
    }

}

void TCurve::fSetValue(const double Value)
{
    m_Value = Value;
}
