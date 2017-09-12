#ifndef TGRAPHICS_H
#define TGRAPHICS_H

#include "../Item/ItemEx.h"
#include <aglobal.h>
class QVariant;

///////////////////////  图形基类 /////////////////////////////////////
class TGraphics : public TItemEx
{
    Q_OBJECT
public:
    TGraphics(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(0, 0)), QPen pen =QPen(QColor(0, 0, 0)), QBrush brush = QBrush(QColor(0, 0, 0)));
    virtual ~TGraphics();
    virtual void fCopy(TGraphics *GraphicsFrom);

public slots:
    virtual void fSetValue(const double Value);                  // 设定值，并运行值脚本，初始化自身外形,联动脚本
    virtual double fGetValue() const;

protected:
    int m_Value = 0;

};

#endif // TGRAPHICS_H
