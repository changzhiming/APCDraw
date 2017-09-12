#include "adeviceinfo.h"
#include <QModbusClient>

ADeviceInfo::ADeviceInfo(QObject *parent) : QObject(parent)
{    }
void ADeviceInfo::setRegisterUnit(QModbusDataUnit::RegisterType registerType, int startAddr, int numCount)
{
    QModbusDataUnit & dataUnit = m_registerMap[registerType];
    dataUnit.setRegisterType(registerType);
    dataUnit.setStartAddress(startAddr);
    dataUnit.setValueCount(numCount);
}
