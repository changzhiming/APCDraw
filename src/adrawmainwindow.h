/*
* @file adrawmainwindow
* @brief 绘制APCDraw软件的主窗体（头文件）
*
* @author 常志明
* @version v1.0
* @date 2017.6.13
*
*/

#ifndef ADRAWMAINWINDOW_H
#define ADRAWMAINWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include <aglobal.h>
class CycleRunScript;
class ValueChangeScript;
class AProjectDirectoryWindow;
class TScene;
class QUndoStack;
class TView;
class QToolButton;
class ADeviceInfo;
class TItem;
class QGraphicsItem;
class QTreeWidget;
class QTreeWidgetItem;

/*
* @class ADrawMainWindow
* @brief Draw 程序主窗包含所有模块窗体
*/
class ADrawMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    ~ADrawMainWindow();
    static ADrawMainWindow * getInstance();
public slots:
    QStringList getAlldeviceName();  //获取当前所有设备名

private slots:
    // menu
    void onNewFile();
    void openProject();
    void saveProject();

    //new create device and database etc
    void showCreateMenu(QTreeWidgetItem *item, int column);
    void onTreeDoubleClick(QTreeWidgetItem *item, int column);

    //add Item
    void addItemToScene(TScene *scene, QList<TItem *> itemList);
    void addItemToScene(TScene *scene, TItem * itemList);
    void deleteItemFromScene(TScene *scene, QList<TItem *> itemList);
    void deleteItemFromScene(TScene *scene, TItem * itemList);
    //view click
    void onViewClick(QGraphicsItem *item);
    void onViewDoubleClick(QGraphicsItem *item);

    void showAnimation(QGraphicsItem *item);     //item context menu
    void updateCurrentItemType();                //TItem Action updata
    //scene Window
    void addScene(TScene *scene, QTreeWidgetItem *item);
    void setCurrentScene(QString sceneName);
    void deleteScene(QString windowName, QTreeWidgetItem *item);

private:
    explicit ADrawMainWindow(QWidget *parent = 0);
    QTreeWidgetItem *generateWidgetItem(const QIcon &icon, const QString text);
    //Db save project
    void initAlltable(const QString &connectName);
    void saveDataBaseMsg(const QString &connectName, const QList<QStringList> &dbInfo);
    void saveGraphicsItem(const QString &connectName, const QList<TItem *> &itemList);
    template<class Proterty>
    QString getProteryHex(Proterty proterty);
    //
    void createMenuAndToolBar();
    void createDockWidget();
    QAction * createToolsAction(QString name, QString iconDir, QVariant data);
    QToolButton *createToolButtonSetAction(QAction *action);

private:
    //Action
    QAction *m_CopyAction = nullptr;
    QAction *m_PaseAction = nullptr;
    QAction *m_deleteAction =nullptr;

    QTreeWidget * m_ProjectDirectoryWindow = nullptr;          //工程目录;
    QPointer<TView> m_GraphicsView;                            //绘图显示窗体
    QPointer<QUndoStack> m_UndoStack;                          //恢复重做存储栈
    QPointer<QDockWidget> m_toolsDockWidget;                   //工具箱
    QPointer<QDockWidget> m_propertyDockWidget;                //图元属性
    QPointer<QDockWidget> m_projectDockWidget;                 //工程树形窗体
    TScene * m_CurrentScene = nullptr;                         //当前场景

    QPointer<QAction> m_CurrentItemTypeAction;                 //当前图元类型

    QHash<QString, TScene *> m_windowNameToScene;              //窗体名称和场景绑定
    QHash<QString, ADeviceInfo *> m_deviceInfoList;             //变量信息
    QList<DataBaseInfo *> m_dbInfoList;                         //数据库存储列表

    QString m_projectName;                                      //当前工程名字

    CycleRunScript * m_application = nullptr;                  //应用循环运行脚本
    QList<CycleRunScript *> m_cyclerunJsList;                  //循环运行脚本列表
    QList<ValueChangeScript *> m_valueChangeJsList;            //数值改变脚本列表

    TScene * m_ScenecopyContent = nullptr;                                  //复制内容指针
};


#endif // ADRAWMAINWINDOW_H
