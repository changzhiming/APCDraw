#ifndef AHANDLEDATATHREAD_H
#define AHANDLEDATATHREAD_H

#include <QUdpSocket>
#include <QTcpSocket>
#include <QObject>
#include <QThread>
#include <QTimer>


class AVariable;
class AHandleDataThread : public QObject
{
    Q_OBJECT
public:
    explicit AHandleDataThread(QList<AVariable *> variable = QList<AVariable *>(), QObject *parent = 0);
    ~AHandleDataThread();

public slots:
    void analysisNetProtocol();

private:
    QThread *m_analysisThread;
    int *currentHandle = 0;
};



#endif // AHANDLEDATATHREAD_H
