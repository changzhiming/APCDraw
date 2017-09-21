#ifndef TTABLE_H
#define TTABLE_H

#include "Widgets.h"
#include <aglobal.h>
///////////////////////  控件基类 /////////////////////////////////////
class TTable : public TWidgets
{
    Q_OBJECT
public:
    TTable(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(40, 40)), QPen pen =QPen(Qt::white), QBrush brush = QBrush(Qt::black));
    virtual ~TTable();

public slots:
    TItem *fCopy();
    void fCopy(TTable *TableFrom);

    bool fSetSize(int RowSum, int ColSum);
    int fGetRowSum();
    int fGetColSum();

    void fSetColLength(int Index, int Len);
    int fGetColLength(int Index);
    void fSetRowLength(int Len);
    int fGetRowLength();

    int fGetCurrentCol();               // 获取当前列
    int fGetCurrentIndex();             // 获取当前行
    QString fGetCurrentData(int Col);   // 获取当前行 某列的数据
    void fSetCell(int Row, int Col, QString Text);
    QString fGetCell(int Row, int Col);

private:
    int mCurrentCol;
    int mCurrentIndex;
    QString ***mData;
    int mRowSum;
    int mColSum;

    int mRowLength;
    int *mColLengthArray;

    void fDestroy();
    void fUpdatePos();
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void fDraw(QPainter *painter);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // TTABLE_H
