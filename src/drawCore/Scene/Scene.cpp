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
TScene * TScene::fCopy()
{
    TScene *scene = new TScene(parent());
    scene->setSceneRect(sceneRect());

    scene->fSetName(fGetName() + QString::number(++m_maxSceneCopy));
    scene->setBackgroundBrush(backgroundBrush());
    QList<TItem *> itemList;
    fGetItemsList(itemList);

    foreach (auto *item, itemList) {
        scene->addItem(item->fCopy());
    }
    return scene;
}


TScene::~TScene()
{ }

void TScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);

    if(event->button()== Qt::LeftButton) {
        mStartDropX = event->scenePos().x();
        mStartDropY = event->scenePos().y();

        QGraphicsItem *UnderItem = itemAt(mStartDropX, mStartDropY, QTransform());

        if(UnderItem && UnderItem->isSelected()) {
            mSelectedBeforeDrop = true;
        }
    }
}
void TScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
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
 * \brief TScene::fGetItemByObjName  return TItem， TItem objname是 \a objectName
 */
TItem* TScene::fGetItemByObjName(const QString &objectName)
{
    if(objectName.isEmpty())
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
TItem *TScene::fGetItemByName(const QString &name)
{
    if(name.isEmpty())
        return nullptr;
    QList<TItemEx *> ItemList;
    fGetItemsList(ItemList);
    foreach (auto *item, ItemList) {
        if(item->fGetName() == name)
            return item;
    }
    return nullptr;
}
