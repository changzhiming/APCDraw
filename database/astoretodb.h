#ifndef ASTORETODB_H
#define ASTORETODB_H

#include <QObject>

class TItem;
class AStoreToDB : public QObject
{
    Q_OBJECT
public:
    static void initAlltable(QString connectName);
    static void saveDataBaseMsg(QString connectName, QList<QStringList> dbInfo);
    static void saveGraphicsItem(QString connectName, QList<TItem *> itemList);
};

#endif // ASTORETODB_H
