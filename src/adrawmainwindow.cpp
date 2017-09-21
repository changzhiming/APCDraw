#include "aglobal.h"
#include "adrawmainwindow.h"
#include "ui/newdevice.h"
#include "ageneralfunction.h"
#include "drawCore/Graphics/GraphicsPub.h"
#include "drawCore/Scene/Scene.h"
#include "drawCore/Undo/UndoAddDel.h"
#include "drawCore/Undo/UndoMoveDrag.h"
#include "drawCore/View/View.h"
#include "Dialog/aobjectanimation.h"
#include "drawCore/Plot/plotpub.h"
#include "adeviceinfo.h"
#include "drawCore/Item/ItemFactory.h"
#include "Dialog/jsdesignwidget.h"
#include "ui/awindowproperty.h"
#include "drawCore/Scene/Scene.h"
#include "ui/newdatabase.h"
#include <QMap>
#include <QFileDialog>
#include "QSqlQuery"
#include <QCloseEvent>
#include <QToolBox>
#include <QToolButton>
#include <QInputDialog>
#include <QDebug>
#include <QDockWidget>
#include <QLabel>
#include <QTextEdit>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QTreeWidget>

#define Project tr("项目工程")
#define DataBaseSource tr("数据库源")

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

ADrawMainWindow::ADrawMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    // project tree
    m_ProjectDirectoryWindow = new QTreeWidget(this);
    m_ProjectDirectoryWindow->setHeaderHidden(true);
    m_ProjectDirectoryWindow->setIconSize(QSize(15, 15));

    QTreeWidgetItem * topLeveItem = generateWidgetItem(style()->standardIcon((QStyle::StandardPixmap)21), tr("项目工程"));
    topLeveItem->setFont(0, QFont("微软雅黑", 12));
    m_ProjectDirectoryWindow->addTopLevelItem(topLeveItem);
    topLeveItem->addChild(generateWidgetItem(style()->standardIcon((QStyle::StandardPixmap)21), tr("数据库源")));
    topLeveItem->addChild(generateWidgetItem(style()->standardIcon((QStyle::StandardPixmap)21), tr("数据存储")));
    topLeveItem->addChild(generateWidgetItem(style()->standardIcon((QStyle::StandardPixmap)21), tr("窗体")));
    topLeveItem->addChild(generateWidgetItem(style()->standardIcon((QStyle::StandardPixmap)21), tr("设备")));
    QTreeWidgetItem * globalScriptItem = generateWidgetItem(style()->standardIcon((QStyle::StandardPixmap)21), tr("全局脚本"));
    topLeveItem->addChild(globalScriptItem);

    globalScriptItem->addChild(generateWidgetItem(style()->standardIcon((QStyle::StandardPixmap)21), tr("应用程序动作")));
    globalScriptItem->addChild(generateWidgetItem(style()->standardIcon((QStyle::StandardPixmap)21), tr("数据改变动作")));
    topLeveItem->setExpanded(true);
    globalScriptItem->setExpanded(true);
    // show view
    m_GraphicsView = new TView(this);
    m_GraphicsView->setDragMode(QGraphicsView::RubberBandDrag);  //橡皮筋拖拉
    setCentralWidget(m_GraphicsView);

    createMenuAndToolBar();

    connect(m_ProjectDirectoryWindow, &QTreeWidget::itemPressed, this, &ADrawMainWindow::showCreateMenu);
    connect(m_ProjectDirectoryWindow, &QTreeWidget::itemDoubleClicked, this, &ADrawMainWindow::onTreeDoubleClick);

    connect(m_GraphicsView, &TView::mMousePress, this, &ADrawMainWindow::onViewClick);
    connect(m_GraphicsView, &TView::mouseDoubleClick, this, &ADrawMainWindow::onViewDoubleClick);
}

/*!
  \brief ADrawMainWindow::~ADrawMainWindow
 */
ADrawMainWindow *ADrawMainWindow::getInstance()
{
    static ADrawMainWindow *g_DrawMainWindowOnce = new ADrawMainWindow(nullptr);
    return g_DrawMainWindowOnce;
}

