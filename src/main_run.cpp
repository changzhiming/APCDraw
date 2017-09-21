#include "arunmainwindow.h"
#include "ageneralfunction.h"
#include <QApplication>
#include <QStyleFactory>
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
    ARunMainWindow::getInstance()->showMaximized();
    return a.exec();
}
