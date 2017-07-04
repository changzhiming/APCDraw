#ifndef TMETER_H
#define TMETER_H

#include "../Graphics/Graphics.h"
#include <aglobal.h>
class TMeter : public TGraphics
{
    Q_OBJECT
public:
    TMeter(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(40, 40)), QPen pen =QPen(Qt::black),
           QBrush brush = QBrush(Qt::white));

    virtual ~TMeter();

    enum
    {
        MODE_CLOSCK_WISE,       // 顺时针
        MODE_COUNTER_WISE       // 逆时针
    };

    virtual TItem *fCopy();
    virtual void fCopy(TMeter *MeterFrom);

    void fSetMode(int Mode);
    int fGetMode();
    void fSetScaleSum(int Sum);
    int fGetScaleSum();
    void fSetStartAngle(double Angle);
    double fGetStartAngle();
    void fSetStepAngle(double Angle);
    double fGetStepAngle();
    void fSetStartValue(double Value);
    double fGetStartValue();
    void fSetStepValue(double Value);
    double fGetStepValue();
    void fSetPointerColor(const QColor &Color);
    QColor fGetPointerColor();

private:
    int mMode;              // 顺时针还是逆时针
    int mScaleSum;          // 刻度总数
    double mStartAngle;     // 起始角度
    double mStepAngle;      // 阶梯角度
    double mStartValue;     // 起始值
    double mStepValue;      // 阶梯值
    QColor mPointerColor;   // 指针颜色

    void fDraw(QPainter *painter);
};

#endif // TMETER_H
