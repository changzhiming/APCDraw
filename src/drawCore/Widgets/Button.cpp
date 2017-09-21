#include "Button.h"
#include <QDebug>

#include <QGraphicsSceneMouseEvent>

TButton::TButton(QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush) :
    TWidgets(atScenePos, bounDingRect, pen, brush)
{
    fSetType(TItemFactory::Button);
    mText = tr("Button");
    mPressed = false;

//    mFontFamily = tr("宋体");
    mFontSize = 12;
//    mFontBlod = false;
//    mFontItalic = false;
//    mFontUnderLine = false;
//    mFontStrikeOut = false;
//    mFontSpacing = 0;
}

TButton::~TButton()
{}

TItem* TButton::fCopy()
{
    TButton *Button = new TButton();
    Button->fCopy(this);
    return Button;
}

void TButton::fCopy(TButton *ButtonFrom)
{
    if(NULL == ButtonFrom)
    {
        return;
    }

    TWidgets::fCopy(ButtonFrom);

    this->fSetText(ButtonFrom->fGetText());
    this->fSetFontSize(ButtonFrom->fGetFontSize());
}


void TButton::fDraw(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing); // 去锯齿
    double Roundness = qMin(m_boundingRect.width(), m_boundingRect.height()) * 0.1; //圆角
    painter->save();

    QPainterPath OutLine;
    OutLine.addRoundedRect(m_boundingRect, Roundness, Roundness);

    painter->fillPath(OutLine, m_Brush.color());
    if(mPressed) {
        painter->setPen(QPen(Qt::gray, 2.0));
        painter->fillPath(OutLine, m_Brush.color());
    }
    painter->drawPath(OutLine);
    //文字
    painter->restore();
    QFont Font = painter->font();
    Font.setPointSize(mFontSize);
    painter->setFont(Font);
    painter->drawText(m_boundingRect, Qt::AlignCenter, mText);
}

void TButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    mPressed = true;
    TWidgets::mousePressEvent(event);
}

void TButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    mPressed = false;
    TWidgets::mouseReleaseEvent(event);
}

void TButton::fSetFontSize(int Size)
{
    mFontSize = Size;
}

int TButton::fGetFontSize() const
{
    return mFontSize;
}
void TButton::fSetText(QString Text)
{
    mText = Text;
}

QString TButton::fGetText()
{
    return mText;
}
