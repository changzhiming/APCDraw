
#ifndef TVALUE_TEXT_H
#define TVALUE_TEXT_H
#include <aglobal.h>
#include "../Graphics/Text.h"

class TValueText : public TText
{

    Q_PROPERTY(int mMode READ fGetMode  WRITE fSetMode)
    Q_PROPERTY(int mIntLen READ fGetIntLen  WRITE fSetIntLen)
    Q_PROPERTY(int mPointLen READ fGetPointLen   WRITE fSetPointLen)

    Q_OBJECT
public:
    TValueText(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(0, 0)), QPen pen =QPen(Qt::black),
               QBrush brush = QBrush(Qt::white));

    virtual ~TValueText();
    virtual void fDraw(QPainter *painter);
    virtual TItem *fCopy();
    virtual void fCopy(TValueText *ValueTextFrom);

    virtual void fSetValue(const double Value);

    enum
    {
        MODE_INT,
        MODE_FLOAT
    };

    inline void fSetMode(int _Mode);
    inline int fGetMode();
    inline void fSetIntLen(int _IntLen);
    inline int fGetIntLen();
    inline void fSetPointLen(int _PointLen);
    inline int fGetPointLen();

protected:
    int mMode;
    int mIntLen;
    int mPointLen;

};

inline void TValueText::fSetMode(int _Mode)
{
    mMode = _Mode;
}

inline int TValueText::fGetMode()
{
    return mMode;
}

inline void TValueText::fSetIntLen(int _IntLen)
{
    mIntLen = _IntLen;
}

inline int TValueText::fGetIntLen()
{
    return mIntLen;
}

inline void TValueText::fSetPointLen(int _PointLen)
{
    mPointLen = _PointLen;
}

inline int TValueText::fGetPointLen()
{
    return mPointLen;
}

#endif // TVALUE_TEXT_H
