#include "amanagedata.h"
#include "adeviceinfo.h"
#include "aglobal.h"
#include <QDebug>
#include <QVariant>
#include <QModbusTcpClient>
#include <QModbusRtuSerialMaster>
#include <QModbusDataUnit>
#include <QtConcurrent>

AManageData * AManageData::getInstance()
{
   static QScopedPointer<AManageData> manageData(new AManageData(nullptr));
   return manageData.data();
}
AManageData::~AManageData()
{
    m_tickTimer->deleteLater();
    m_ModbusThread->quit();
    m_ModbusThread->wait();
}

ADeviceInfo * AManageData::getDeviceInfo(const QString &deviceName) const
{
    foreach (ADeviceInfo * deviceInfo, m_deviceInfoList) {
        CONDITION_TRURUN_BOOL(deviceInfo->getDeviceName() == deviceName, deviceInfo)
    }
    return nullptr;
}
bool AManageData::addDevice(ADeviceInfo *deviceInfo)
{
    CONDITION_TRURUN_BOOL(deviceInfo == nullptr || deviceInfo->getModbusClient() == nullptr, false);
    //判断是否重复添加
    m_deviceInfoList.append(deviceInfo);
    deviceInfo->setParent(this);
    foreach (ADeviceInfo * t_deviceInfo, m_deviceInfoList) {
        if(t_deviceInfo->getIp() == deviceInfo->getIp() && t_deviceInfo->getPort() == deviceInfo->getPort())
            return false;
    }
    //
    if(deviceInfo->getConnectType() == Tcp) {
        QModbusClient *modbusDevice = new QModbusTcpClient(this);
        connect(modbusDevice, &QModbusClient::stateChanged, [this, deviceInfo](int state) {
            if(state != QModbusDevice::ConnectedState) {
                deviceInfo->setConnectStatus(false);
                emit deviceStatusChanged(deviceInfo->getDeviceName(), false);
            } else {
                deviceInfo->setConnectStatus(true);
                emit deviceStatusChanged(deviceInfo->getDeviceName(), true);
            }
        });

        if (modbusDevice->state() != QModbusDevice::ConnectedState) {
            modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter, deviceInfo->getPort());
            modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter, deviceInfo->getIp());
            modbusDevice->setTimeout(deviceInfo->getTimeOut());
            modbusDevice->setNumberOfRetries(deviceInfo->getNumberOfRetries());

            if (!modbusDevice->connectDevice()) {
                qDebug()<<(tr("Connect failed: ") + modbusDevice->errorString());
            }
        }
    }
    if(deviceInfo->getConnectType() == Serial) {
        //串口初始化
    }
    return true;
}

AManageData::AManageData(QObject *parent) : QObject(parent)
{
    m_tickTimer = new QTimer(0);

    connect(m_tickTimer, &QTimer::timeout, this, [this](){
        static qint64 tickNumber = 100;
        foreach (ADeviceInfo* deviceInfo, m_deviceInfoList) {
            if(tickNumber % deviceInfo->getTickInterval() == 0)
                readModbusData(deviceInfo, QModbusDataUnit::HoldingRegisters); //send 03;
        }
        tickNumber += 100;
    });
    m_tickTimer->start(100);
    //start thread
    m_ModbusThread = new QThread(this);
    m_ModbusThread->setObjectName(tr("ModbusDataThread"));
    moveToThread(m_ModbusThread);
    m_ModbusThread->start();
}

bool AManageData::readModbusData(ADeviceInfo *deviceInfo, QModbusDataUnit::RegisterType registerType)
{
    CONDITION_TRURUN_BOOL(deviceInfo == nullptr || deviceInfo->getModbusClient() == nullptr, false);

    QModbusClient *modbusDevice = deviceInfo->getModbusClient();
    if(!modbusDevice->connectDevice()) {
        deviceInfo->setConnectStatus(false);
        emit deviceStatusChanged(deviceInfo->getDeviceName(), false);
        return false;
    }
    if (auto *reply = modbusDevice->sendReadRequest(deviceInfo->getRegisterUnit(registerType), deviceInfo->getServerAddr())) {
        if (!reply->isFinished()) {
            //读取数据
            connect(reply, &QModbusReply::finished, [this, deviceInfo, reply]{
                if (reply->error() == QModbusDevice::NoError) {
                    QtConcurrent::run(QThreadPool::globalInstance(), this, &AManageData::valueChangedOperate, deviceInfo, reply->result());
                }
                reply->deleteLater();
            });
        }
        else
            reply->deleteLater(); // broadcast replies return immediately
    }
    return true;
}
bool AManageData::readModbusData(const QString &deviceName, QModbusDataUnit::RegisterType registerType)
{
    return readModbusData(getDeviceInfo(deviceName), registerType);
}

bool AManageData::writeModbusData(ADeviceInfo *deviceInfo, QModbusDataUnit::RegisterType registerType, quint16 startAddr, const QVector<quint16> &values)
{
    CONDITION_TRURUN_BOOL(deviceInfo == nullptr || deviceInfo->getModbusClient() == nullptr, false);

    QModbusClient *modbusDevice = deviceInfo->getModbusClient();

    if(!modbusDevice->connectDevice()) {
        deviceInfo->setConnectStatus(false);
        emit deviceStatusChanged(deviceInfo->getDeviceName(), false);
        return false;
    }

    QModbusDataUnit dataUnit = deviceInfo->getRegisterUnit(registerType);
    dataUnit.setStartAddress(startAddr);
    dataUnit.setValueCount(values.count());
    dataUnit.setValues(values);

    if (auto *reply = modbusDevice->sendWriteRequest(dataUnit, deviceInfo->getServerAddr())) {
        if (!reply->isFinished()) {

            connect(reply, &QModbusReply::finished, [this, deviceInfo, reply]{
                if (reply->error() == QModbusDevice::NoError) {
                    QtConcurrent::run(QThreadPool::globalInstance(), this, &AManageData::valueChangedOperate, deviceInfo, reply->result());
                }
                reply->deleteLater();
            });
        }
        else
            reply->deleteLater(); // broadcast replies return immediately
    }
    return true;
}
bool AManageData::writeModbusData(const QString &deviceName, QModbusDataUnit::RegisterType registerType, quint16 startAddr, const QVector<quint16> &values)
{
    return writeModbusData(getDeviceInfo(deviceName), registerType, startAddr,values);
}
quint16 AManageData::getDeviceValue(QString deviceName, QModbusDataUnit::RegisterType registerType, quint16 registerAddr)
{
    QModbusDataUnit &t_Unit = getDeviceInfo(deviceName)->getRegisterUnit(registerType);
    return t_Unit.value(registerAddr - t_Unit.startAddress());
}

/*!
 * \brief AManageData::valueChangedOperate  数值改变 做的操作
 * \param deviceInfo                        设备类
 * \param unit                              读取的数据单元
 */
void AManageData::valueChangedOperate(ADeviceInfo *deviceInfo, const QModbusDataUnit &unit)
{
    QModbusDataUnit &t_Unit = deviceInfo->getRegisterUnit(unit.registerType());
    for (uint i = 0; i < unit.valueCount(); i++) {

        if(t_Unit.value(unit.startAddress() + i - t_Unit.startAddress()) != unit.value(i)) {
            t_Unit.setValue(unit.startAddress() + i - t_Unit.startAddress(), unit.value(i));
            emit deviceValueChanged(deviceInfo->getDeviceName(), unit.startAddress() + i, unit.value(i));
            //数据更新操作
        }
    }
}
