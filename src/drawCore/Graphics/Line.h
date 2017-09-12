#ifndef TLINE_H
#define TLINE_H

#include "../Graphics/Graphics.h"

/////////////////////////////////////////////////  直线  ////////////////////////////////////////////////////
class TLine : public TGraphics
{
    Q_OBJECT
public:
    TLine(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(40, 40)), QPen pen =QPen(Qt::black),
          QBrush brush = QBrush(QColor(Qt::white)));
    virtual ~TLine();

    virtual TItem *fCopy();
    virtual void fCopy(TLine *LineFrom);
    virtual void fDraw(QPainter *painter);

    enum LineDirect
    {
        LeftTopToRightBottom = 1,
        RightBottomToLeftTop,
    };
    Q_ENUM(LineDirect)

    void fSetLineDirect(LineDirect lineDiract);
    LineDirect fGetLineDirect();

protected:
    LineDirect m_LineDirect;

private:
    QPointF m_start, m_stop;
};

#endif // TLINE_H
