#ifndef TITEM_H
#define TITEM_H

#include <aglobal.h>
#include <QGraphicsItem>
#include <QtGui/QPen>
#include <QtGui/QPainter>

class TItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

    Q_PROPERTY(double RotateAngle READ fGetRotateAngle   WRITE fSetRotateAngle)
    Q_PROPERTY(double ZValue READ fGetZValue  WRITE fSetZValue)

public:

    TItem(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(0, 0)), QPen pen =QPen(QColor(0, 0, 0)), QBrush brush = QBrush(QColor(0, 0, 0)));
    virtual ~TItem();

    virtual TItem* fCopy() = 0;             // 创建一个
    virtual void fCopy(TItem *ItemFrom);    // 根据拷贝已有对象的属性

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void fDraw(QPainter* painter) = 0;

    // 鼠标事件
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    virtual void UpdateMouse(const QPointF &PosNow);

Q_SIGNALS:
    void mDrop(TItem *Item, double StartDx, double StartDy, double StopDx, double StopDy);

    /* JS 脚本调用函数   */
public slots:

     void fSetLineColor(int r, int g, int b, int a = 255);
     void fSetLineColor(QColor color);
     void fSetLineAlpha(int alpha);
     QColor fGetLineColor() const;

     void fSetLineStyle(int style);
     Qt::PenStyle fGetLineStyle() const;

     void fSetLineWidth(int width);
     int fGetLineWidth() const;

     void fSetBackGroundColor(int r, int g, int b, int a = 255);
     void fSetBackGroundColor(QColor color);
     void fSetBackGroundAlpha(int alpha);
     QColor fGetBackGroundColor() const;

     void fSetBackGroundStyle(int style);
     Qt::BrushStyle fGetBackGroundStyle();

     void fSetBoundingRect(qreal x, qreal y, qreal width, qreal heigth);
    // 旋转
     bool fSetRotateAngle(double Angle);
     double fGetRotateAngle();
    //设置在场景中位置
     void fSetScenePos(const QPointF &pos);
     void fSetScenePos(double startX, double startY);
     QPointF fGetScenePos();

    //所有的内联函数
public:
    void TItem::fSetMouseStyle(bool mouseType)
    {
        m_MouseHand = mouseType;
        update();
    }

    bool TItem::fGetMouseStyle()
    {
        return m_MouseHand;
    }

    void fSetZValue(double Z)
    {
        setZValue(Z);
    }

    double fGetZValue()
    {
        return zValue();
    }

    void  fSetBoundingRect(const QRectF &boundingRect)
    {
        m_boundingRect = boundingRect;
        update();
    }

    void fSetBoundingWidthHeight(double width, double height)
    {
        m_boundingRect.setWidth(width);
        m_boundingRect.setHeight(height);
        update();
    }

    QRectF fGetBoundingRect()
    {
        return m_boundingRect;
    }

    void fSetBrush(const QBrush &brush)
    {
        m_Brush = brush;
        update();
    }

    QBrush fGetBrush()
    {
         return m_Brush;
    }

    void fSetPen(const QPen &pen)
    {
        m_Pen = pen;
        update();
    }

    QPen fGetPen()
    {
        return m_Pen;
    }

    inline void fUpdate()
    {
        update(boundingRect());
    }

    inline int  fGetType() const
    {
        return mType;
    }

    inline bool fGetMoveAble() const
    {
        return m_MoveEnable;
    }

    void fSetMoveAble(bool Able)
    {
        m_MoveEnable = Able;
        fMoveEnable(Able);
    }

    void fMoveEnable(bool Enable)
    {
        setFlag(ItemIsMovable, Enable);
    }

    void fSetSelectAble(bool Able)
    {
        m_SelectEnable = Able;
        setFlag(ItemIsSelectable, Able);
    }

    bool fGetSelectAble() const
    {
        return m_SelectEnable;
    }

    bool fGetDragAble() const
    {
        return m_DragEnable;
    }
    void fSetDragAble(bool Able)
    {
        m_DragEnable = Able;
        setAcceptHoverEvents(Able);
    }
    void fSetFocusAble(bool Able)
    {
        m_FocusEnable = Able;
        setFlag(ItemIsFocusable,  Able);
    }
    bool fGetFocusAble()
    {
        return m_FocusEnable;
    }

protected:
    int mType;
    double mRotateAngle;

    enum
    {
        Direc_Free          = 0,
        Direc_Top           = 1,
        Direc_RightTop      = 2,
        Direc_Right         = 3,
        Direc_RightBottom   = 4,
        Direc_Bottom        = 5,
        Direc_LeftBottom    = 6,
        Direc_Left          = 7,
        Direc_LeftTop       = 8
    };

    bool mDropScale;      // 是否开始拖动
    int mDropDirection;   // 拖动方向
    QPointF mDropPos;     // 拖动点,会随着拖动过程改变
    QPointF mPressStart;  // 拖动起

    bool m_MoveEnable;
    bool m_SelectEnable;
    bool m_DragEnable;
    bool m_FocusEnable;
    //样式
    QPen m_Pen;
    QBrush m_Brush;
    QRectF m_boundingRect;
    bool m_MouseHand =  false;            //鼠标进入变手型
};

#endif // TITEM_H
