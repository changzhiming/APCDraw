#include "aglobal.h"
#include "adrawmainwindow.h"
#include "ui/aprojectdirectorywindow.h"
#include "ageneralfunction.h"
#include "drawCore/Graphics/GraphicsPub.h"
#include "drawCore/Scene/Scene.h"
#include "drawCore/Undo/UndoAddDel.h"
#include "drawCore/Undo/UndoMoveDrag.h"
#include "drawCore/View/View.h"
#include "Dialog/aobjectanimation.h"
#include <QString>
#include "drawCore/Plot/graph.h"
#include "drawCore/Plot/bar.h"
#include "drawCore/Plot/piechart.h"
#include <QThread>

#include <QToolBox>
#include <QToolButton>
#include <QInputDialog>
#include <QDebug>
#include <QDockWidget>
#include <QLabel>
#include <QTextEdit>
#include <QString>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>

/*!
    \module APCUI
    \title 绘图软件UI模块
    \brief 包含所有的绘图组件显示UI和相关类
*/


/*!
  \class ADrawMainWindow
  \brief
  \inmodule APCUI
 */


/*!
 * \brief ADrawMainWindow::ADrawMainWindow \a parent
 */

ADrawMainWindow::ADrawMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_ProjectDirectoryWindow = new AProjectDirectoryWindow(this);
    m_GraphicsView = new TView(this);

    m_GraphicsView->setDragMode(QGraphicsView::RubberBandDrag);  //橡皮筋拖拉
    setCentralWidget(m_GraphicsView);

    createMenuAndToolBar();

    connect(m_ProjectDirectoryWindow, &AProjectDirectoryWindow::createNewWindow, this, &ADrawMainWindow::onCreateNewWindow);
    connect(m_GraphicsView, &TView::mMousePress, [=](){
        if(nullptr == m_GraphicsView->scene()) {
            QMessageBox::warning(this, tr("提示"), tr("请执行“文件--新建”，新建一个画布，再进行绘图")); return;
        }
        if(m_CurrentItemTypeAction.isNull())
            QMessageBox::warning(this, tr("提示"), tr("请选择一个绘图工具，再进行绘图"));
    });
}

/*!
  \brief ADrawMainWindow::~ADrawMainWindow
 */
ADrawMainWindow::~ADrawMainWindow()
{

}
ADrawMainWindow &ADrawMainWindow::getInstance()
{
    static ADrawMainWindow g_MainWidget(0);
    return g_MainWidget;
}

/*!
 \brief Create all the DockWidget and all associated events
*/
void ADrawMainWindow::createDockWidget()
{
    //工具箱
    m_toolsDockWidget=new QDockWidget(tr("工具箱"),this);
    m_toolsDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    m_toolsDockWidget->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    addDockWidget(Qt::RightDockWidgetArea, m_toolsDockWidget);
    //属性
    m_propertyDockWidget=new QDockWidget(tr("属性"),this);
    m_propertyDockWidget->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetMovable);
    addDockWidget(Qt::RightDockWidgetArea,m_propertyDockWidget);
    tabifyDockWidget(m_toolsDockWidget, m_propertyDockWidget);
    m_toolsDockWidget->raise();

    //工程
    m_projectDockWidget=new QDockWidget(tr("工程"), this);
    m_projectDockWidget->setWidget(m_ProjectDirectoryWindow);
    m_projectDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    m_projectDockWidget->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    addDockWidget(Qt::LeftDockWidgetArea, m_projectDockWidget);

    setTabPosition(Qt::RightDockWidgetArea, QTabWidget::East);
    setTabPosition(Qt::LeftDockWidgetArea, QTabWidget::West);

    setAnimated(true);
    setDockOptions(AnimatedDocks | AllowTabbedDocks | QMainWindow::ForceTabbedDocks);
}

/*!
 * \brief 创建工具栏Action \a name Action显示名字 \a iconDir 图标路径 \a data Action保存数据
 */
QAction * ADrawMainWindow::createToolsAction(QString name, QString iconDir, QVariant data)
{
    QAction *action = new QAction(QIcon(iconDir), name, this);
    action->setCheckable(true);
    action->setData(data);

    connect(action, &QAction::triggered, this, &ADrawMainWindow::updateCurrentItemType);
    return action;
}

/*!
 * \brief ADrawMainWindow::createToolButtonSetAction 绑定 \a action 到返回的QToolButton
 */
QToolButton *ADrawMainWindow::createToolButtonSetAction(QAction *action)
{
    QToolButton *tempToolButton = new QToolButton(this);
    tempToolButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    tempToolButton->setDefaultAction(action);
    tempToolButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    return tempToolButton;
}

