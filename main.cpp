#include "adrawmainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QLabel>
#include <windows.h>
#include <QStyle>
#include <QStyleFactory>
#include "drawCore/Graphics/Pixmap.h"
#include "drawCore/Scene/Scene.h"
#include "drawCore/View/View.h"
#include "login/login.h"
#include "ageneralfunction.h"
#include "JSEngine/ajsexecute.h"
#include "Variable/avariable.h"
#include "SendAndReciveThread/ahandledata.h"
#include "SendAndReciveThread/ahandledatathread.h"
#include "SendAndReciveThread/areciverhandlethread.h"
#include "ProtocolPlugin/aloadandunloadplugin.h"
#include "database/astoretodb.h"
#include "database/aexecdbthread.h"
/*!
   int main(int argc, char *argv[]);
   \brief main QT 程序主函数
 */

int main(int argc, char *argv[])
{
    //设置qDebug输出信息带文件行号
    qSetMessagePattern("[%{time h:mm:ss.zzz} %{if-debug}Debug%{endif}%{if-warning}Waring%{endif}%{if-critical}\
        Critical%{endif}%{if-fatal}Fatal%{endif}] %{file}:%{line} : %{message}");

    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));
    a.setStyleSheet(QAPC::AGeneralFunction::getStylesheet(":/qss/qss/adrawmainwindow.qss"));  //设置qss样式
    qRegisterMetaType<QHostAddress>("QHostAddress");

    //AReciverHandleThread::getInstance();
    ALoadAndUnloadPlugin::getInstance();
    AJSExecute::getInstance();

    ADrawMainWindow::getInstance().showMaximized();
    AExecDbThread::addDbCon("QSQLITE", "", "project.db", "", "" , "sql1");
    //AExecDbThread::execSql("sql1", QString("insert into ssss values (?)"), sss);

//    Login login("Project1.db");
//    login.show();

    return a.exec();
}
