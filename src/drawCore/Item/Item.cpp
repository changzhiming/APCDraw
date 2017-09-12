#include "Item.h"
#include <QToolTip>
#include <QGraphicsSceneEvent>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include <QGraphicsScene>
#include "ItemFactory.h"
/*!
  \class TItem
  \brief 图形项基类， 提供基本的左边变换， 拖拽， 拖拉， Item类型
  */

/*!
 * \brief TItem::TItem  构造Item类 \a atScenePos在场景中位置
 * \a bounDingRect 绘图区域
 * \a pen  画笔， 字体和边框颜色
 * \a brush 画刷， 填充色
 * \a type  Item 类型
 * \sa TItemFactory::Type
 */

TItem::TItem(QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush) : QGraphicsObject()
{
    mType = TItemFactory::Base;

    m_boundingRect = bounDingRect;
    m_Pen = pen;
    m_Brush = brush;
    mDropScale = false;
    mDropDirection = Direc_Free;
    mRotateAngle = 0;

    fSetSelectAble(true);
    fSetMoveAble(true);
    fSetDragAble(true);
    setPos(atScenePos);
}

TItem::~TItem()
{}

QRectF TItem::boundingRect() const
{
    QRectF mRect = m_boundingRect;
    double padding = m_Pen.width();
    mRect.adjust(-padding, -padding, +padding, +padding);
    return mRect;
}

void TItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{  
    Q_UNUSED(widget)
    if(fGetSelectAble() && (option->state & QStyle::State_Selected)) {
        QPen pen = m_Pen;
        pen.setColor(Qt::red);
        pen.setStyle(Qt::DotLine);
        pen.setWidth(2);
        painter->setPen(pen);
        painter->drawRect(m_boundingRect);
    }

    painter->setPen(m_Pen);
    painter->setBrush(m_Brush);
    painter->setRenderHint(QPainter::Antialiasing, true);
    ///< paint a graph
    fDraw(painter);
}

QDataStream & TItem::serialize(QDataStream &out)
{
    out<<mType<<mRotateAngle<<m_MoveEnable<<m_SelectEnable<<m_DragEnable<<
         m_FocusEnable<<m_Pen<<m_Brush<<m_boundingRect<<m_MouseHand<<pos();
    return out;
}

QDataStream & TItem::desserialize(QDataStream &in)
{
    in>>mType>>mRotateAngle>>m_MoveEnable>>m_SelectEnable>>m_DragEnable>>
         m_FocusEnable>>m_Pen>>m_Brush>>m_boundingRect>>m_MouseHand;
    QPointF posPoint;
    in>>posPoint;
    setPos(posPoint);

    fSetMoveAble(m_MoveEnable);
    fSetSelectAble(m_SelectEnable);
    fSetDragAble(m_DragEnable);
    return in;
}

void TItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);

    if(fGetDragAble() && Qt::LeftButton == event->button() && mDropDirection > Direc_Free) {
        mPressStart = event->pos();
        mDropPos = mapToScene(event->pos());
        mDropScale = true;
    } else {
        fMoveEnable(true); // 临时设置为可移动，否则不能触发mouseReleaseEvent
        mDropScale = false;
    }
}

void TItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);

    if(mDropScale)
    {
        QPointF dis = mapToScene(event->pos()) - mDropPos;
        mDropPos = mapToScene(event->pos());
        switch(mDropDirection)
        {
        case Direc_Top: // 上 dis.y < 0
        {
            m_boundingRect.adjust(0, 0, 0, -dis.y());
            moveBy(0, dis.y());
            break;
        }
        case Direc_RightTop: // 右上
        {
            m_boundingRect.adjust(0, 0, dis.x(), -dis.y());
            moveBy(0, dis.y());
            break;
        }
        case Direc_Right: // 右 dis.x > 0
        {
            m_boundingRect.adjust(0, 0, dis.x(), 0);
            break;
        }
        case Direc_RightBottom: // 右下
        {
            m_boundingRect.adjust(0, 0, dis.x(), dis.y());
            break;
        }
        case Direc_Bottom: // 下 dis.y > 0
        {
            m_boundingRect.adjust(0, 0, 0, dis.y());
            break;
        }
        case Direc_LeftBottom: // 左下
        {
            m_boundingRect.adjust(0, 0, -dis.x(), dis.y());
            moveBy(dis.x(), 0);
            break;
        }
        case Direc_Left: // 左 dis.x < 0
        {
            m_boundingRect.adjust(0, 0, -dis.x(), 0);
            moveBy(dis.x(), 0);
            break;
        }
        case Direc_LeftTop: // 左上
        {
            m_boundingRect.adjust(0, 0, -dis.x(), -dis.y());
            moveBy(dis.x(), dis.y());
            break;
        }

        default:
            break;
        }
        if(scene())
            scene()->update();
    }
}

void TItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    fMoveEnable(m_MoveEnable); // 关闭临时可移动，恢复正常的移动标志
}

