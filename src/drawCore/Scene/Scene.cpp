#include "Scene.h"
#include <QPointF>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

TScene::TScene(QObject *parent) : QGraphicsScene(parent)
{
    mStartDropX = 0;
    mStartDropY = 0;
    mSelectedBeforeDrop = false;
}

TScene::~TScene()
{ }

void TScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);

    if(event->button()== Qt::LeftButton) {
        mStartDropX = event->scenePos().x();
        mStartDropY = event->scenePos().y();

        QTransform deviceTransform;
        QGraphicsItem *UnderItem = itemAt(mStartDropX, mStartDropY, deviceTransform);

        if(UnderItem && UnderItem->isSelected()) {
            mSelectedBeforeDrop = true;
        }
    }
}

void TScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{   
    if(event->button()== Qt::LeftButton) {
        if(!mSelectedBeforeDrop) {
            if(qAbs(event->scenePos().x() - mStartDropX) > 10)
                emit mDropFinsh(QRectF(QPointF( mStartDropX, mStartDropY), QPointF( event->scenePos().x(), event->scenePos().y())));
        }
    }

    mSelectedBeforeDrop = false;
    QGraphicsScene::mouseReleaseEvent(event);
}


void TScene::fSetBackColor(int R, int G, int B, int A)
{
    setBackgroundBrush(QBrush(QColor(R, G, B, A)));
}

/*!
 * \brief TScene::fGetItemByNameId  return TItem， TItem objname是 \a objectName
 */
TItem* TScene::fGetItemByObjName(const QString &objectName)
{
    if(objectName.length() <= 0)
        return nullptr;
    QList<TItem *> ItemList;
    fGetItemsList(ItemList);

    foreach(TItem * item,  ItemList)
    {
        if(item->objectName() == objectName)
            return item;
    }
    return nullptr;
}
