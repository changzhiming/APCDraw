#ifndef TWIDGETS_H
#define TWIDGETS_H

#include "../Item/ItemEx.h"
#include "../Item/ItemFactory.h"

///////////////////////  控件基类 /////////////////////////////////////
class TWidgets : public TItemEx
{
    Q_OBJECT
public:
    TWidgets(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(0, 0)), QPen pen =QPen(QColor(0, 0, 0)), QBrush brush = QBrush(QColor(0, 0, 0)));
    virtual ~TWidgets();

    virtual void fCopy(TWidgets *WidgetsFrom);

public slots:

};

#endif // TWIDGETS_H
