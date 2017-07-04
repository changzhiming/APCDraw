#include "adrawmainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QLabel>
#include <windows.h>
#include "drawCore/Graphics/Pixmap.h"
#include "drawCore/Scene/Scene.h"
#include "drawCore/View/View.h"
#include "login/login.h"
#include "ageneralfunction.h"

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
    a.setStyleSheet(QAPC::AGeneralFunction::getStylesheet(":/qss/qss/adrawmainwindow.qss"));  //设置qss样式

    ADrawMainWindow w;
    w.showMaximized();

//    Login login("Project1.db");
//    login.show();

    return a.exec();
}
