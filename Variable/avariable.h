#ifndef AVARIABLE_H
#define AVARIABLE_H

#include <QObject>
#include <QHash>
//struct NetWorkInfo {
//    enum NETTYPE{
//        UDP,
//        TCP,
//    };
//    NETTYPE type = UDP;
//    QHostAddress m_ipAddr;
//    quint16 m_ClientPort;
//    quint16 m_ServerPort;
//};
//struct SerialPortInfo {
//    QString comName;
//    QSerialPort::BaudRate baudRate;
//    QSerialPort::DataBits dataBites;
//    QSerialPort::Parity parity;
//    QSerialPort::StopBits stopBits;
//};

class AVariable : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString    variableName          READ getVariableName      WRITE setVariableName)
    Q_PROPERTY(QString    protocolName          READ getProtocolName      WRITE setProtocolName)

    Q_PROPERTY(int    mainId               READ getMainId          WRITE setMainId)
    Q_PROPERTY(int    tickInterval         READ getTickInterval    WRITE setTickInterval)
public:      
    enum LINKTYPE {
        UDP = 0,
        TCP,
        SERIAL,
    };

    explicit AVariable( QObject *parent = 0);
    ~AVariable();

    inline void setTickInterval(int ms);
    inline int getTickInterval() const;

    inline void setMainId(int id);
    inline int getMainId() const;

    inline void setRegisterNum(int num);
    inline int getRegisterNum() const;

    inline void setVariableName(QString name);
    inline QString getVariableName() const;

    inline void setProtocolName(QString name);
    inline QString getProtocolName() const;

    inline void setLinkType(int type);
    inline int getLinkType();

public slots:
    void reciveValue(quint32 addr, qreal value);
    qreal getValue(quint32 addr) const;

signals:
    void valueChange(quint32 addr, double value);

protected:
    QHash<quint32, double> m_VariableValue;  //存储所有的变量值

    QString m_VariableName;
    QString m_ProtocolName;
    // devId
    int m_MainId = 0;
    int m_TickInterval = 0;

    int m_LinkType = 0;
};

inline void AVariable::setTickInterval(int ms)
{    m_TickInterval = ms;}
inline int AVariable::getTickInterval() const
{    return m_TickInterval;}

inline void AVariable::setMainId(int id)
{    m_MainId = id;}

inline int AVariable::getMainId() const
{    return m_MainId;}

inline void AVariable::setVariableName(QString name)
{    m_VariableName = name;}

inline QString AVariable::getVariableName() const
{    return m_VariableName;}

inline void AVariable::setProtocolName(QString name)
{    m_ProtocolName = name;}

inline QString AVariable::getProtocolName() const
{    return m_ProtocolName;}
inline void AVariable::setLinkType(int type)
{ m_LinkType = type;}
inline int AVariable::getLinkType()
{ return m_LinkType;}
#endif // AVARIABLE_H
