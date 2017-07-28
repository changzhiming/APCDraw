#include "ahandledata.h"
#include "Variable/avariable.h"
#include <QThread>

AHandleData &AHandleData::getInstance()
{
    static AHandleData handleData;
    return handleData;
}

/*!
 * \class AHandleData 发送数据线程
 * \param parent
 */

AHandleData::AHandleData(QObject *parent) : QObject(parent)
{
    m_sendData = new QThread(this);
    m_sendData->setObjectName(tr("sendDatathread"));
    m_sendData->start();
    moveToThread(m_sendData);
}

AHandleData::~AHandleData()
{
    m_sendData->quit();
    m_sendData->wait();
    delete m_sendData;
}

void AHandleData::sendData(QString ip, quint16 clientPort,  quint16 servalPort, QByteArray data)
{
    m_UdpSocket.bind(servalPort, QUdpSocket::ShareAddress);
    m_UdpSocket.writeDatagram(data, QHostAddress(ip), clientPort);
}

void AHandleData::sendQSerialPortData(QString serialName, QByteArray data)
{
    Q_UNUSED(serialName)
    Q_UNUSED(data)
}