/*!
 \brief 创建菜单栏
*/
void ADrawMainWindow::createMenuAndToolBar()
{
    createDockWidget();             // create DockWidget

    //创建Action
    m_UndoStack = new QUndoStack(this);;
    QAction * mActionUndo = m_UndoStack->createUndoAction(this, tr("撤销(&U)"));
    mActionUndo->setIcon(QIcon(tr("://pic/edit/Undo.png")));
    mActionUndo->setShortcut(QKeySequence::Undo);
    QAction * mActionRedo = m_UndoStack->createRedoAction(this, tr("重做(&R)"));
    mActionRedo->setIcon(QIcon(tr("://pic/edit/Redo.png")));
    mActionRedo->setShortcut(QKeySequence::Redo);

    QMenuBar * t_MenuBar =  new QMenuBar(this);
    setMenuBar(t_MenuBar);
    //文件菜单
    QMenu * t_FileMenu     = t_MenuBar->addMenu(tr("文件(&F)"));
    QMenu * t_Compile      = t_MenuBar->addMenu(tr("编辑(&E)"));
    QMenu * t_LookMenu     = t_MenuBar->addMenu(tr("查看(&V)"));
    QMenu * t_ToolMenu     = t_MenuBar->addMenu(tr("工具(&T)"));
    QMenu * t_FunctionMenu = t_MenuBar->addMenu(tr("功能(&S)"));
    QMenu * t_WindowMenu   = t_MenuBar->addMenu(tr("窗口(&W)"));
    QMenu * t_HelpMenu     = t_MenuBar->addMenu(tr("帮助(&H)"));

    Q_UNUSED(t_Compile)
    Q_UNUSED(t_LookMenu)
    Q_UNUSED(t_FunctionMenu)
    Q_UNUSED(t_WindowMenu)
    Q_UNUSED(t_HelpMenu)


    t_FileMenu->addAction(QIcon(QStringLiteral(":/menuImage/image/alarm.png")), tr("新建(&N)"),this, &ADrawMainWindow::onNewFile, QKeySequence::New);
    t_FileMenu->addAction(QIcon(QStringLiteral(":/menuImage/image/alarm.png")), tr("打开(&O)"),[this](){   }, QKeySequence::Open);
    t_FileMenu->addAction(QIcon(QStringLiteral(":/menuImage/image/alarm.png")), tr("关闭(&C)"),[](){qDebug()<<"关闭";}, QKeySequence::Close);
    t_FileMenu->addSeparator();
    t_FileMenu->addAction(QIcon(QStringLiteral(":/menuImage/image/alarm.png")), tr("保存(&S)"),[](){qDebug()<<"保存";}, QKeySequence::Save);
    t_FileMenu->addAction(QIcon(QStringLiteral(":/menuImage/image/alarm.png")), tr("删除(&D)"),[](){qDebug()<<"删除";}, QKeySequence::Delete);
    //

    QMenu *t_baseItemMenu = t_ToolMenu->addMenu(QIcon(QStringLiteral(":/menuImage/image/alarm.png")), tr("基本图元"));
    QMenu *t_CommonComponents = t_ToolMenu->addMenu(QIcon(QStringLiteral(":/menuImage/image/alarm.png")), tr("常用组件"));
    QMenu *t_basicControl = t_ToolMenu->addMenu(QIcon(QStringLiteral(":/menuImage/image/alarm.png")), tr("基本控件"));

    QAction *t_actionFree = createToolsAction(tr("释放(&F)"), QStringLiteral("://image/draw/Free.png"), TItemFactory::Base);
    QAction *t_actionLine = createToolsAction(tr("线(&N)"), QStringLiteral("://image/draw/Line.png"), TItemFactory::Line);
    QAction *t_actionEllipse = createToolsAction(tr("椭圆(&E)"), QStringLiteral("://image/draw/Ellipse.png"), TItemFactory::Ellipse);
    QAction *t_actionRect = createToolsAction(tr("矩形(&R)"), QStringLiteral("://image/draw/Rect.png"), TItemFactory::Rect);
    QAction *t_actionPolygon = createToolsAction(tr("任意多边形(&P)"), QStringLiteral("://image/draw/Polygon.png"), TItemFactory::Polygon);
    QAction *t_actionArc = createToolsAction(tr("圆弧(&A)"), QStringLiteral("://image/draw/Arc.png"), TItemFactory::Arc);
    QAction *t_actionText= createToolsAction(tr("文字(&T)"), QStringLiteral("://image/draw/Text.png"), TItemFactory::Text);
    QAction *t_actionValueText =  createToolsAction(tr("值文字(&V)"), QStringLiteral("://image/draw/ValueText.png"), TItemFactory::ValueText);
    QAction *t_actionPixmap = createToolsAction(tr("图片(&C)"), QStringLiteral("://image/draw/Pixmap.png"), TItemFactory::Pixmap);
    QAction *t_actionPath = createToolsAction(tr("路径(&H)"), QStringLiteral("://image/draw/Path.png"), TItemFactory::Path);
    QAction *t_actionLight = createToolsAction(tr("指示灯(&L)"), QStringLiteral("://image/draw/Light.png"), TItemFactory::Light);

    QAction *t_actionClock= createToolsAction(tr("表盘(&M)"), QStringLiteral("://image/draw/Clock.png"), TItemFactory::Clock);
    QAction *t_actionCurve= createToolsAction(tr("实时曲线(&C)"), QStringLiteral("://image/draw/Curve.png"), TItemFactory::Curve);

    QAction *t_actionButton = createToolsAction(tr("按钮(&U)"), QStringLiteral("://image/draw/Button.png"), TItemFactory::Button);
    QAction *t_actionInputEdit = createToolsAction(tr("文本框(&I)"), QStringLiteral("://image/draw/TextBox.png"), TItemFactory::InputEdit);
    QAction *t_actionProcessBar = createToolsAction(tr("进度条(&S)"), QStringLiteral("://image/draw/ProcessBar.png"), TItemFactory::ProcessBar);
    QAction *t_actionTable = createToolsAction(tr("表格(&B)"), QStringLiteral("://image/draw/Table.png"), TItemFactory::Table);

    t_baseItemMenu->addAction(t_actionFree);
    t_baseItemMenu->addAction(t_actionLine);
    t_baseItemMenu->addAction(t_actionEllipse);
    t_baseItemMenu->addAction(t_actionRect);
    t_baseItemMenu->addAction(t_actionPolygon);
    t_baseItemMenu->addAction(t_actionArc);
    t_baseItemMenu->addAction(t_actionText);
    t_baseItemMenu->addAction(t_actionValueText);
    t_baseItemMenu->addAction(t_actionPixmap);
    t_baseItemMenu->addAction(t_actionPath);
    t_baseItemMenu->addAction(t_actionLight);

    t_CommonComponents->addAction(t_actionClock);
    t_CommonComponents->addAction(t_actionCurve);

    t_basicControl->addAction(t_actionButton);
    t_basicControl->addAction(t_actionInputEdit);
    t_basicControl->addAction(t_actionProcessBar);
    t_basicControl->addAction(t_actionTable);

    //创建工具箱窗体
    QToolBox     * toolBox           = new QToolBox(this);
    QWidget      * t_BaseItemWidget  = new QWidget(this);
    QVBoxLayout  * t_vLayoutBaseItem = new QVBoxLayout(t_BaseItemWidget);
    t_vLayoutBaseItem->setContentsMargins(2, 2, 2, 2);

    QWidget      * t_CommonComponentsWidget        = new QWidget(this);
    QVBoxLayout  * t_vLayoutCommonComponentsWidget = new QVBoxLayout(t_CommonComponentsWidget);
    t_vLayoutCommonComponentsWidget->setContentsMargins(2, 2, 2, 2);

    QWidget      * t_basicControlWidget        = new QWidget(this);
    QVBoxLayout  * t_vLayoutbasicControlWidget = new QVBoxLayout(t_basicControlWidget);
    t_vLayoutbasicControlWidget->setContentsMargins(2, 2, 2, 2);


    t_vLayoutBaseItem->addWidget(createToolButtonSetAction(t_actionFree));
    t_vLayoutBaseItem->addWidget(createToolButtonSetAction(t_actionLine));
    t_vLayoutBaseItem->addWidget(createToolButtonSetAction(t_actionEllipse));
    t_vLayoutBaseItem->addWidget(createToolButtonSetAction(t_actionRect));
    t_vLayoutBaseItem->addWidget(createToolButtonSetAction(t_actionPolygon));
    t_vLayoutBaseItem->addWidget(createToolButtonSetAction(t_actionArc));
    t_vLayoutBaseItem->addWidget(createToolButtonSetAction(t_actionText));
    t_vLayoutBaseItem->addWidget(createToolButtonSetAction(t_actionValueText));
    t_vLayoutBaseItem->addWidget(createToolButtonSetAction(t_actionPixmap));
    t_vLayoutBaseItem->addWidget(createToolButtonSetAction(t_actionPath));
    t_vLayoutBaseItem->addWidget(createToolButtonSetAction(t_actionLight));
    t_vLayoutBaseItem->addStretch();

    t_vLayoutCommonComponentsWidget->addWidget(createToolButtonSetAction(t_actionClock));
    t_vLayoutCommonComponentsWidget->addWidget(createToolButtonSetAction(t_actionCurve));
    t_vLayoutCommonComponentsWidget->addStretch();

    t_vLayoutbasicControlWidget->addWidget(createToolButtonSetAction(t_actionButton));
    t_vLayoutbasicControlWidget->addWidget(createToolButtonSetAction(t_actionInputEdit));
    t_vLayoutbasicControlWidget->addWidget(createToolButtonSetAction(t_actionProcessBar));
    t_vLayoutbasicControlWidget->addWidget(createToolButtonSetAction(t_actionTable));
    t_vLayoutbasicControlWidget->addStretch();

    toolBox->addItem(t_BaseItemWidget, QIcon(QStringLiteral(":/menuImage/image/alarm.png")), tr("基本图元"));
    toolBox->addItem(t_CommonComponentsWidget, QIcon(QStringLiteral(":/menuImage/image/alarm.png")), tr("常用组件"));
    toolBox->addItem(t_basicControlWidget, QIcon(QStringLiteral(":/menuImage/image/alarm.png")), tr("基本控件"));

    m_toolsDockWidget->setWidget(toolBox);

}
/*!
 \brief 创建一个新的工程文件
*/
void ADrawMainWindow::onNewFile()
{

}

