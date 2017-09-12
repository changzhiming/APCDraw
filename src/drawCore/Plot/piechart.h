#ifndef PIECHART_H
#define PIECHART_H

#include <QObject>
#include "../Item/ItemEx.h"
#include <aglobal.h>
class PieChart : public TItemEx
{
    Q_OBJECT
public:
    explicit PieChart(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(0, 0)), QPen pen =QPen(QColor(0, 0, 0)), QBrush brush = QBrush(QColor(255, 255, 255)));

    virtual TItem *fCopy();
    virtual void fCopy(PieChart *PieForm);
    virtual void fDraw(QPainter *painter);

public slots:
    void append(int perce, QString name = QString());
private:
    QHash<int , QString > m_ItemList;  //所有信息
    int m_allNumber;
};

#endif // PIECHART_H
