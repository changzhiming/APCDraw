#include "View.h"
#include "Dialog/aobjectanimation.h"
#include "../Scene/Scene.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <QMenu>

TView::TView(QWidget *parent)
    : QGraphicsView(parent)
{
    mZoom = 1;
}

void TView::wheelEvent(QWheelEvent *event)
{
    double numDegrees = event->delta() / 8.0;
    double numSteps = numDegrees / 15.0;
    double factor = std::pow(1.125, numSteps);

    fZoom(factor);
}

void TView::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit mMousePress(event->pos().x(), event->pos().y());
    QGraphicsView::mousePressEvent(event);
}
void TView::contextMenuEvent(QContextMenuEvent *event)
{
    QGraphicsView::contextMenuEvent(event);

    QTransform deviceTransform;
    QGraphicsItem *UnderItem = scene()->itemAt(mapToScene(event->pos()), deviceTransform);
    if(UnderItem) {
        QMenu menu;
        menu.addAction(tr("对象动作"), [=]() {
            AObjectAnimation *obj = new AObjectAnimation(dynamic_cast<TItemEx *>(UnderItem), this);
            obj->show();
        });
        menu.addSeparator();
        menu.addActions(actions());
        menu.exec(QCursor::pos());
    }

}
void TView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QGraphicsView::mouseDoubleClickEvent(event);

    if(scene()) {
        QTransform deviceTransform;
        QGraphicsItem *UnderItem = scene()->itemAt(mapToScene(event->pos()), deviceTransform);
        if(UnderItem) {

        }
    }
}
void TView::fZoom(double _Multiple)
{
    double NewZoom = mZoom * _Multiple;

    if(NewZoom > 0.1 && NewZoom < 10)
    {
        scale(_Multiple, _Multiple);

        mZoom = NewZoom;
    }
}

void TView::fSetZoom(double _Zoom)
{
    if(_Zoom > 0.1 && _Zoom < 10)
    {
        double Multiple = _Zoom / mZoom;

        scale(Multiple, Multiple);

        mZoom = _Zoom;
    }
}

double TView::fGetZoom() const
{
    return mZoom;
}
