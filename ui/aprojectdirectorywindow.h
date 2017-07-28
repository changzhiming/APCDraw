/*!
* @file aprojectdirectorywindow.h
* @brief 工程别表模块
*
* @author 常志明
* @version v1.0
* @date 2017.6.14
*/

#ifndef APROJECTDIRECTORYWINDOW_H
#define APROJECTDIRECTORYWINDOW_H
#include <aglobal.h>
#include <QWidget>

class QTreeWidgetItem;
class QHBoxLayout;
class QTreeWidget;


class AProjectDirectoryWindow : public QWidget
{
    Q_OBJECT
    Q_ENUMS(ItemType)

public:

    /*!
    * @brief 判断创建的列表类型
    */
    enum ItemType {
        NOITEM,
        TOPITEM,
        WINDOWITEM,
        DBITEM,
        JSITEM,
        VARIALE,
        CHILDWINDOWITEM,
        CHILDDBITEM,
        CHILDJSITEM,
        CHILDVARIALE,
    };

    explicit AProjectDirectoryWindow(QWidget *parent = 0);

    bool addItemToTreeWidget(ItemType parentItemType, ItemType childItemType, QString &showName);
    bool initTreeWidget();
    inline void setProjectName(QString name);
signals:
    void createNewWindow();  //创建新窗口
    void createDataBase();
    void createJS();
    void createVarible();

public slots:
    void onShowItemMenu(QTreeWidgetItem* item ,int column);

private:

    QPointer<QHBoxLayout> m_MainHBoxLayout;
    QTreeWidgetItem * m_treeItem = nullptr;
    QPointer<QTreeWidget> m_treeWidget;
};

#endif // APROJECTDIRECTORYWINDOW_H
