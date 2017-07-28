#include "ahandledatathread.h"
#include "Variable/avariable.h"
#include <QThread>
#include <QTime>
#include "areciverhandlethread.h"
#include "Variable/amanagevariable.h"
#include "ProtocolPlugin/aloadandunloadplugin.h"

extern QList<Net> g_AHandleDataNetDataList;
extern QMutex g_AHandleDatadataMutex;

AHandleDataThread::AHandleDataThread(QList<AVariable *> variable, QObject *parent) : QObject(parent)
{
    m_analysisThread = new QThread(this);
    m_analysisThread->setObjectName(tr("analysisThread"));
    m_analysisThread->start();
    moveToThread(m_analysisThread);
}

AHandleDataThread::~AHandleDataThread()
{
    qDebug()<<"AHandleDataThread delete";
    m_analysisThread->quit();
    m_analysisThread->wait();
}

void AHandleDataThread::analysisNetProtocol()
{
    g_AHandleDatadataMutex.lock();
    if(g_AHandleDataNetDataList.size() >= 1) {
        Net dataNet = g_AHandleDataNetDataList.takeFirst();
        g_AHandleDatadataMutex.unlock();
        QStringList protocolList = AManageVariable::getInstance().getProtocolName(dataNet.senderIp.toString(), dataNet.port);
        if(!protocolList.isEmpty()) {

            foreach(auto pro, protocolList)
            {
                int mainId = ALoadAndUnloadPlugin::getInstance().getMainId(pro, dataNet.data);
                if(mainId) {
                    QHash<quint32, double> addrToValue = ALoadAndUnloadPlugin::getInstance().getParseValue(pro, dataNet.data);
                    AVariable * var = AManageVariable::getInstance().getVariable(dataNet.senderIp.toString(), dataNet.port, mainId);
                    for(QHash<quint32, double>::iterator i = addrToValue.begin(); i!= addrToValue.end(); i++)
                    {
                        var->reciveValue(i.key(), i.value());
                    }
                    break;
                }
            }
        }

        //任务处理待编写
    } else {
        g_AHandleDatadataMutex.unlock();
    }
}

