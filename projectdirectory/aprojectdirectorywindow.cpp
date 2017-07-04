#include "aprojectdirectorywindow.h"
#include <QTreeWidget>
#include <QStyle>
#include <QHBoxLayout>
#include <QMenu>
#include <QApplication>

AProjectDirectoryWindow::AProjectDirectoryWindow(QWidget *parent) : QWidget(parent)
{
    m_MainHBoxLayout = new QHBoxLayout(this);

    initTreeWidget();
    connect(m_treeWidget.data(), &QTreeWidget::itemPressed, this, &AProjectDirectoryWindow::onShowItemMenu);
}

/*!
 * \brief AProjectDirectoryWindow::addItemToTreeWidget
 * \a parentItemType  父亲窗体类型
 * \a childItemType  孩子窗体类型
 * \a showName   显示名字
 * return 如果成功返回 \c true 否则返回 \c false
 */
bool AProjectDirectoryWindow::addItemToTreeWidget(ItemType parentItemType, ItemType childItemType, QString &showName)
{     
    if(m_treeItem) {
        //创建子项目
        QTreeWidgetItem *widgetItem = new QTreeWidgetItem(childItemType);
        widgetItem->setText(0, showName);
        widgetItem->setIcon(0, style()->standardIcon((QStyle::StandardPixmap)21));

        if(parentItemType == NOITEM) {
            m_treeItem->addChild(widgetItem);
            m_treeWidget->expandItem(m_treeItem);
            return true;
        }
        //添加到树形列表
        int t_childCount = m_treeItem->childCount();
        for(int i = 0; i < t_childCount; i++)
        {
            if(m_treeItem->child(i)->type() == parentItemType) {
                m_treeItem->child(i)->addChild(widgetItem);
                m_treeWidget->expandItem(m_treeItem->child(i));
                return true;
            }
        }
    }
    return false;
}

/*!
* @brief 初始化treeWidget列表
* @access public
* @return void
*/
bool AProjectDirectoryWindow::initTreeWidget()
{
    if(!m_treeItem) {
        m_treeWidget = new QTreeWidget(this);

        m_MainHBoxLayout->addWidget(m_treeWidget);
        m_MainHBoxLayout->setContentsMargins(0, 0, 0, 0);
        m_treeWidget->setHeaderHidden(true);
        m_treeWidget->setIconSize(QSize(20, 20));

        m_treeItem = new QTreeWidgetItem(m_treeWidget, TOPITEM);
        m_treeItem->setIcon(0, style()->standardIcon((QStyle::StandardPixmap)21));
        m_treeItem->setText(0, tr("项目工程"));
        m_treeWidget->addTopLevelItem(m_treeItem);
        //添加列表
        addItemToTreeWidget(NOITEM, DBITEM, tr("数据库"));
        addItemToTreeWidget(NOITEM, WINDOWITEM, tr("窗口"));
        addItemToTreeWidget(NOITEM, JSITEM, tr("脚本"));
        return true;
    }
    return false;
}

/*!
* @brief 设置项目工程名称
* @access public
* @return void
*/
inline void AProjectDirectoryWindow::setProjectName(QString name)
{
    m_treeItem->setText(0, tr("项目工程") +QString("(%1)").arg(name));
}

/*!
* @brief 槽函数，显示列表项目弹出菜单， item 点击的item： column 点击的列
* @return void
*/
void AProjectDirectoryWindow::onShowItemMenu(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column)
    if(qApp->mouseButtons() == Qt::RightButton) {
        QMenu menu(m_treeWidget);

        switch(item->type())
        {
        case DBITEM:
            if (item->type() == DBITEM) {
                  menu.addAction(tr("新建数据库存储"), [=]() {
                      qDebug()<<"ss";

                  });
                  menu.exec(QCursor::pos());
            }
            break;
        case WINDOWITEM:
            if (item->type() == WINDOWITEM) {

                  menu.addAction(tr("新建窗口"), [=]() {
                      emit createNewWindow();  //创建新窗口
                  });

                  menu.exec(QCursor::pos());
            }
            break;
        case JSITEM:
            if (item->type() == JSITEM) {
                menu.addAction(tr("新建JS脚本"), [=]() {
                  qDebug()<<"ss";
                });
                 menu.exec(QCursor::pos());
            }
            break;
         default:
            break;
     }
    }
}
