#ifndef AMANAGEVARIABLE_H
#define AMANAGEVARIABLE_H
#include <QHash>
#include <QTimer>

#include "audpvariable.h"
class AManageVariable : public QObject
{
    Q_OBJECT
public:
    static AManageVariable & getInstance();
    ~AManageVariable();

    AVariable *createUdpVariable(QString variableName, QString protocolName, int mainId = 0, int tickInterval = 0,
                           QString ipAddr = QString(), quint16 clientPort= 0, quint16 serverPort = 0);
    void deleteVariable(QString variableName);
    AVariable *getVariable(QString variableName);
    AVariable *getVariable(QString ip, quint16 port, int mainId);
    QStringList getProtocolName(QString ip, quint16 port);
signals:
    void tickVar(QList<AVariable *> varList);  //滴答变量列表
    void valueChanged();
private:
    explicit AManageVariable(QObject *parent = 0);
    QHash<QString, AVariable *> m_AUdpVariableList;
    QHash<int, QTimer *> m_tickTimer;

    QHash<QTimer *, QList<AVariable *>> m_tickVar;  //定时时间和相应的变量
};

#endif // AMANAGEVARIABLE_H
