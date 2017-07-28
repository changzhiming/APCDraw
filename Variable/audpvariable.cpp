#include "audpvariable.h"
#include "../ProtocolPlugin/aloadandunloadplugin.h"

AUdpVariable::AUdpVariable(QObject *parent) : AVariable(parent){}

QDataStream &operator<<(QDataStream &out, const AUdpVariable & variable)
{
    Q_UNUSED(variable)
    return out;
}
QDataStream &operator>>(QDataStream &in, AUdpVariable &variable)
{
    Q_UNUSED(variable)
    return in;
}