ADrawMainWindow::~ADrawMainWindow()
{
    IF_TRUE_RUN(m_application, delete m_application);
    foreach (auto * Script, m_cyclerunJsList) {
        delete Script;
    }
    foreach (auto * Script, m_valueChangeJsList) {
        delete Script;
    }
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
    m_UndoStack = new QUndoStack(this);
    QAction * mActionUndo = m_UndoStack->createUndoAction(this, tr("撤销(&U)"));
    mActionUndo->setIcon(QIcon(tr(":/image/edit/Undo.png")));
    mActionUndo->setShortcut(QKeySequence::Undo);
    QAction * mActionRedo = m_UndoStack->createRedoAction(this, tr("重做(&R)"));
    mActionRedo->setIcon(QIcon(tr(":/image/edit/Redo.png")));
    mActionRedo->setShortcut(QKeySequence::Redo);

    createDockWidget();             // create DockWidget

    //创建Action
    QMenuBar * t_MenuBar =  menuBar();

    //文件菜单
    QMenu * t_FileMenu     = t_MenuBar->addMenu(tr("文件(&F)"));
    QMenu * t_Compile      = t_MenuBar->addMenu(tr("编辑(&E)"));
    QMenu * t_LookMenu     = t_MenuBar->addMenu(tr("查看(&V)"));
    QMenu * t_ToolMenu     = t_MenuBar->addMenu(tr("工具(&T)"));
    QMenu * t_FunctionMenu = t_MenuBar->addMenu(tr("功能(&S)"));
    QMenu * t_WindowMenu   = t_MenuBar->addMenu(tr("窗口(&W)"));
    QMenu * t_HelpMenu     = t_MenuBar->addMenu(tr("帮助(&H)"));

    Q_UNUSED(t_LookMenu)
    Q_UNUSED(t_FunctionMenu)
    Q_UNUSED(t_WindowMenu)
    //
    t_FileMenu->addAction(QIcon(QStringLiteral(":/menuImage/image/alarm.png")), tr("新建(&N)"),this, &ADrawMainWindow::onNewFile, QKeySequence::New);
    t_FileMenu->addAction(QIcon(QStringLiteral(":/menuImage/image/alarm.png")), tr("打开(&O)"),this, &ADrawMainWindow::openProject, QKeySequence::Open);
    t_FileMenu->addAction(QIcon(QStringLiteral(":/menuImage/image/alarm.png")), tr("关闭(&C)"),this, []{}, QKeySequence::Close);
    t_FileMenu->addSeparator();
    t_FileMenu->addAction(QIcon(QStringLiteral(":/menuImage/image/alarm.png")), tr("保存(&S)"),this, &ADrawMainWindow::saveProject, QKeySequence::Save);
    //
    t_Compile->addAction(tr("剪切(&T)"),[this](){}, QKeySequence::Cut);
    m_CopyAction = t_Compile->addAction(tr("复制(&C)"),[this](){}, QKeySequence::Copy);
    m_PaseAction = t_Compile->addAction(tr("粘贴(&P)"),[this](){}, QKeySequence::Paste);
    m_deleteAction = t_Compile->addAction(QIcon(QStringLiteral(":/menuImage/image/alarm.png")), tr("删除(&D)"),[this](){qDebug()<<"删除";}, QKeySequence::Delete);

    t_Compile->addSeparator();
    t_Compile->addAction(mActionUndo);
    t_Compile->addAction(mActionRedo);
    //
    t_HelpMenu->addAction(tr("关于(&A)"), [this]{
        QMessageBox::information(this, tr("关于"), tr("组态"));
    });

    QMenu *t_baseItemMenu = t_ToolMenu->addMenu(QIcon(QStringLiteral(":/menuImage/image/alarm.png")), tr("基本图元"));
    QMenu *t_CommonComponents = t_ToolMenu->addMenu(QIcon(QStringLiteral(":/menuImage/image/alarm.png")), tr("常用组件"));
    QMenu *t_basicControl = t_ToolMenu->addMenu(QIcon(QStringLiteral(":/menuImage/image/alarm.png")), tr("基本控件"));

    QAction *t_actionFree = createToolsAction(tr("释放(&F)"), QStringLiteral("://image/draw/Free.png"), TItemFactory::Base);
    QAction *t_actionLine = createToolsAction(tr("线(&N)"), QStringLiteral("://image/draw/Line.png"), TItemFactory::Line);
    QAction *t_actionEllipse = createToolsAction(tr("椭圆(&E)"), QStringLiteral("://image/draw/Ellipse.png"), TItemFactory::Ellipse);
    QAction *t_actionProcessBar = createToolsAction(tr("进度条(&S)"), QStringLiteral("://image/draw/ProcessBar.png"), TItemFactory::ProcessBar);
    QAction *t_actionRect = createToolsAction(tr("矩形(&R)"), QStringLiteral("://image/draw/Rect.png"), TItemFactory::Rect);
    QAction *t_actionPolygon = createToolsAction(tr("任意多边形(&P)"), QStringLiteral("://image/draw/Polygon.png"), TItemFactory::Polygon);
    QAction *t_actionArc = createToolsAction(tr("圆弧(&A)"), QStringLiteral("://image/draw/Arc.png"), TItemFactory::Arc);
    QAction *t_actionText= createToolsAction(tr("文字(&T)"), QStringLiteral("://image/draw/Text.png"), TItemFactory::Text);
    QAction *t_actionValueText =  createToolsAction(tr("值文字(&V)"), QStringLiteral("://image/draw/ValueText.png"), TItemFactory::ValueText);
    QAction *t_actionPixmap = createToolsAction(tr("图片(&C)"), QStringLiteral("://image/draw/Pixmap.png"), TItemFactory::Pixmap);
    QAction *t_actionPath = createToolsAction(tr("路径(&H)"), QStringLiteral("://image/draw/Path.png"), TItemFactory::Path);
    QAction *t_actionLight = createToolsAction(tr("指示灯(&L)"), QStringLiteral("://image/draw/Light.png"), TItemFactory::Light);

    QAction *t_actionCurve= createToolsAction(tr("实时曲线(&C)"), QStringLiteral("://image/draw/Curve.png"), TItemFactory::_Graph);
    QAction *t_actionBar= createToolsAction(tr("柱形图(&C)"), QStringLiteral("://image/draw/Curve.png"), TItemFactory::_Bar);
    QAction *t_actionPieChart= createToolsAction(tr("饼图(&C)"), QStringLiteral("://image/draw/Curve.png"), TItemFactory::_Pie);
    QAction *t_actionInstrument= createToolsAction(tr("仪表盘(&M)"), QStringLiteral("://image/draw/Clock.png"), TItemFactory::_Instrument);

    QAction *t_actionButton = createToolsAction(tr("按钮(&U)"), QStringLiteral("://image/draw/Button.png"), TItemFactory::Button);
    QAction *t_actionInputEdit = createToolsAction(tr("文本框(&I)"), QStringLiteral("://image/draw/TextBox.png"), TItemFactory::InputEdit);
    QAction *t_actionTable = createToolsAction(tr("表格(&B)"), QStringLiteral("://image/draw/Table.png"), TItemFactory::Table);

    t_baseItemMenu->addAction(t_actionFree);
    t_baseItemMenu->addAction(t_actionLine);
    t_baseItemMenu->addAction(t_actionEllipse);
    t_baseItemMenu->addAction(t_actionProcessBar);
    t_baseItemMenu->addAction(t_actionRect);
    t_baseItemMenu->addAction(t_actionPolygon);
    t_baseItemMenu->addAction(t_actionArc);
    t_baseItemMenu->addAction(t_actionText);
    t_baseItemMenu->addAction(t_actionValueText);
    t_baseItemMenu->addAction(t_actionPixmap);
    t_baseItemMenu->addAction(t_actionPath);
    t_baseItemMenu->addAction(t_actionLight);

    t_CommonComponents->addAction(t_actionCurve);
    t_CommonComponents->addAction(t_actionBar);
    t_CommonComponents->addAction(t_actionPieChart);
    t_CommonComponents->addAction(t_actionInstrument);

    t_basicControl->addAction(t_actionButton);
    t_basicControl->addAction(t_actionInputEdit); 
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
    t_vLayoutBaseItem->addWidget(createToolButtonSetAction(t_actionProcessBar));
    t_vLayoutBaseItem->addWidget(createToolButtonSetAction(t_actionRect));
    t_vLayoutBaseItem->addWidget(createToolButtonSetAction(t_actionPolygon));
    t_vLayoutBaseItem->addWidget(createToolButtonSetAction(t_actionArc));
    t_vLayoutBaseItem->addWidget(createToolButtonSetAction(t_actionText));
    t_vLayoutBaseItem->addWidget(createToolButtonSetAction(t_actionValueText));
    t_vLayoutBaseItem->addWidget(createToolButtonSetAction(t_actionPixmap));
    t_vLayoutBaseItem->addWidget(createToolButtonSetAction(t_actionPath));
    t_vLayoutBaseItem->addWidget(createToolButtonSetAction(t_actionLight));
    t_vLayoutBaseItem->addStretch();

    t_vLayoutCommonComponentsWidget->addWidget(createToolButtonSetAction(t_actionCurve));
    t_vLayoutCommonComponentsWidget->addWidget(createToolButtonSetAction(t_actionBar));
    t_vLayoutCommonComponentsWidget->addWidget(createToolButtonSetAction(t_actionPieChart));
    t_vLayoutCommonComponentsWidget->addWidget(createToolButtonSetAction(t_actionInstrument));
    t_vLayoutCommonComponentsWidget->addStretch();

    t_vLayoutbasicControlWidget->addWidget(createToolButtonSetAction(t_actionButton));
    t_vLayoutbasicControlWidget->addWidget(createToolButtonSetAction(t_actionInputEdit));
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
    QString FileDir = QFileDialog::getSaveFileName(this, tr("新建工程"), "", "*.db");
    if(!FileDir.isEmpty()) {
        if(AGeneralFunction::addDbCon("QSQLITE", "", FileDir, "", "" , "projectSql")) {
            AGeneralFunction::removeDbCon("projectSql");
            AGeneralFunction::addDbCon("QSQLITE", "", FileDir, "", "" , "projectSql");
        }
        this->setWindowTitle(this->windowTitle() + QString("(%1)").arg(FileDir));
        m_projectName = FileDir;
    }
}
void ADrawMainWindow::openProject()
{
    QString fileName =  QFileDialog::getOpenFileName(this, tr("打开工程"), "", "*.db");
    if(!fileName.isEmpty()) {
        if(AGeneralFunction::addDbCon("QSQLITE", "", fileName, "", "" , "projectSql")) {
            AGeneralFunction::removeDbCon("projectSql");
            if(!AGeneralFunction::addDbCon("QSQLITE", "", fileName, "", "" , "projectSql")) {
                QMessageBox::warning(this, tr("错误"), tr("无效工程文件"), tr("退出"));
                return;
            }
        }
        m_projectName = fileName;
    }
}
void ADrawMainWindow::saveProject()
{
    if(!m_projectName.isEmpty()) {    
        initAlltable("projectSql");
        QList<TItem *> list;
        m_CurrentScene->fGetItemsList(list);
        saveGraphicsItem("projectSql", list);
    }
}

