﻿#ifndef TPIXMAP_H
#define TPIXMAP_H
#include "Graphics.h"

/////////////////////////////////////////////////  图片  /////////////////////////////////////////////////////
class TPixmap : public TGraphics
{
    Q_OBJECT
public:
    TPixmap(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(40, 40)), QPen pen =QPen(Qt::black),
            QBrush brush = QBrush(Qt::white), QString &FileDir = QString(":/menuImage/image/alarm.png"));

    virtual ~TPixmap();

    virtual TItem *fCopy();
    virtual void fCopy(TPixmap *PixmapFrom);
    virtual void fDraw(QPainter *painter);
/*
 * 供脚本调用的函数
*/
public slots:
    void fSetPixmapPath(const QString &FileDir);
    QString fGetPixmapPath();

    //virtual void fSetValue(const double Value);
protected:
    QString m_CurrentPixmapPath;

};
#endif // TPIXMAP_H
