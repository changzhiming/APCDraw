#ifndef ABASEPROTOCOL_H
#define ABASEPROTOCOL_H
#include <QByteArray>
#include <QHash>
#include <QtPlugin>
#include <QObject>
#include <QtCore/qglobal.h>

class ABaseProtocol
{
public:
    virtual ~ABaseProtocol() {}
    virtual QString getProtocolName() const = 0;
    virtual QByteArray generateTickPackage(int mainId) = 0;
    virtual QByteArray generateWriteProtocolPackage(int mainId, quint32 addr, double value) = 0;
    virtual QByteArray generateReadProtocolPackage(int mainId, quint32 addr) = 0;

    virtual int getMainId(QByteArray &data) = 0;
    virtual QHash<quint32, double> parseProtocolPackage(QByteArray &data) = 0;
};

Q_DECLARE_INTERFACE(ABaseProtocol, "org.APCDraw.Protocol")

#endif // ABASEPROTOCOL_H
