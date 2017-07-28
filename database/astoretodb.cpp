#include "astoretodb.h"
#include "aexecdbthread.h"
#include "drawCore/Item/Item.h"
void AStoreToDB::initAlltable(QString connectName)
{

    AExecDbThread::execSql(connectName, QString("create table if not exists database_msg(driver_name text, "
                                                      "host_name text, db_name text, user_name text, passwd text, connect_name text)"));
    AExecDbThread::execSql(connectName, tr("delete from database_msg"));

    AExecDbThread::execSql(connectName, QString("insert into graphics_item(type INTERGE, data BOLB)"));
    AExecDbThread::execSql(connectName, tr("delete from graphics_item"));
}

void AStoreToDB::saveDataBaseMsg(QString connectName, QList<QStringList> dbInfo)
{
    AExecDbThread::execSql(connectName, QString("create table if not exists database_msg(driver_name text, "
                                                      "host_name text, db_name text, user_name text, passwd text, connect_name text)"));
    foreach (QStringList db, dbInfo) {
        QString sql = QString("insert into database_msg values('%1', '%2', '%3', '%4', '%5', '%6')").arg(db.at(0)).arg(db.at(1)).arg(db.at(2)).arg(db.at(3)).arg(db.at(4)).arg(db.at(5));

        AExecDbThread::execSql(connectName, sql);
    }
}
void AStoreToDB::saveGraphicsItem(QString connectName, QList<TItem *> itemList)
{
    QSqlDatabase &db =  AExecDbThread::getDb(connectName);
    if(db.isValid()) {
        QSqlQuery query(db);

        foreach(auto item, itemList)
        {
            query.prepare(QStringLiteral("insert into graphics_item values(?, ?)"));
            query.addBindValue(item->type());
            QByteArray graphicsByte;
            item->serialize(graphicsByte);
            query.bindValue(0, graphicsByte, QSql::Binary);
            query.exec();
        }
    }
}
