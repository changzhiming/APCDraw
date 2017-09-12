#ifndef TITEM_EX_H
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
    Q_PROPERTY(QString Name READ fGetName WRITE fSetName)

    Q_OBJECT

public:
    TItemEx(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(0, 0)), QPen pen =QPen(QColor(0, 0, 0)), QBrush brush = QBrush(QColor(0, 0, 0)));
    virtual ~TItemEx();
protected:
    virtual void fCopy(TItemEx *ItemExFrom);

public:  //内联
    inline void fSetMousePressJS(const QString &js);
    inline QString fGetMousePressJS() const;

    inline void fSetMouseDoublicJS(const QString &js);
    inline QString fGetMouseDoublicJS() const;

    inline void fSetMouseEnterJS(const QString &js);
    inline QString fGetMouseEnterJS() const;

    inline void fSetMouseLeaveJS(const QString &js);
    inline QString fGetMouseLeaveJS() const;

    inline void fSetLinkScene(QString jumpSceneObjName);
    inline QString fGetLinkScene() const;

    inline void fSetDisconnect(bool disconnect);
    inline bool fGetDisconnect() const;

    inline void fSetName(QString name) { m_Name = name;}
    inline const QString & fGetName() const {  return m_Name; }

Q_SIGNALS:
    void mGotoLink(QString &m_JumpSceneObjName);
    void m_SendRunJs(QString &js);

protected:
    QString m_JumpSceneObjName;  ///<跳转场景OBJname
    QString m_MousePressJS, m_MouseDoublickJS, m_MouseEnterJS, m_MouseLeaveJS;
    QString m_Name;              //名称
    bool m_Disconnect = false;   //断开连接
};

inline void TItemEx::fSetMousePressJS(const QString &js)
{    m_MousePressJS = js;}

inline QString TItemEx::fGetMousePressJS() const
{   return m_MousePressJS;}
inline void TItemEx::fSetMouseDoublicJS(const QString &js)
{ m_MouseDoublickJS = js;}
inline QString TItemEx::fGetMouseDoublicJS() const
{ return m_MouseDoublickJS;}

inline void TItemEx::fSetMouseEnterJS(const QString &js)
{m_MouseEnterJS = js;}
inline QString TItemEx::fGetMouseEnterJS() const
{ return m_MouseEnterJS;}

inline void TItemEx::fSetMouseLeaveJS(const QString &js)
{ m_MouseLeaveJS = js;}
inline QString TItemEx::fGetMouseLeaveJS() const
{ return m_MouseLeaveJS;}
/*!
 * \brief TItemEx::fSetLinkScene 设置 Scene object名字为 \a jumpSceneObjNam 的场景为连接场景
 * \param jumpSceneObjNam
 */
inline void TItemEx::fSetLinkScene(QString jumpSceneObjNam)
{
    m_JumpSceneObjName = jumpSceneObjNam;
}

inline QString TItemEx::fGetLinkScene() const
{
    return m_JumpSceneObjName;
}

/*!
 * \brief TItemEx::fGetDisconnect 获取连接状态
 */
inline bool TItemEx::fGetDisconnect() const
{
    return m_Disconnect;
}

/*!
 * \brief TItemEx::fSetDisconnect 设置连接状态为 \a disconnect
 */
inline void TItemEx::fSetDisconnect(bool disconnect)
{
    m_Disconnect = disconnect;
}

#endif // TITEM_EX_H
