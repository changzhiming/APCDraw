#include "ItemEx.h"
#include <QMenu>
#include "QHBoxLayout"
#include <QDialog>
#include <QInputDialog>


TItemEx::TItemEx(QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush) :
    TItem(atScenePos, bounDingRect, pen, brush)
{

}

TItemEx::~TItemEx()
{}

void TItemEx::fCopy(TItemEx *ItemExFrom)
{
    if(!ItemExFrom)
        return;

    TItem::fCopy(ItemExFrom);

    this->setToolTip(ItemExFrom->toolTip());
    this->fSetMousePressJS(ItemExFrom->fGetMousePressJS());

    this->fSetLinkScene(ItemExFrom->fGetLinkScene());
    this->fSetDisconnect(ItemExFrom->fGetDisconnect());

}

inline void TItemEx::fSetMousePressJS(const QString &js)
{
    m_MousePressJS = js;
}

inline QString TItemEx::fGetMousePressJS() const
{
    return m_MousePressJS;
}

/*!
 * \brief TItemEx::fSetLinkScene 设置 Scene object名字为 \a jumpSceneObjNam 的场景为连接场景
 * \param jumpSceneObjNam
 */
inline void TItemEx::fSetLinkScene(QString &jumpSceneObjNam)
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
