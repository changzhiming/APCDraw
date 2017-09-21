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

public:
    QString m_deviceName;                   //device name
    QString m_deviceDescript;               //设备描述
    int m_tickInterval = 100;              //心跳间隔
    int m_timeOut = 3;                      //超时时间
    int m_serverAddr = 1;                   //设备地址
    ModbusConnection m_connectType = Tcp;         //链接类型
    QString m_connectProtocol;
    qreal m_OrderIntervalTime = 20;         //命令间隔20ms
    int m_numberOfRetries = 3;              //重发次数
    int m_sendFailNumDisconnect = 3;        // 发送失败几次掉线
    int m_reconnectionTime = 30;             //3s

    QString m_ip = "127.0.0.1";                           //Tcp  ip地址
    quint16 m_port = 502;                     //端口号
    bool m_connectStatus = false;           //连接状态
    //serial

    QModbusClient *m_modbusDevice = nullptr;//设备指针
    QModbusDataUnitMap m_registerMap;       //存储数据
};

#endif // ADEVICEINFO_H
