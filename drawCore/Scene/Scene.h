#ifndef TSCENE_H
#define TSCENE_H
#include <QGraphicsScene>
#include "../Item/ItemEx.h"
class QGraphicsSceneMouseEvent;

class TScene : public QGraphicsScene
{
    Q_OBJECT

public:
    TScene(QObject *parent = 0);
    ~TScene();

    template<typename ItemType>
    void fGetItemsList(QList<ItemType *> &List)
    {
        List.clear();
        foreach(QGraphicsItem *mGraphicsItem, items())
        {
            ItemType *FindItem = dynamic_cast<ItemType *>(mGraphicsItem);

            if(FindItem) {
                List.push_back(FindItem);
            }
        }
    }

    template<typename ItemType>
    void fGetItemsSelected(QList<ItemType *> &List)
    {
        List.clear();
        foreach(QGraphicsItem *mGraphicsItem, selectedItems())
        {
            ItemType *FindItem = dynamic_cast<ItemType *>(mGraphicsItem);

            if(FindItem) {
                List.push_back(FindItem);
            }
        }
    }

    TItem* fGetItemByObjName(const QString &objectName);

    // 内联函数
    inline void fSetName(QString Name);
    inline QString fGetName();

public slots:
    void fSetBackColor(int R, int G, int B, int A);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);// 鼠标按下
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event);//鼠标移动
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);// 鼠标松开

Q_SIGNALS:
    void mDropFinsh(double StartX, double StartY, double StopX, double StopY);
    void mMoveItemList(TScene *Scene, QList<TItem *> ItemList,
                       double StartX, double StartY, double StopX, double StopY);
private:

    double mStartDropX;
    double mStartDropY;

    QString mName;
    bool mSelectedBeforeDrop;

};
void TScene::fSetName(QString Name)
{   mName = Name;}

QString TScene::fGetName()
{    return mName;}

#endif // TSCENE_H
