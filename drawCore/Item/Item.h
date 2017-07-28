#ifndef TITEM_H
#define TITEM_H

#include <aglobal.h>
#include <QGraphicsItem>
#include <QtGui/QPen>
#include <QtGui/QPainter>
#include <QDataStream>

class TItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

    Q_PROPERTY(int     Type           READ fGetType           WRITE fSetType)
    Q_PROPERTY(QRectF  BoundingRect   READ fGetBoundingRect   WRITE fSetBoundingRect)
    Q_PROPERTY(double  RotateAngle    READ fGetRotateAngle    WRITE fSetRotateAngle)
    Q_PROPERTY(double  ZValue         READ fGetZValue         WRITE fSetZValue)
    Q_PROPERTY(QBrush  Brush          READ fGetBrush          WRITE fSetBrush)
    Q_PROPERTY(QPen    Pen            READ fGetPen            WRITE fSetPen)
    Q_PROPERTY(bool    MouseMove      READ fGetMoveAble       WRITE fSetMoveAble)
    Q_PROPERTY(bool    Select         READ fGetSelectAble     WRITE fSetSelectAble)
    Q_PROPERTY(bool    Drag           READ fGetDragAble       WRITE fSetDragAble)
    Q_PROPERTY(bool    Focus          READ fGetFocusAble      WRITE fSetFocusAble)

public:

    TItem(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(0, 0)), QPen pen =QPen(QColor(0, 0, 0)), QBrush brush = QBrush(QColor(0, 0, 0)));
    virtual ~TItem();

    virtual TItem* fCopy() = 0;             // 创建一个
    virtual void fCopy(TItem *ItemFrom);    // 根据拷贝已有对象的属性

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void fDraw(QPainter* painter) = 0;

    virtual QDataStream & serialize(QDataStream out);
    virtual QDataStream & desserialize(QDataStream in);

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
    inline void fSetMouseStyle(bool mouseType);
    inline bool fGetMouseStyle();

    inline void fSetZValue(double Z);
    inline double fGetZValue();

    inline void  fSetBoundingRect(const QRectF &boundingRect);
    inline void fSetBoundingWidthHeight(double width, double height);
    inline QRectF fGetBoundingRect();

    inline void fSetBrush(const QBrush &brush);
    inline QBrush fGetBrush();

    inline void fSetPen(const QPen &pen);
    inline QPen fGetPen();
    inline void fUpdate();

    inline int  fGetType() const;
    inline void fSetType(int type);

    inline bool fGetMoveAble() const;
    inline void fSetMoveAble(bool Able);
    inline void fMoveEnable(bool Enable);

    inline void fSetSelectAble(bool Able);
    inline bool fGetSelectAble() const;
    inline bool fGetDragAble() const;
    inline void fSetDragAble(bool Able);
    inline void fSetFocusAble(bool Able);
    inline bool fGetFocusAble();

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

inline void TItem::fSetMouseStyle(bool mouseType)
{
    m_MouseHand = mouseType;
    update();
}

inline bool TItem::fGetMouseStyle()
{
    return m_MouseHand;
}

inline void TItem::fSetZValue(double Z)
{
    setZValue(Z);
}

inline double TItem::fGetZValue()
{
    return zValue();
}

inline void  TItem::fSetBoundingRect(const QRectF &boundingRect)
{
    m_boundingRect = boundingRect;
    update();
}

inline void TItem::fSetBoundingWidthHeight(double width, double height)
{
    m_boundingRect.setSize(QSize(width, height));
    update();
}

inline QRectF TItem::fGetBoundingRect()
{
    return m_boundingRect;
}

inline void TItem::fSetBrush(const QBrush &brush)
{
    m_Brush = brush;
    update();
}

inline QBrush TItem::fGetBrush()
{
     return m_Brush;
}

inline void TItem::fSetPen(const QPen &pen)
{
    m_Pen = pen;
    update();
}

inline QPen TItem::fGetPen()
{
    return m_Pen;
}

inline void TItem::fUpdate()
{
    update(boundingRect());
}

inline int  TItem::fGetType() const
{
    return mType;
}

inline void TItem::fSetType(int type)
{
    mType = type;
}

inline bool TItem::fGetMoveAble() const
{
    return m_MoveEnable;
}

inline void TItem::fSetMoveAble(bool Able)
{
    m_MoveEnable = Able;
    fMoveEnable(Able);
}

inline void TItem::fMoveEnable(bool Enable)
{
    setFlag(ItemIsMovable, Enable);
}

inline void TItem::fSetSelectAble(bool Able)
{
    m_SelectEnable = Able;
    setFlag(ItemIsSelectable, Able);
}

inline bool TItem::fGetSelectAble() const
{
    return m_SelectEnable;
}

inline bool TItem::fGetDragAble() const
{
    return m_DragEnable;
}
inline void TItem::fSetDragAble(bool Able)
{
    m_DragEnable = Able;
    setAcceptHoverEvents(Able);
}
inline void TItem::fSetFocusAble(bool Able)
{
    m_FocusEnable = Able;
    setFlag(ItemIsFocusable,  Able);
}
inline bool TItem::fGetFocusAble()
{
    return m_FocusEnable;
}

#endif // TITEM_H
