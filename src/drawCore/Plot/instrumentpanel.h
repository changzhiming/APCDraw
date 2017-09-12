#ifndef INSTRUMENTPANEL_H
#define INSTRUMENTPANEL_H

#include <QObject>
#include "../Item/ItemEx.h"
#include <aglobal.h>
#include <QWidget>
class InstrumentPanel : public TItemEx
{
    Q_OBJECT
public:
    explicit InstrumentPanel(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(0, 0)), QPen pen =QPen(QColor(0, 0, 0)), QBrush brush = QBrush(QColor(100, 100, 0)));

    virtual TItem *fCopy();
protected:
    virtual void fCopy(InstrumentPanel *PieForm);
    virtual void fDraw(QPainter *painter); 
public slots:
    void fSetValue(double value);
private:
    void drawCrown(QPainter *painter);
    void drawScaleNum(QPainter *painter);
    void drawScale(QPainter *painter);
    void drawTitle(QPainter *painter);
    void drawNumericValue(QPainter *painter);
    void drawIndicator(QPainter *painter);
private:
    double m_Value = 0, m_precision = 3;
    int m_startAngle, m_endAngle;
    int m_scaleMajor = 10, m_scaleMinor = 10;
    double m_maxValue = 100, m_minValue = 0;
    QString m_title , m_units = "km/h";
    QFont m_font;
};
#endif // INSTRUMENTPANEL_H