//显示创建变量， 窗体， 脚本等菜单
void ADrawMainWindow::showCreateMenu(QTreeWidgetItem *item, int column)
{
    IF_TRUE_RUN(m_projectName.isEmpty(), QMessageBox::warning(this, tr("警告"), tr("请新建工程或打开工程"), tr("是")); return)
    IF_TRUE_RUN(QApplication::mouseButtons() != Qt::RightButton || !item->parent(), return);
    QMenu menu(this);
    QString itemName = item->text(column), itemParentName = item->parent()->text(column);

    if(itemParentName == tr("项目工程") && itemName == tr("数据库源")) {
        menu.addAction(tr("新建数据库"), [this, item]{
            DataBaseInfo *databaseInfo = new DataBaseInfo;
            NewDataBase *dataBaseWidget = new NewDataBase(databaseInfo, this);
            dataBaseWidget->show();

            connect(dataBaseWidget, &NewDataBase::ok, [this, item](DataBaseInfo *dbInfo){
                m_dbInfoList.append(dbInfo);
                item->addChild(this->generateWidgetItem(style()->standardIcon((QStyle::StandardPixmap)21), dbInfo->m_DataBaseInfoName));
            });
            connect(dataBaseWidget, &NewDataBase::cancle, [this, item](DataBaseInfo *dbInfo){
               delete  dbInfo;
            });
        });
    }
    if(itemParentName == tr("项目工程") && itemName == tr("数据存储")) {
        menu.addAction(tr("新建数据存储"), [this, item]{

        });
    }

    if(itemParentName == tr("项目工程") && itemName == tr("窗体")) {
        menu.addAction(tr("新建窗体"), [this, item]{
            TScene * scene = new TScene(m_GraphicsView);
            AWindowProperty *windowProperty = new AWindowProperty(scene, this);
            windowProperty->setAllWindowName(m_windowNameToScene.keys());
            windowProperty->show();

            connect(windowProperty, &AWindowProperty::okSave, [this, item](TScene *scene){
                addScene(scene, item);
            });
            connect(windowProperty, &AWindowProperty::cancle, [this](TScene *scene){
                delete scene;
            });
        });
    }

    if(itemParentName == tr("项目工程") && itemName == tr("设备")) {
        menu.addAction(tr("新建设备"), [this, item]{
            ADeviceInfo *deviceInfo = new ADeviceInfo(this);
            NewDevice *new_device = new NewDevice(deviceInfo, this);
            new_device->setexistVarName(m_deviceInfoList.keys());

            connect(new_device, &NewDevice::ensure, [this, item](ADeviceInfo *deviceInfo){
                m_deviceInfoList.insert(deviceInfo->m_deviceName, deviceInfo);
                item->addChild(this->generateWidgetItem(style()->standardIcon((QStyle::StandardPixmap)21), deviceInfo->m_deviceName));
            });
            connect(new_device, &NewDevice::cancle, [this](ADeviceInfo *deviceInfo){
               delete deviceInfo;
            });
            new_device->show();
        });
    }

    if(itemParentName == tr("窗体")) {
        menu.addAction(tr("打开"), [this, itemName]{
           setCurrentScene(itemName);
        });
        menu.addAction(tr("复制"), [this, itemName]{
            m_ScenecopyContent = m_windowNameToScene.value(itemName);
        });
        menu.addAction(tr("粘贴"), [this, item]{
            TScene * t_scene = dynamic_cast<TScene *>(m_ScenecopyContent);
            if(t_scene) {
                addScene(t_scene->fCopy(), item);
            }
        });

        menu.addAction(tr("删除"), [this, itemName, item]{
            deleteScene(itemName, item);
        });

        menu.addSeparator();
        menu.addAction(tr("窗口属性"), [this, itemName]{
            TScene *scene = m_windowNameToScene.value(itemName);
            AWindowProperty *windowProperty = new AWindowProperty(scene, this);

            QStringList allWindow = m_windowNameToScene.keys();
            allWindow.removeOne(itemName);
            windowProperty->show();
        });
        menu.addAction(tr("窗口动作"), [this, itemName]{
            CycleRunScript *t_cycleRun = nullptr;
            foreach (CycleRunScript *cycleRun, m_cyclerunJsList) {
                IF_TRUE_RUN(cycleRun->m_windowName == itemName, t_cycleRun = cycleRun; break)
            }

            if(!t_cycleRun) {
                t_cycleRun = new CycleRunScript;
                t_cycleRun->m_windowName = itemName;
                m_cyclerunJsList.append(t_cycleRun);
            }
            JSDesignWidget * jsDesignWidget = new JSDesignWidget(tr("窗口程序动作"), this);
            jsDesignWidget->addJSWidget(tr("进入窗体"), t_cycleRun->m_enterJs);
            jsDesignWidget->addJSWidget(tr("窗体运行时周期执行"), t_cycleRun->m_cycleRunJs);
            jsDesignWidget->addJSWidget(tr("退出窗体"), t_cycleRun->m_leaveJs);
            jsDesignWidget->setIntervalTime(t_cycleRun->m_cycleRunIntervalTime);

            connect(jsDesignWidget, &JSDesignWidget::okData, [this, t_cycleRun](QMap<QString, QString> jsmap, QList<int> runInterValList){
                IF_TRUE_RUN(jsmap.contains(tr("进入窗体")), t_cycleRun->m_enterJs = jsmap.value(tr("进入窗体")))
                if(jsmap.contains(tr("窗体运行时周期执行"))) {
                    t_cycleRun->m_cycleRunJs = jsmap.value(tr("窗体运行时周期执行"));
                    t_cycleRun->m_cycleRunIntervalTime =runInterValList.at(jsmap.keys().indexOf(tr("窗体运行时周期执行")));
                }
                IF_TRUE_RUN(jsmap.contains(tr("退出窗体")), t_cycleRun->m_leaveJs = jsmap.value(tr("退出窗体")))
            });
            jsDesignWidget->show();
        });
    }

    if(itemParentName == tr("全局脚本") && itemName == tr("数据改变动作")) {
        menu.addAction(tr("新建动作"), [this, item]{
            ValueChangeScript *valueScript = new ValueChangeScript;
            JSDesignWidget * jsDesignWidget = new JSDesignWidget(getAlldeviceName(), valueScript, tr("数据改变动作"), this);
            jsDesignWidget->addJSWidget(tr("数值改变执行"));

            connect(jsDesignWidget, &JSDesignWidget::okVariableData, [this, item, valueScript](ValueChangeScript *t_valueChanged){
                m_valueChangeJsList.append(t_valueChanged);
                item->addChild(this->generateWidgetItem(style()->standardIcon((QStyle::StandardPixmap)21), valueScript->m_scriptValueName));
            });
            connect(jsDesignWidget, &JSDesignWidget::cancle, [this, valueScript]{
                delete valueScript;
            });
            jsDesignWidget->show();
        });
    }

    menu.exec(QCursor::pos());
}

