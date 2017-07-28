#include "ItemFactory.h"

#include "../Graphics/GraphicsPub.h"
#include "../Widgets/WidgetsPub.h"

QHash<TItemFactory::Type, int> TItemFactory::g_TypeNum;

TItemFactory::TItemFactory() : QObject()
{}

TItemFactory::~TItemFactory()
{}

TItemEx* TItemFactory::fFactory(int Type, QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush)
{
    TItemEx *Item = NULL;

    switch (Type)
    {

    case Point:
    {
        Item = new TPoint(atScenePos, bounDingRect, pen, brush);
        setTypeObjName(Item, Point);
    }
    break;

    case Line:
    {
        Item = new TLine(atScenePos, bounDingRect, pen, brush);
        setTypeObjName(Item, Line);
    }
    break;

    case Ellipse:
    {
        Item = new TEllipse(atScenePos, bounDingRect, pen, brush);
        setTypeObjName(Item, Ellipse);
    }
    break;

    case Rect:
    {
        Item = new TRect(atScenePos, bounDingRect, pen, brush);
        setTypeObjName(Item, Rect);
    }
    break;

    case Polygon:
    {
        Item = new TPolygon(atScenePos, bounDingRect, pen, brush);
        setTypeObjName(Item, Polygon);
        break;
    }

    case Arc:
    {
        Item = new TArc(atScenePos, bounDingRect, pen, brush);
        setTypeObjName(Item, Arc);
    }
    break;

    case Text:
    {
        Item = new TText(atScenePos, bounDingRect, pen, brush);
        setTypeObjName(Item, Text);
    }
    break;

    case ValueText:
    {
        Item = new TValueText(atScenePos, bounDingRect, pen, brush);
        setTypeObjName(Item, ValueText);
    }
    break;

    case Pixmap:
    {
        Item = new TPixmap(atScenePos, bounDingRect, pen, brush);
        setTypeObjName(Item, Pixmap);
    }
    break;

    case Light:
    {
        Item = new TLight(atScenePos, bounDingRect, pen, brush);
        setTypeObjName(Item, Light);
    }
    break;

    case Curve:
    {
        Item = new TCurve(atScenePos, bounDingRect, pen, brush);
        setTypeObjName(Item, Curve);
    }
    break;

    case Meter:
    {
        Item = new TMeter(atScenePos, bounDingRect, pen, brush);
        setTypeObjName(Item, Meter);
    }
    break;

    case ProcessBar:
    {
        Item = new TProcessBar(atScenePos, bounDingRect, pen, brush);
        setTypeObjName(Item, ProcessBar);
    }
    break;
    case Graph:
    {
        //Item = new QCustomPlot(atScenePos, bounDingRect, pen, brush);
        //setTypeObjName(Item, Plot);
    }
    break;

//    case Table:
//    {
//        Item = new TTable(atScenePos, bounDingRect, pen, brush);
//    }
//    break;

//    case Button:
//    {
//        Item = new TButton(atScenePos, bounDingRect, pen, brush);
//    }
//    break;

//    case InputEdit:
//    {
//        Item = new TInputEdit(atScenePos, bounDingRect, pen, brush);
//    }
    break;

    default:
        break;
    }

    return Item;
}
int TItemFactory::setTypeNum(TItemFactory::Type type)
{
    if(g_TypeNum.contains(type)) {
        g_TypeNum[type] = g_TypeNum[type] + 1;
    } else {
        g_TypeNum.insert(type, 0);
    }
    return g_TypeNum[type];
}
void TItemFactory::setTypeObjName(TItem *Item, int Type)
{
    switch (Type)
    {

    case Point:
    {
        Item->setObjectName(QStringLiteral("Point") + QString::number(setTypeNum(Point)));
    }
    break;

    case Line:
    {
        Item->setObjectName(QStringLiteral("Line") + QString::number(setTypeNum(Line)));
    }
    break;

    case Ellipse:
    {
        Item->setObjectName(QStringLiteral("Ellipse") + QString::number(setTypeNum(Ellipse)));
    }
    break;

    case Rect:
    {
        Item->setObjectName(QStringLiteral("Rect") + QString::number(setTypeNum(Rect)));
    }
    break;

    case Polygon:
    {
        Item->setObjectName(QStringLiteral("Polygon") + QString::number(setTypeNum(Polygon)));
        break;
    }

    case Arc:
    {
        Item->setObjectName(QStringLiteral("Arc") + QString::number(setTypeNum(Arc)));
    }
    break;

    case Text:
    {
        Item->setObjectName(QStringLiteral("Text") + QString::number(setTypeNum(Text)));
    }
    break;

    case ValueText:
    {
        Item->setObjectName(QStringLiteral("ValueText") + QString::number(setTypeNum(ValueText)));
    }
    break;

    case Pixmap:
    {
        Item->setObjectName(QStringLiteral("Pixmap") + QString::number(setTypeNum(Pixmap)));
    }
    break;

    case Light:
    {
        Item->setObjectName(QStringLiteral("Light") + QString::number(setTypeNum(Line)));
    }
    break;

    case Curve:
    {
        Item->setObjectName(QStringLiteral("Curve") + QString::number(setTypeNum(Curve)));
    }
    break;

    case Meter:
    {
        Item->setObjectName(QStringLiteral("Meter") + QString::number(setTypeNum(Meter)));
    }
    break;

    case ProcessBar:
    {
        Item->setObjectName(QStringLiteral("ProcessBar") + QString::number(setTypeNum(ProcessBar)));
    }
    break;
    case Graph:
    {
        Item->setObjectName(QStringLiteral("Graph") + QString::number(setTypeNum(Graph)));
    }
    break;

//    case Table:
//    {
//        Item = new TTable(atScenePos, bounDingRect, pen, brush);
//    }
//    break;

//    case Button:
//    {
//        Item = new TButton(atScenePos, bounDingRect, pen, brush);
//    }
//    break;

//    case InputEdit:
//    {
//        Item = new TInputEdit(atScenePos, bounDingRect, pen, brush);
//    }
    break;

    default:
        break;
    }
}
