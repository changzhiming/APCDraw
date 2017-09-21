#ifndef AMANAGEDATA_H
#define AMANAGEDATA_H
#include <QModbusDataUnitMap>
#include <QObject>

class QModbusClient;
class QTimer;
class ADeviceInfo;

class AManageData : public QObject
{
    Q_OBJECT
public:
    static AManageData *getInstance();
    ~AManageData();
public slots:
    ADeviceInfo *getDeviceInfo(const QString &deviceName) const;
    bool addDevice(ADeviceInfo *deviceInfo);

    bool readModbusData(const QString &deviceName, QModbusDataUnit::RegisterType registerType);
    bool writeModbusData(const QString &deviceName, QModbusDataUnit::RegisterType registerType, quint16 startAddr,const QVector<quint16> &values);

    quint16 getDeviceValue(QString deviceName, QModbusDataUnit::RegisterType registerType, quint16 registerAddr);
signals:
    void deviceStatusChanged(QString deviceName, bool deviceStatus);
    void deviceValueChanged(QString deviceName, quint16 registerAddr, quint16 value);

private:
    explicit AManageData(QObject *parent = 0);

    bool writeModbusData(ADeviceInfo *deviceInfo, QModbusDataUnit::RegisterType registerType, quint16 startAddr, const QVector<quint16> &values);
    bool readModbusData(ADeviceInfo *deviceInfo, QModbusDataUnit::RegisterType registerType);

    void valueChangedOperate(ADeviceInfo *deviceInfo, const QModbusDataUnit &unit);
private:

    QList<ADeviceInfo *> m_deviceInfoList;
    QTimer * m_tickTimer = nullptr ;
    QThread *m_ModbusThread =nullptr;
};

#endif // AMANAGEDATA_H
