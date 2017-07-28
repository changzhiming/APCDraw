#ifndef AHANDLEDATA_H
#define AHANDLEDATA_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QSerialPort>
#include <QMutex>

class AVariable;
class AHandleData : public QObject
{
    Q_OBJECT
public:
    static AHandleData &getInstance();
    ~AHandleData();

public slots:
    void sendData(QString ip, quint16 clientPort,  quint16 servalPort, QByteArray data);
    void sendQSerialPortData(QString serialName, QByteArray data);
private:
    explicit AHandleData(QObject *parent = 0);

    QUdpSocket m_UdpSocket;
    QMutex sendDataMutex;              //
    QThread *m_sendData;
};

#endif // AHANDLEDATA_H
