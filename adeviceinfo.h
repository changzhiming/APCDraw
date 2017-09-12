#ifndef ADEVICEINFO_H
#define ADEVICEINFO_H

#include <QObject>

class ADeviceInfo : public QObject
{
    Q_OBJECT
public:
    explicit ADeviceInfo(QObject *parent = 0);

signals:

public slots:
};

#endif // ADEVICEINFO_H