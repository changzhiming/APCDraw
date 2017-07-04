#include "Text.h"
#include "../Item/ItemFactory.h"
#include <QDebug>

TText::TText(QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush) :
        TGraphics(atScenePos, bounDingRect, pen, brush)
{
    mType = TItemFactory::Text;

    mFontFamily = tr("宋体");
    mFontSize = 12;
    mFontBlod = false;
    mFontItalic = false;
    mFontUnderLine = false;
    mFontStrikeOut = false;
    mFontSpacing = 0;
    mText = QString("text");

}

TText::~TText()
{}

TItem *TText::fCopy()
{
    TText *Text = new TText();

    Text->fCopy(this);

    return Text;
}

void TText::fCopy(TText *TextFrom)
{
    if(NULL == TextFrom)
    {
        return;
    }

    TGraphics::fCopy(TextFrom);

    this->fSetText(TextFrom->fGetText());
    this->fSetFontFamily(TextFrom->fGetFontFamily());
    this->fSetFontSize(TextFrom->fGetFontSize());
    this->fSetFontBlod(TextFrom->fGetFontBlod());
    this->fSetFontItalic(TextFrom->fGetFontItalic());
    this->fSetFontSpacing(TextFrom->fGetFontSpacing());
    this->fSetFontUnderLine(TextFrom->fGetFontUnderLine());
    this->fSetFontStrikeOut(TextFrom->fGetFontStrikeOut());
}

void TText::fSetText(const QString &Text)
{
    mText = Text;
    TItem::fUpdate();
}

QString TText::fGetText() const
{
    return mText;
}

void TText::fSetFontFamily(const QString &Family)
{
    mFontFamily = Family;
}

QString TText::fGetFontFamily() const
{
    return mFontFamily;
}

void TText::fSetFontSize(int Size)
{
    mFontSize = Size;
}

int TText::fGetFontSize() const
{
    return mFontSize;
}

void TText::fSetFontBlod(bool Blod)
{
    mFontBlod = Blod;
}

bool TText::fGetFontBlod() const
{
    return mFontBlod;
}

void TText::fSetFontItalic(bool Italic)
{
    mFontItalic = Italic;
}

bool TText::fGetFontItalic() const
{
    return mFontItalic;
}

void TText::fSetFontUnderLine(bool UnderLine)
{
    mFontUnderLine = UnderLine;
}

bool TText::fGetFontUnderLine() const
{
    return mFontUnderLine;
}

void TText::fSetFontStrikeOut(bool StrikeOut)
{
    mFontStrikeOut = StrikeOut;
}

bool TText::fGetFontStrikeOut() const
{
    return mFontStrikeOut;
}

void TText::fSetFontSpacing(int Spacing)
{
    mFontSpacing = Spacing;
}

int TText::fGetFontSpacing() const
{
    return mFontSpacing;
}

void TText::fDraw(QPainter *painter)
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

    painter->drawText(boundingRect(), Qt::AlignCenter, mText);
}
