#include "avariable.h"
#include <QDataStream>
/*!
 * \calss AVariable
 * \brief 一个节点一个变量类，  一个节点可以有很多个寄存器地址
 */

AVariable::AVariable(QObject *parent) : QObject(parent){}
AVariable::~AVariable(){}
/*!
 * \brief AVariable::reciveValue  设置从底层接受的值
 * \param addr
 * \param value
 */
void AVariable::reciveValue(quint32 addr, qreal value)
{
    if(m_VariableValue.contains(addr)) {
        if(value != m_VariableValue[addr]) {
            emit valueChange(addr, value);
            m_VariableValue[addr] = value;
        }
    } else {
        emit valueChange(addr, value);
        m_VariableValue.insert(addr, value);
    }
}

qreal AVariable::getValue(quint32 addr) const
{
    if(m_VariableValue.contains(addr)) {
        return m_VariableValue.value(addr);
    }
    return 0;
}

