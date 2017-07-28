#ifndef AUDPVARIABLE_H
#define AUDPVARIABLE_H
#include "avariable.h"
#include <QNetworkInterface>
#include <QSerialPort>

class AUdpVariable : public AVariable
{
    Q_OBJECT
    Q_PROPERTY(QString    ipAddr         READ getIpAddr        WRITE setIpAddr)
    Q_PROPERTY(int    clientPort         READ getClientPort    WRITE setClientPort)
    Q_PROPERTY(int    serverPort         READ getServerPort    WRITE setServerPort)

public:
    AUdpVariable(QObject *parent = 0);

    inline void setIpAddr(QString ip);
    inline QString getIpAddr() const;

    inline void setClientPort(quint16 port);
    inline quint16 getClientPort() const;
    inline void setServerPort(quint16 port);
    inline quint16 getServerPort() const;

private:
    //ip and port
    QString m_IpAddr;
    quint16 m_ClientPort;
    quint16 m_ServerPort;

private:
    friend  QDataStream &operator<<(QDataStream &, const AUdpVariable &);
    friend  QDataStream &operator>>(QDataStream &, AUdpVariable &);
};

inline void AUdpVariable::setClientPort(quint16 port)
{ m_ClientPort = port; }
inline quint16 AUdpVariable::getClientPort() const
{ return m_ClientPort; }
inline void AUdpVariable::setServerPort(quint16 port)
{ m_ServerPort = port; }
inline quint16 AUdpVariable::getServerPort() const
{ return m_ServerPort; }
inline void AUdpVariable::setIpAddr(QString ip)
{ m_IpAddr = ip; }
inline QString AUdpVariable::getIpAddr() const
{ return m_IpAddr; }

QDataStream &operator<<(QDataStream &, const AUdpVariable &);
QDataStream &operator>>(QDataStream &, AUdpVariable &);

#endif // AUDPVARIABLE_H
