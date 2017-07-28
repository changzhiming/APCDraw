#include "areciverhandlethread.h"
#include "Variable/avariable.h"
#include <QThread>
#include <QTimer>
#include <QApplication>
#include "ahandledatathread.h"
#include "aglobal.h"

QList<Net> g_AHandleDataNetDataList;
QMutex g_AHandleDatadataMutex;

AReciverHandleThread & AReciverHandleThread::getInstance()
{
    static AReciverHandleThread reciverHandleThread;
    return reciverHandleThread;
}

/*!
 /class AReciverHandleThread
  /brief 接收数据线程
 */
AReciverHandleThread::AReciverHandleThread(QObject *parent) : QObject(parent)
{
    AHandleDataThread *handThread = new AHandleDataThread();
    m_handleList.append(handThread);

    m_timer = new QTimer();
    m_timer->start(1000);

    connect(this, &AReciverHandleThread::hasNetData, handThread, &AHandleDataThread::analysisNetProtocol);
    connect(m_timer, &QTimer::timeout, this, &AReciverHandleThread::detePackageNum);

    reciverData = new QThread(this);
    reciverData->setObjectName(tr("AReciverHandleThread"));
    reciverData->start();
    moveToThread(reciverData);
}

AReciverHandleThread::~AReciverHandleThread()
{
    qDebug()<<"AReciverHandleThread delete";
    m_timer->deleteLater();
    foreach(auto *handThread , m_handleList)
    {
        delete handThread;
    }
    foreach(auto udp, m_UdpSocketList)
    {
        delete udp;
    }

    reciverData->quit();
    reciverData->wait();
    delete reciverData;
}
void AReciverHandleThread::createBindUdp(quint16 port)
{
    QUdpSocket *udpSocket = new QUdpSocket(this);
    udpSocket->bind(port, QUdpSocket::ShareAddress);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(handleNetCommand()));

    m_UdpSocketList.append(udpSocket);
}

void AReciverHandleThread::createBindTcp(quint16 port)
{
    Q_UNUSED(port)
}

void AReciverHandleThread::handleNetCommand()
{
    QHostAddress senderIp;
    quint16 senderPort;
    QByteArray datagram;

    QUdpSocket *reciver=qobject_cast<QUdpSocket *>(sender());
    while(reciver && reciver->hasPendingDatagrams())
    {
        datagram.resize(reciver->pendingDatagramSize());
        reciver->readDatagram(datagram.data(), datagram.size(), &senderIp, &senderPort);

        Net netData = {senderIp, senderPort, datagram};
        g_AHandleDatadataMutex.lock();
        g_AHandleDataNetDataList.append(netData);
        g_AHandleDatadataMutex.unlock();
        emit hasNetData();
    }
}
void AReciverHandleThread::handleSerialCommand()
{
    //
}

void AReciverHandleThread::detePackageNum()
{
    Q_ASSERT_X(m_handleList.size() <= 4, ("线程数太多"), "数据量太大");
    if(g_AHandleDataNetDataList.size() >= 1000) {
        AHandleDataThread *handThread = new AHandleDataThread(QList<AVariable *>() ,this);
        m_handleList.append(handThread);
        connect(&AReciverHandleThread::getInstance(), &AReciverHandleThread::hasNetData, handThread, &AHandleDataThread::analysisNetProtocol);
    }
}
