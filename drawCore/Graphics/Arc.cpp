#include "Arc.h"
#include "../Item/ItemFactory.h"

TArc::TArc(QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush) :
        TGraphics(atScenePos, bounDingRect, pen, brush)
{
    mType = TItemFactory::Arc;
    mMode = MODE_PIE;

    mStartAngle = 45;
    mCoverAngle = 90;
}

TArc::~TArc()
{}

TItem *TArc::fCopy()
{
    TArc *Arc = new TArc();
    Arc->fCopy(this);
    return Arc;
}

void TArc::fCopy(TArc *ArcFrom)
{
    if(NULL == ArcFrom)
    {
        return;
    }

    TGraphics::fCopy(ArcFrom);

    this->fSetMode(ArcFrom->fGetMode());
    this->fSetStartAngle(ArcFrom->fGetStartAngle());
    this->fSetCoverAngle(ArcFrom->fGetCoverAngle());
}

bool TArc::fSetMode(const int Mode)
{
    if(Mode > MODE_MIN && Mode < MODE_MAX)
    {
        mMode = Mode;
        return true;
    }
    else
    {
        return false;
    }
}

int TArc::fGetMode() const
{
    return mMode;
}

void TArc::fSetStartAngle(const double StartAngle)
{
    mStartAngle = StartAngle;
}

double TArc::fGetStartAngle() const
{
    return mStartAngle;
}

void TArc::fSetCoverAngle(const double CoverAngle)
{
    mCoverAngle = CoverAngle;
}

double TArc::fGetCoverAngle() const
{
    return mCoverAngle;
}

void TArc::fDraw(QPainter *painter)
{
    switch(mMode)
    {        
    case MODE_PIE:
        painter->drawPie(m_boundingRect.adjusted(0, 0, 0, m_boundingRect.height()), mStartAngle * 16, mCoverAngle * 16);
        break;

    case MODE_ARC:
        painter->drawArc(m_boundingRect.adjusted(0, 0, 0, m_boundingRect.height()), mStartAngle * 16, mCoverAngle * 16);
        break;

    case MODE_CHORD:
        painter->drawChord(m_boundingRect.adjusted(0, 0, 0, m_boundingRect.height()), mStartAngle * 16, mCoverAngle * 16);
        break;

    default:
        break;
    }
}
