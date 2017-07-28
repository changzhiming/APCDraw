#include "ajsexecute.h"
#include <QThread>
#include <QJSValue>
#include <QMessageBox>
#include <QApplication>
#include <QDebug>

AJSExecute::AJSExecute(QObject *parent) : QObject(parent)
{
}
AJSExecute::~AJSExecute()
{
}

AJSExecute & AJSExecute::getInstance()
{
    static AJSExecute ajsExecute = AJSExecute();
    return ajsExecute;
}

/*!
 * \brief AJSExecute::createAllQObject 创建所有的可用类到js
 * \param object
 */
void AJSExecute::createQObjectToJS(QObject * object, QString objName)
{
    if(objName.isEmpty() || objName.contains(QRegExp("[\\x4e00-\\x9fa5]+")))
        return;
    QJSValue scriptButton = myEngine.newQObject(object);
    myEngine.globalObject().setProperty(objName, scriptButton);
}

 void AJSExecute::execJS(QString js)
 {
     QJSValue result = myEngine.evaluate(js);
     if(result.isError()) {
         QMessageBox::warning(0, tr("脚本错误"), tr("行号") + result.property("lineNumber").toString() + result.toString());
     }
 }

// void AJSExecute::sync()
// {

//     if (QThread::currentThread() != JSThread){
//         QMetaObject::invokeMethod(&getInstance(), "sync", Qt::BlockingQueuedConnection);
//         return;
//     }
//     qApp->processEvents();
// }
