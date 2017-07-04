#include "ValueText.h"
#include "../Item/ItemFactory.h"

TValueText::TValueText(QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush) :
        TText(atScenePos, bounDingRect, pen, brush)
{   
    mType = TItemFactory::ValueText;

    mMode = MODE_FLOAT;
    mIntLen = 0;
    mPointLen = 6;
}

TValueText::~TValueText()
{}

TItem *TValueText::fCopy()
{
    TValueText *ValueText = new TValueText();

    ValueText->fCopy(this);

    return ValueText;
}

void TValueText::fCopy(TValueText *ValueTextFrom)
{
    if(NULL == ValueTextFrom)
    {
        return;
    }
    TText::fCopy(ValueTextFrom);
    this->fSetMode(ValueTextFrom->fGetMode());
    this->fSetIntLen(ValueTextFrom->fGetIntLen());
    this->fSetPointLen(ValueTextFrom->fGetPointLen());
}

void TValueText::fSetValue(const double Value)
{

    TGraphics::fSetValue(Value);
    switch(mMode)
    {
    case MODE_INT:
        fSetText(QString::number(m_Value));
        break;

    case MODE_FLOAT:
        fSetText(QString::number(m_Value, 'f', mPointLen));
        break;

    default:
        break;
    }
    TItem::fUpdate();
}

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

void TValueText::fDraw(QPainter *painter)
{
    QFont Font;
    Font.setFamily(mFontFamily);
    Font.setPointSize(mFontSize);
    Font.setBold(mFontBlod);
    Font.setItalic(mFontItalic);
    Font.setUnderline(mFontUnderLine);
    Font.setStrikeOut(mFontStrikeOut);
    Font.setLetterSpacing(QFont::AbsoluteSpacing, mFontSpacing);
    painter->setFont(Font);

    painter->drawText(m_boundingRect, Qt::AlignCenter, mText);
}