//双击左侧树形列表项  . 显示相应窗口
void ADrawMainWindow::onTreeDoubleClick(QTreeWidgetItem *item, int column)
{
    IF_TRUE_RUN(m_projectName.isEmpty(), QMessageBox::warning(this, tr("警告"), tr("请新建工程或打开工程"), tr("是")); return)
    IF_TRUE_RUN(!item->parent(), return);
    QString itemName = item->text(column), itemParentName = item->parent()->text(column);

    IF_TRUE_RUN(itemParentName == tr("窗体"), setCurrentScene(itemName); return)

    if(itemParentName == tr("全局脚本")) {
        if(itemName == tr("应用程序动作")) {
            IF_TRUE_RUN(m_projectName.isEmpty(), QMessageBox::warning(this, tr("警告"), tr("请新建工程或打开工程"), tr("是")); return);
            IF_TRUE_RUN(!m_application, m_application = new CycleRunScript; m_application->m_windowName = QLatin1String("app"))

            JSDesignWidget * jsDesignWidget = new JSDesignWidget(tr("应用程序动作"), this);
            jsDesignWidget->addJSWidget(tr("进入程序"), m_application->m_enterJs);
            jsDesignWidget->addJSWidget(tr("程序运行时周期执行"), m_application->m_cycleRunJs);
            jsDesignWidget->addJSWidget(tr("退出程序"), m_application->m_leaveJs);
            jsDesignWidget->setIntervalTime(m_application->m_cycleRunIntervalTime);

            connect(jsDesignWidget, &JSDesignWidget::okData, [this](QMap<QString, QString> jsmap, QList<int> runInterValList){
                IF_TRUE_RUN(jsmap.contains(tr("进入程序")), m_application->m_enterJs = jsmap.value(tr("进入程序")))
                if(jsmap.contains(tr("窗体运行时周期执行"))) {
                    m_application->m_cycleRunJs = jsmap.value(tr("窗体运行时周期执行"));
                    m_application->m_cycleRunIntervalTime =runInterValList.at(jsmap.keys().indexOf(tr("窗体运行时周期执行")));
                }
                IF_TRUE_RUN(jsmap.contains(tr("退出程序")), m_application->m_leaveJs = jsmap.value(tr("退出程序")))
            });
            jsDesignWidget->show();
        }
    }
    if(itemParentName == tr("数据改变动作")) {
        ValueChangeScript *valueScript = nullptr;
        foreach (auto *variable, m_valueChangeJsList) {
            IF_TRUE_RUN(variable->m_scriptValueName == itemName, valueScript = variable; break)
        }
        if(valueScript) {
            JSDesignWidget * jsDesignWidget = new JSDesignWidget(getAlldeviceName(), valueScript, tr("数据改变动作"), this);
            jsDesignWidget->addJSWidget(tr("数值改变执行"), valueScript->m_valueJs);
            jsDesignWidget->show();
        }
    }
    if(itemParentName == tr("设备")) {
        ADeviceInfo *deviceInfo = nullptr;
        foreach (auto *device, m_deviceInfoList) {
            IF_TRUE_RUN(device->m_deviceName == itemName, deviceInfo = device; break)
        }
        if(deviceInfo) {
            NewDevice *new_device = new NewDevice(deviceInfo, this);
            new_device->setexistVarName(m_deviceInfoList.keys());
            new_device->show();
        }
    }
    if(itemParentName == tr("数据库源")) {
        DataBaseInfo *databaseInfo = nullptr;
        foreach (auto *dbInfo, m_dbInfoList) {
            IF_TRUE_RUN(dbInfo->m_DataBaseInfoName == itemName, databaseInfo = dbInfo; break)
        }
        if(databaseInfo) {
            NewDataBase *dataBaseWidget = new NewDataBase(databaseInfo, this);
            dataBaseWidget->show();
        }
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
//添加新的场景窗体
void ADrawMainWindow::addScene(TScene *scene, QTreeWidgetItem *item)
{
    IF_TRUE_RUN(!scene || !item, return)

    QString sceneName = scene->fGetName();
    m_windowNameToScene.insert(sceneName, scene);
    setCurrentScene(sceneName);

    item->addChild(this->generateWidgetItem(style()->standardIcon((QStyle::StandardPixmap)21), sceneName));
    connect(scene, &TScene::mDropFinsh, [this](QRectF itemRect){
        if(!m_CurrentItemTypeAction.isNull() && m_CurrentItemTypeAction->data().toInt()) {
            TItem *item = TItemFactory::fFactory(m_CurrentItemTypeAction->data().toInt(), QPointF(itemRect.x(), itemRect.y()), QRectF(QPointF(0, 0), itemRect.size()));
            addItemToScene(m_CurrentScene, item);
        }
    });
}
//根据 icon和text创建TreeWidgetItem
QTreeWidgetItem *ADrawMainWindow::generateWidgetItem(const QIcon &icon, const QString text)
{
    QTreeWidgetItem * widgetItem = new QTreeWidgetItem();
    widgetItem->setIcon(0, icon);
    widgetItem->setText(0, text);
    return widgetItem;
}

void ADrawMainWindow::initAlltable(const QString &connectName)
{
    QStringList item_property, item_datatype;
    item_property<<"type"<<"objaddr"<<"z_value"<<"pen"<<"brush"<<"pos"<<"bounding_rect"<<"objname";
    item_datatype<<"int"<<"int"<<"real"<<"text"<<"text"<<"text"<<"text"<<"text";
    AGeneralFunction::createTable(connectName, "item", item_property, item_datatype);


    AGeneralFunction::execSql(connectName, QString("create table if not exists database_msg(driver_name text, "
                                                      "host_name text, db_name text, user_name text, passwd text, connect_name text)"));
    AGeneralFunction::execSql(connectName, tr("delete from database_msg"));

    AGeneralFunction::execSql(connectName, QString("create table if not exists graphics_item(type INTERGE, data BOLB)"));
    AGeneralFunction::execSql(connectName, tr("delete from graphics_item"));
}

void ADrawMainWindow::saveDataBaseMsg(const QString &connectName, const QList<QStringList> &dbInfo)
{
    AGeneralFunction::execSql(connectName, QString("create table if not exists database_msg(driver_name text, "
                                                      "host_name text, db_name text, user_name text, passwd text, connect_name text)"));
    foreach (QStringList db, dbInfo) {
        QString sql = QString("insert into database_msg values('%1', '%2', '%3', '%4', '%5', '%6')").arg(db.at(0)).arg(db.at(1)).arg(db.at(2)).arg(db.at(3)).arg(db.at(4)).arg(db.at(5));

        AGeneralFunction::execSql(connectName, sql);
    }
}

void ADrawMainWindow::saveGraphicsItem(const QString &connectName, const QList<TItem *> &itemList)
{
    AGeneralFunction::execSql(connectName, QStringLiteral("delete from item"));
    foreach(auto item, itemList)
    {
        QString sql = QString("insert into item values(");
        sql += QString("%1 %2 ").arg(item->fGetType()).arg(',');
        sql += QString("%1 %2 ").arg((int)item).arg(',');
        sql += QString("%1 %2 ").arg(item->fGetZValue()).arg(',');
        sql += QString("'%1' %2 ").arg(getProteryHex(item->fGetPen())).arg(',');
        sql += QString("'%1' %2 ").arg(getProteryHex(item->fGetBrush())).arg(',');
        sql += QString("'%1' %2 ").arg(getProteryHex(item->fGetScenePos())).arg(',');
        sql += QString("'%1' %2 ").arg(getProteryHex(item->fGetBoundingRect())).arg(',');
        sql += QString("'%1' %2 ").arg(item->objectName()).arg(')');
        AGeneralFunction::execSql(connectName, sql);
    }
}
template<class Proterty>
QString ADrawMainWindow::getProteryHex(Proterty proterty)
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::ReadWrite);
    stream<<proterty;
    return data.toHex();
}
//根据窗体名称显示相应窗体
void ADrawMainWindow::setCurrentScene(QString sceneNamee)
{
    m_GraphicsView->setScene(m_windowNameToScene.value(sceneNamee));
    m_CurrentScene = m_windowNameToScene.value(sceneNamee); //set current scene
}

