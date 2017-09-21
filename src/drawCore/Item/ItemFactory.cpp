#include "ItemFactory.h"
#include "../Graphics/GraphicsPub.h"
#include "../Widgets/WidgetsPub.h"
#include "../Plot/plotpub.h"

QHash<TItemFactory::Type, int> TItemFactory::g_TypeNum;

TItemEx* TItemFactory::fFactory(int Type, QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush)
{
    TItemEx *Item = NULL;

    switch (Type)
    {

    case Point:
    {
        Item = new TPoint(atScenePos, bounDingRect, pen, brush);
        Item->setObjectName(QStringLiteral("Point") + QString::number(setTypeNum(Point)));
    }
    break;

    case Line:
    {
        Item = new TLine(atScenePos, bounDingRect, pen, brush);
        Item->setObjectName(QStringLiteral("Line") + QString::number(setTypeNum(Line)));
    }
    break;

    case Ellipse:
    {
        Item = new TEllipse(atScenePos, bounDingRect, pen, brush);
        Item->setObjectName(QStringLiteral("Ellipse") + QString::number(setTypeNum(Ellipse)));
    }
    break;

    case Rect:
    {
        Item = new TRect(atScenePos, bounDingRect, pen, brush);
        Item->setObjectName(QStringLiteral("Rect") + QString::number(setTypeNum(Rect)));
    }
    break;

    case Polygon:
    {
        Item = new TPolygon(atScenePos, bounDingRect, pen, brush);
        Item->setObjectName(QStringLiteral("Polygon") + QString::number(setTypeNum(Polygon)));
        break;
    }

    case Arc:
    {
        Item = new TArc(atScenePos, bounDingRect, pen, brush);
        Item->setObjectName(QStringLiteral("Arc") + QString::number(setTypeNum(Arc)));
    }
    break;

    case Text:
    {
        Item = new TText(atScenePos, bounDingRect, pen, brush);
        Item->setObjectName(QStringLiteral("Text") + QString::number(setTypeNum(Text)));
    }
    break;

    case ValueText:
    {
        Item = new TValueText(atScenePos, bounDingRect, pen, brush);
        Item->setObjectName(QStringLiteral("ValueText") + QString::number(setTypeNum(ValueText)));
    }
    break;

    case Pixmap:
    {
        Item = new TPixmap(atScenePos, bounDingRect, pen, brush);
        Item->setObjectName(QStringLiteral("Pixmap") + QString::number(setTypeNum(Pixmap)));
    }
    break;

    case Light:
    {
        Item = new TLight(atScenePos, bounDingRect, pen, brush);
        Item->setObjectName(QStringLiteral("Light") + QString::number(setTypeNum(Line)));
    }
    break;

    case Curve:
    {
        Item = new TCurve(atScenePos, bounDingRect, pen, brush);
        Item->setObjectName(QStringLiteral("Curve") + QString::number(setTypeNum(Curve)));
    }
    break;

    case Meter:
    {
        Item = new TMeter(atScenePos, bounDingRect, pen, brush);
        Item->setObjectName(QStringLiteral("Meter") + QString::number(setTypeNum(Meter)));
    }
    break;

    case ProcessBar:
    {
        Item = new TProcessBar(atScenePos, bounDingRect, pen, brush);
        Item->setObjectName(QStringLiteral("ProcessBar") + QString::number(setTypeNum(ProcessBar)));
    }
    break;
    case _Graph:
    {
        Item = new Graph(atScenePos, bounDingRect, pen, brush);
        Item->setObjectName(QStringLiteral("Graph") + QString::number(setTypeNum(_Graph)));
    }
    break;
    case _Bar:
    {
        Item = new Bar(atScenePos, bounDingRect, pen, brush);
        Item->setObjectName(QStringLiteral("Bar") + QString::number(setTypeNum(_Bar)));
    }
    break;
    case _Pie:
    {
        Item = new PieChart(atScenePos, bounDingRect, pen, brush);
        Item->setObjectName(QStringLiteral("Pie") + QString::number(setTypeNum(_Pie)));
    }
    break;
    case _Instrument:
    {
        Item = new InstrumentPanel(atScenePos, bounDingRect, pen, brush);
        Item->setObjectName(QStringLiteral("Instrument") + QString::number(setTypeNum(_Instrument)));
    }
    break;

    case Table:
    {
        Item = new TTable(atScenePos, bounDingRect, pen, brush);
        Item->setObjectName(QStringLiteral("Table") + QString::number(setTypeNum(Table)));
    }
    break;

    case Button:
    {
        Item = new TButton(atScenePos, bounDingRect, pen, brush);
        Item->setObjectName(QStringLiteral("Button") + QString::number(setTypeNum(Button)));
    }
    break;

    case InputEdit:
    {
        Item = new TInputEdit(atScenePos, bounDingRect, pen, brush);
        Item->setObjectName(QStringLiteral("InputEdit") + QString::number(setTypeNum(InputEdit)));
    }
    break;

    default:
        break;
    }

    return Item;
}
int TItemFactory::setTypeNum(TItemFactory::Type type)
{
    if(g_TypeNum.contains(type))
        g_TypeNum[type] = g_TypeNum[type] + 1;
    else
        g_TypeNum.insert(type, 0);

    return g_TypeNum[type];
}
