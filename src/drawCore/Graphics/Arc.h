#ifndef TARC_H
#define TARC_H

#include "../Graphics/Graphics.h"

/////////////////////////////////////////////////  圆弧  /////////////////////////////////////////////////////
class TArc : public TGraphics
{

    Q_PROPERTY(int mMode READ fGetMode  WRITE fSetMode)
    Q_PROPERTY(bool mStartAngle READ fGetStartAngle  WRITE fSetStartAngle)
    Q_PROPERTY(bool mCoverAngle READ fGetCoverAngle  WRITE fSetCoverAngle)

    Q_OBJECT
public:
    TArc(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(40, 40)), QPen pen =QPen(Qt::black),
         QBrush brush = QBrush(QColor(Qt::white)));

    virtual ~TArc();
    virtual TItem *fCopy();
    virtual void fCopy(TArc *ArcFrom);

    virtual void fDraw(QPainter *painter);
    enum
    {
        MODE_MIN = -1,
        MODE_PIE = 0,
        MODE_ARC,
        MODE_CHORD,
        MODE_MAX
    };

    bool fSetMode(const int Mode);
    int fGetMode() const;
    void fSetStartAngle(const double StartAngle);
    double fGetStartAngle() const;
    void fSetCoverAngle(const double CoverAngle);
    double fGetCoverAngle() const;

protected:
    int mMode;
    double mStartAngle;
    double mCoverAngle;  
};
#endif // TARC_H