void TItem::UpdateMouse(const QPointF &PosNow)
{
    if(!fGetDragAble())
        return;

    QCursor mCursor;

    QRectF mRect = boundingRect();

    QPointF lt = mRect.topLeft();
    QPointF lb = mRect.bottomLeft();
    QPointF rt = mRect.topRight();
    QPointF rb = mRect.bottomRight();

    int Add = m_Pen.width() + 3;

    if(PosNow.x() <= lt.x() + Add && PosNow.y() <= lt.y() + Add)      // 左上
    {
        mDropDirection = Direc_LeftTop;
        mCursor.setShape(Qt::SizeFDiagCursor);
    }
    else if(PosNow.x() >= rb.x() - Add && PosNow.y() >= rb.y() - Add) // 右下
    {
        mDropDirection = Direc_RightBottom;
        mCursor.setShape(Qt::SizeFDiagCursor);
    }
    else if(PosNow.x() <= lb.x() + Add && PosNow.y() >= lb.y() - Add) // 左下
    {
        mDropDirection = Direc_LeftBottom;
        mCursor.setShape(Qt::SizeBDiagCursor);
    }
    else if(PosNow.x() >= rt.x() - Add && PosNow.y() <= rt.y() + Add) // 右上
    {
        mDropDirection = Direc_RightTop;
        mCursor.setShape(Qt::SizeBDiagCursor);
    }
    else if(PosNow.x() < lt.x() + Add /* && PosNow.y() < lb.y() && PosNow.y() > lt.y()*/) // 左
    {
        mDropDirection = Direc_Left;
        mCursor.setShape(Qt::SizeHorCursor);
    }
    else if(PosNow.x() > rt.x() - Add /*&& PosNow.y() < rb.y() && PosNow.y() > rt.y()*/) // 右
    {
        mDropDirection = Direc_Right;
        mCursor.setShape(Qt::SizeHorCursor);
    }
    else if(PosNow.y() < lt.y() + Add /*&& PosNow.x() > lt.x() && PosNow.x() < rt.x()*/) // 上
    {
        mDropDirection = Direc_Top;
        mCursor.setShape(Qt::SizeVerCursor);
    }
    else if(PosNow.y() > lb.y() - Add /*&& PosNow.x() > lt.x() && PosNow.x() < rt.x()*/) // 下
    {
        mDropDirection = Direc_Bottom;
        mCursor.setShape(Qt::SizeVerCursor);
    }
    else
    {
        mDropDirection = Direc_Free;
        mCursor.setShape(Qt::ArrowCursor);
    }

    if(Direc_Free == mDropDirection)
        fMoveEnable(m_MoveEnable);
    else
        fMoveEnable(false);

    setCursor(mCursor);
}

void TItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QPointF PosNow = event->pos();
    UpdateMouse(PosNow);
    QGraphicsItem::hoverEnterEvent(event);
}

void TItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QPointF PosNow = event->pos();
    UpdateMouse(PosNow);
    QGraphicsItem::hoverMoveEvent(event);
}

void TItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    mDropScale = false;
    mDropDirection = Direc_Free;
    // 当鼠标离开图形，恢复移动状态
    fMoveEnable(fGetMoveAble());
    QGraphicsItem::hoverLeaveEvent(event);
}

void TItem::keyReleaseEvent(QKeyEvent *event)
{
    QGraphicsItem::keyReleaseEvent(event);
}

void TItem::fCopy(TItem *ItemFrom)
{
    fSetPen(ItemFrom->fGetPen());
    fSetBrush(ItemFrom->fGetBrush());
    fSetBoundingRect(ItemFrom->fGetBoundingRect());
    fSetScenePos(ItemFrom->fGetScenePos());

    fSetSelectAble(ItemFrom->fGetSelectAble());
    fSetMoveAble(ItemFrom->fGetMoveAble());
    fSetDragAble(ItemFrom->fGetDragAble());
    fSetZValue(ItemFrom->fGetZValue());
}

bool TItem::fSetRotateAngle(double Angle)
{   
    if(qAbs(Angle) < 0.000001)
        return false;

    setRotation(Angle);
    mRotateAngle = Angle;
    return true;
}
double TItem::fGetRotateAngle()
{
    return mRotateAngle;
}

void TItem::fSetLineColor(int r, int g, int b, int a)
{
    m_Pen.setColor(QColor(r, g, b, a));
    update();
}
void TItem::fSetLineColor(QColor color)
{
    m_Pen.setColor(color);
    update();
}
void TItem::fSetLineAlpha(int alpha)
{
    QColor color = m_Pen.color();
    color.setAlpha(alpha);
    m_Pen.setColor(color);
    update();
}

QColor TItem::fGetLineColor() const
{
    return m_Pen.color();
}


void TItem::fSetLineStyle(int style)
{
    m_Pen.setStyle(Qt::PenStyle(style));
    update();
}

Qt::PenStyle TItem::fGetLineStyle() const
{
    return m_Pen.style();
}

void TItem::fSetLineWidth(int width)
{
    m_Pen.setWidth(width);
    update();
}

int TItem::fGetLineWidth() const
{
    return m_Pen.width();
}

void TItem::fSetBackGroundColor(int r, int g, int b, int a)
{
    m_Brush.setColor(QColor(r, g, b, a));
    update();
}
 void TItem::fSetBackGroundColor(QColor color)
 {
     m_Brush.setColor(color);
 }
void TItem::fSetBackGroundAlpha(int alpha)
{
    QColor color = m_Brush.color();
    color.setAlpha(alpha);
    m_Brush.setColor(color);
    update();
}

QColor TItem::fGetBackGroundColor() const
{
    return m_Brush.color();
}

void TItem::fSetBackGroundStyle(int style)
{
    m_Brush.setStyle(Qt::BrushStyle(style));
    update();
}

Qt::BrushStyle TItem::fGetBackGroundStyle()
{
    return m_Brush.style();
}

void  TItem::fSetScenePos(const QPointF &pos)
{
    setPos(pos);
}
void TItem::fSetScenePos(double startX, double startY)
{
    setPos(startX, startY);
}

QPointF TItem::fGetScenePos() const
{
    return pos();
}

void TItem::fSetBoundingRect(qreal x, qreal y, qreal width, qreal heigth)
{
     m_boundingRect.adjust(x, y, x + width, y + heigth);
}


