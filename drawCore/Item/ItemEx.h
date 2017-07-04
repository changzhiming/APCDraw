﻿#ifndef TITEM_EX_H
#define TITEM_EX_H

#include "Item.h"
/*!
* @class 类名
* @brief 概述
*
* 详细概述
* @b 修改记录：
* @li 日期
* @- add setA()
* @- changed getA()
*/
#include <QWidget>
class TItemEx : public TItem
{
    Q_PROPERTY(QString MousePressJS READ fGetMousePressJS WRITE fSetMousePressJS)
    Q_PROPERTY(QString LinkScene READ fGetLinkScene WRITE fSetLinkScene)

    Q_OBJECT

public:
    TItemEx(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(0, 0)), QPen pen =QPen(QColor(0, 0, 0)), QBrush brush = QBrush(QColor(0, 0, 0)));
    virtual ~TItemEx();

    virtual void fCopy(TItemEx *ItemExFrom);

public:  //内联
    inline void fSetMousePressJS(const QString &js);
    inline QString fGetMousePressJS() const;

    inline void fSetLinkScene(QString &jumpSceneObjName);
    inline QString fGetLinkScene() const;

    inline void fSetDisconnect(bool disconnect);
    inline bool fGetDisconnect() const;

    void fSetName(QString &name)
    {
        m_Name = name;
    }
    const QString & fGetName() const
    {
        return m_Name;
    }

Q_SIGNALS:
    void mGotoLink(QString &m_JumpSceneObjName);
    void m_SendRunJs(QString &js);

protected:
    QString m_JumpSceneObjName;  ///<跳转场景OBJname
    QString m_MousePressJS;
    QString m_Name;            //名称
    bool m_Disconnect = false;   //断开连接
};

#endif // TITEM_EX_H