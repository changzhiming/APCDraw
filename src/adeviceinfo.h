#ifndef ADEVICEINFO_H
#define ADEVICEINFO_H

#include <QObject>
#include <QModbusDataUnitMap>
enum ModbusConnection {
    Tcp,
    Serial,
};

class QModbusClient;
class ADeviceInfo : public QObject
{
    Q_OBJECT
public:

    explicit ADeviceInfo(QObject *parent = 0);
    void setRegisterUnit(QModbusDataUnit::RegisterType registerType, int startAddr, int numCount);
    inline QModbusDataUnit &getRegisterUnit(QModbusDataUnit::RegisterType registerType) { return m_registerMap[registerType];}

    inline void setDeviceName(const QString &name) { m_deviceName = name; }
    inline QString getDeviceName() const { return m_deviceName; }

    inline void setModbusClient(QModbusClient *modbusClient) { m_modbusDevice = modbusClient; }
    inline QModbusClient *getModbusClient() const { return m_modbusDevice; }

    inline void setConnectStatus(bool connect){ m_connectStatus = connect; }
    inline bool getConnectStatus() const{ return m_connectStatus; }

    inline void setTickInterval(int tickInterVal){ m_tickInterval = tickInterVal; }
    inline int getTickInterval() const { return m_tickInterval; }

    inline void setTimeOut(int timeOut) { m_timeOut = timeOut; }
    inline int getTimeOut() const {return m_timeOut;}

    inline void setNumberOfRetries(int numberOfRetries) { m_numberOfRetries = numberOfRetries; }
    inline int getNumberOfRetries() const { return m_numberOfRetries; }

    inline void setServerAddr(int serveraddr) { m_serverAddr = serveraddr; }
    inline int getServerAddr() const { return m_serverAddr; }

    inline void setConnectType(ModbusConnection connectType) { m_connectType = connectType; }
    inline ModbusConnection getConnectType() const { return m_connectType; }

    inline void setIp(const QString &ip)  { m_ip = ip ;}
    inline QString getIp() const { return m_ip;}

    inline void setPort(quint16 port) { m_port = port; }
    inline quint16 getPort() const { return m_port; }

private:
    QString m_deviceName;                   //device name
    QModbusClient *m_modbusDevice = nullptr;//设备指针
    QModbusDataUnitMap m_registerMap;       //存储数据
    bool m_connectStatus = false;           //连接状态
    int m_tickInterval = 1000;              //心跳间隔
    int m_timeOut = 3;                      //超时时间
    int m_numberOfRetries = 1000;            //重连次数
    int m_serverAddr = 1;                    //服务端地址
    ModbusConnection m_connectType;          //链接类型

    QString m_ip;                           //Tcp  ip地址
    quint16 m_port = 0;                     //端口号
    //serial
};

#endif // ADEVICEINFO_H
