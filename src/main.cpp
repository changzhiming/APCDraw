#include "adrawmainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QStyle>
#include <QStyleFactory>
#include "ui/login.h"
#include "ageneralfunction.h"

#include "ageneralfunction.h"
#include "amanagedata.h"
#include <QtConcurrent>
#include <QModbusResponse>
#include "drawCore/Graphics/GraphicsPub.h"
#include "aglobal.h"

/*!
   int main(int argc, char *argv[]);
   \brief main QT 程序主函数
 */

bool main(int argc, char *argv[])
{
    //设置qDebug输出信息带文件行号
    qSetMessagePattern("[%{time h:mm:ss.zzz} %{if-debug}Debug%{endif}%{if-warning}Waring%{endif}%{if-critical}\
        Critical%{endif}%{if-fatal}Fatal%{endif}] %{file}:%{line} : %{message}");

    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));
    a.setStyleSheet(AGeneralFunction::getStylesheet(QStringLiteral(":/qss/qss/adrawmainwindow.qss")));  //设置qss样式

    ADrawMainWindow::getInstance()->showMaximized();
    AGeneralFunction::addDbCon("QSQLITE", "", "project.db", "", "" , "sql1");

//    Login login("Project1.db");
//    login.show();
    return a.exec();
}
