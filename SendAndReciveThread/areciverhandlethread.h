#ifndef ARECIVERHANDLETHREAD_H
#define ARECIVERHANDLETHREAD_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpSocket>

struct Net {
    QHostAddress senderIp;
    quint16 port;
    QByteArray data;
};

class QTimer;
class AVariable;
class AHandleDataThread;
class AReciverHandleThread : public QObject
{
    Q_OBJECT
public:
    static AReciverHandleThread & getInstance();
    ~AReciverHandleThread();

    void createBindUdp(quint16 port = 502);
    void createBindTcp(quint16 port = 502);

signals:
    void hasNetData();
public slots:
    void handleNetCommand();
    void handleSerialCommand();
    void detePackageNum();


private:
    explicit AReciverHandleThread( QObject *parent = 0);

    QList<QUdpSocket *> m_UdpSocketList;
    QThread *reciverData;
    QTimer  * m_timer;
    QList<AHandleDataThread *> m_handleList;
};


#endif // ARECIVERHANDLETHREAD_H