/*!
 \brief 创建新的窗体
*/
void ADrawMainWindow::onCreateNewWindow()
{  
    bool ok;
    QString t_windowName = QInputDialog::getText(this, tr("新建窗体"), tr("窗体名称："), QLineEdit::Normal, QString(), &ok);
    if(ok && !t_windowName.isEmpty()) {
        if(!m_windowNameToScene.contains(t_windowName)) {
          m_ProjectDirectoryWindow->addItemToTreeWidget(AProjectDirectoryWindow::WINDOWITEM, AProjectDirectoryWindow::CHILDWINDOWITEM, t_windowName);

          TScene * scene = new TScene(m_GraphicsView);
          scene->setObjectName(tr("sceneObj") + QString::number(m_CurrentMaxSceneId++));
          scene->fSetName(t_windowName);

          m_GraphicsView->setScene(scene);
          m_CurrentScene = scene; //set current scene
          scene->setSceneRect(0, 0, QApplication::desktop()->width(), QApplication::desktop()->height());
          m_windowNameToScene.insert(t_windowName, scene);         
          connect(scene, &TScene::mDropFinsh, this, &ADrawMainWindow::onDrawItem);
        } else {
            QMessageBox::warning(this, tr("警告"), tr("窗体名称不能相同"));
            return;
        }

    } else if(ok){
        QMessageBox::warning(this, tr("警告"), tr("输入不能为空"));
        return;
    }
}
//设当前绘画类型
void ADrawMainWindow::updateCurrentItemType()
{
    QAction * action = qobject_cast<QAction *>(sender());
    if(action) {
        if(m_CurrentItemTypeAction.isNull()) {
            m_CurrentItemTypeAction = action;
            return;
        }
        if(action != m_CurrentItemTypeAction) {
            m_CurrentItemTypeAction->setChecked(false);
            m_CurrentItemTypeAction = action;
        } else {
            m_CurrentItemTypeAction.clear();
        }
    }
}
/*!
 * \brief ADrawMainWindow::onDrawItem 创建Item 添加到场景
 */
void ADrawMainWindow::onDrawItem(double StartX, double StartY, double StopX, double StopY)
{
    if(m_CurrentItemTypeAction->data().toInt() == 0)
    {
        return;
    }
    for(int i=0; i< 10000; i++)
    {        
        PieChart *customPlot = new PieChart(QPoint(StartX + i*300, StartY + i*300), QRectF(QPointF(0, 0), QSize(StopX - StartX, StopY - StartY)));
        if(m_GraphicsView->scene() && customPlot) {
             m_GraphicsView->scene()->addItem(customPlot);
        }
    }


//    TItem *item = TItemFactory::fFactory(m_CurrentItemTypeAction->data().toInt(), QPointF(StartX, StartY), QRectF(QPointF(0, 0), QSize(StopX - StartX, StopY - StartY)));
//    if(m_GraphicsView->scene() && item) {
//        m_GraphicsView->scene()->addItem(item);
//    }
}