void ADrawMainWindow::deleteScene(QString windowName, QTreeWidgetItem *item)
{
    m_windowNameToScene.remove(windowName);
    setCurrentScene("");
    delete item;
    delete m_windowNameToScene.value(windowName);
}

void ADrawMainWindow::addItemToScene(TScene *scene, QList<TItem *> itemList)
{
    if(scene) {
        TUndoAddDel *Undo = new TUndoAddDel(m_CurrentScene, itemList);
        Undo->fSetOperation(TUndoAddDel::OPERATION_ADD);
        m_UndoStack->push(Undo);
    }
}

void ADrawMainWindow::addItemToScene(TScene *scene, TItem * itemList)
{
    QList<TItem *> list;
    list.append(itemList);
    addItemToScene(scene, list);
}
void ADrawMainWindow::deleteItemFromScene(TScene *scene, QList<TItem *> itemList)
{
    if(scene) {
        TUndoAddDel *Undo = new TUndoAddDel(m_CurrentScene, itemList);
        Undo->fSetOperation(TUndoAddDel::OPERATION_DEL);
        m_UndoStack->push(Undo);
    }
}

void ADrawMainWindow::deleteItemFromScene(TScene *scene, TItem * itemList)
{
    QList<TItem *> list;
    list.append(itemList);
    deleteItemFromScene(scene, list);
}
//单击窗体
void ADrawMainWindow::onViewClick(QGraphicsItem *item)
{
    if(m_projectName.isEmpty()) {
        QMessageBox::warning(this, tr("提示"), tr("请执行“文件--新建”，新建一个工程，再进行绘图"));
        return;
    }
    if(nullptr == m_CurrentScene) {
        QMessageBox::warning(this, tr("提示"), tr("请执行“窗口右键新建”，新建一个画布，再进行绘图"));
        return;
    }
    if(item != nullptr && QApplication::mouseButtons() == Qt::RightButton)
       showAnimation(item);

}
//双击窗体
void ADrawMainWindow::onViewDoubleClick(QGraphicsItem *item)
{
    IF_TRUE_RUN(item != nullptr && QApplication::mouseButtons() == Qt::RightButton, showAnimation(item))
}
//显示图元菜单
void ADrawMainWindow::showAnimation(QGraphicsItem *item)
{
    QMenu menu;
    menu.addAction(tr("对象动作"), [this, item]() {
        AObjectAnimation *obj = new AObjectAnimation(dynamic_cast<TItemEx *>(item), this);
        obj->setAllDeviceName(ADrawMainWindow::getInstance()->getAlldeviceName());
        obj->show();
    });

    menu.addAction(tr("图层设置"), [this, item](){
        double zValue = QInputDialog::getDouble(this, tr("图层设置"), tr("设置当前图层"), item->zValue());
        if(zValue != 0) {
            item->setZValue(zValue);
        }
    });

    menu.addAction(tr("删除图元"), [this, item](){
        deleteItemFromScene(m_CurrentScene, dynamic_cast<TItem *>(item));
    });

    menu.addSeparator();
    menu.addActions(actions());
    menu.exec(QCursor::pos());
}
QStringList ADrawMainWindow::getAlldeviceName()
{
    return m_deviceInfoList.keys();
}


