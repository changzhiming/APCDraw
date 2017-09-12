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
#include "drawCore/Item/ItemFactory.h"
namespace Ui {
class ADrawMainWindow;
}
class AProjectDirectoryWindow;
class TScene;
class QUndoStack;
class TView;
class QToolButton;
/*
* @class ADrawMainWindow
* @brief Draw 程序主窗包含所有模块窗体
*/
class ADrawMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ~ADrawMainWindow();

    static ADrawMainWindow & getInstance();

    void createMenuAndToolBar();
    void createDockWidget();

    QAction * createToolsAction(QString name, QString iconDir, QVariant data);
    QToolButton *createToolButtonSetAction(QAction *action);
public slots:
    void onNewFile();
    void onCreateNewWindow();
    void updateCurrentItemType();
    void onDrawItem(QRectF itemRect);
private:
    explicit ADrawMainWindow(QWidget *parent = 0);

    QPointer<AProjectDirectoryWindow> m_ProjectDirectoryWindow; //工程目录;
    QPointer<TView> m_GraphicsView;                                     //绘图显示窗体
    QPointer<QUndoStack> m_UndoStack;                          //恢复重做存储栈
    QPointer<QDockWidget> m_toolsDockWidget;                         //工具箱
    QPointer<QDockWidget> m_propertyDockWidget;                    //图元属性
    QPointer<QDockWidget> m_projectDockWidget;                    //工程树形窗体
    TScene * m_CurrentScene;                          //当前场景
    QHash<QString, TScene *> m_windowNameToScene;              //窗体名称和场景绑定
    QPointer<QAction> m_CurrentItemTypeAction;                      //当前图元类型  

    int m_CurrentMaxSceneId = 0;                              //当前最大场景ID
};


#endif // ADRAWMAINWINDOW_H
