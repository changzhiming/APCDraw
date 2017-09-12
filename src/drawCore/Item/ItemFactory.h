
#ifndef TITEM_FACTORY_H
#define TITEM_FACTORY_H
#include "ItemEx.h"

class TItemFactory : public QObject
{   
    Q_OBJECT
    Q_ENUMS(Type)
public:
    enum Type {
                    Base        = 0,
                    Group       = 1,
                    Point       = 2,
                    Line        = 3,
                    Ellipse     = 4,
                    Rect        = 5,
                    Polygon     = 6,
                    Arc         = 7,
                    Text        = 10,
                    Pixmap      = 11,
                    Path        = 12,
                    ValueText   = 13,
                    Light       = 14,
                    Meter       = 15,
                    ProcessBar  = 16,
                    Curve       = 17,
                    Clock       = 18,
                    _Graph      = 19,
                    _Bar        = 20,
                    _Pie        = 21,
                    _Instrument = 22,

                    Button      = 101,
                    InputEdit   = 102,
                    Table       = 103,
                    Max,
              };
    static TItemEx * fFactory(int Type, QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(40, 40)), QPen pen =QPen(Qt::black),
                            QBrush brush = QBrush(Qt::white));
    static QHash<TItemFactory::Type, int> g_TypeNum;  //每种类型的最大个数
    static int setTypeNum(Type type);
    static void setTypeObjName(TItem *item, int type);
private:
    TItemFactory();
    ~TItemFactory();   
};

#endif // TITEM_FACTORY_H
