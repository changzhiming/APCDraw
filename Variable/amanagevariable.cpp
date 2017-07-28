#include "amanagevariable.h"
#include "SendAndReciveThread/ahandledata.h"
#include "ProtocolPlugin/aloadandunloadplugin.h"
/*!
 * \class AManageVariable 管理所有的变量
 * \param parent
 */

AManageVariable & AManageVariable::getInstance()
{
    static AManageVariable manageVar;
    return manageVar;
}

AManageVariable::AManageVariable(QObject *parent) : QObject(parent){    }
AManageVariable::~AManageVariable()
{
    foreach(auto var, m_AUdpVariableList)
    {
        delete var;
    }
}

AVariable* AManageVariable::createUdpVariable(QString variableName, QString protocolName, int mainId, int tickInterval,
                       QString ipAddr, quint16 clientPort, quint16 serverPort)
{
    if(!m_AUdpVariableList.contains(variableName)) {
        AUdpVariable *udpVariable = new AUdpVariable(this);
        udpVariable->setVariableName(variableName);
        udpVariable->setProtocolName(protocolName);
        udpVariable->setMainId(mainId);
        udpVariable->setTickInterval(tickInterval);
        udpVariable->setIpAddr(ipAddr);
        udpVariable->setClientPort(clientPort);
        udpVariable->setServerPort(serverPort);

        m_AUdpVariableList.insert(variableName, udpVariable);
        //创建滴答定时器
        if(tickInterval && m_tickTimer.contains(tickInterval)) {

            m_tickVar[m_tickTimer.value(tickInterval)].append(udpVariable);
        } else if(tickInterval){
            QTimer *tiemr = new QTimer(this);
            connect(tiemr, &QTimer::timeout, this, [=](){emit tickVar(m_tickVar.value(tiemr));});
            m_tickTimer.insert(tickInterval, tiemr);
            QList<AVariable *> varList;
            varList.append(udpVariable);
            m_tickVar.insert(tiemr, varList);

            tiemr->start(tickInterval);
        }

        return udpVariable;
    }
    return nullptr;
}
void AManageVariable::deleteVariable(QString variableName)
{
    if(m_AUdpVariableList.contains(variableName)) {
        delete m_AUdpVariableList.value(variableName);
        m_AUdpVariableList.remove(variableName);
    }
}

AVariable * AManageVariable::getVariable(QString variableName)
{
    if(m_AUdpVariableList.contains(variableName)) {
        return m_AUdpVariableList.value(variableName);
    }
    return nullptr;
}
AVariable *AManageVariable::getVariable(QString ip, quint16 port, int mainId)
{
    foreach(auto * var, m_AUdpVariableList.values()) {
        AUdpVariable * udp = qobject_cast<AUdpVariable *>(var);
        if(udp) {
            if(udp->getIpAddr() == ip && mainId == udp->getMainId() && udp->getClientPort() == port) {
                return udp;
            }
        }
    }
    return nullptr;
}
QStringList AManageVariable::getProtocolName(QString ip, quint16 port)
{
    QStringList protocolList;
    foreach(auto * var, m_AUdpVariableList.values()) {
        AUdpVariable * udp = qobject_cast<AUdpVariable *>(var);
        if(udp) {
            if(udp->getIpAddr() == ip && udp->getClientPort() == port) {
                protocolList<<udp->getProtocolName();
            }
        }
    }
    return protocolList;
}
