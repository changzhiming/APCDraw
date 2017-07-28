#include "aexecdbthread.h"
#include <QSqlQuery>
#include <QDebug>

AExecDbThread::AExecDbThread(QObject *parent) : QObject(parent)
{
}
bool AExecDbThread::addDbCon(QString type, QString Host, QString DBName, QString UserName, QString PassWord, QString connectName)
{
    if(QSqlDatabase::connectionNames().contains(connectName))
        return false;

    if(connectName.isEmpty()) {
        connectName = type;
        for(int i = 0; QSqlDatabase::connectionNames().contains(connectName) ; i++)
        {
            connectName = type + QString::number(i);
        }
    }
    QSqlDatabase m_DB = QSqlDatabase::addDatabase(type, connectName);
    m_DB.setHostName(Host);
    m_DB.setDatabaseName(DBName);
    m_DB.setUserName(UserName);
    m_DB.setPassword(PassWord);
    if(m_DB.open())
        return true;
    else
        return false;
}
QSqlDatabase & AExecDbThread::getDb(QString connectName)
{
    return QSqlDatabase::database(connectName, true);
}

QList<QStringList> AExecDbThread::getAllDbInfo()
{
    QList<QStringList> t_dbInfo;
    foreach (QString connectName, QSqlDatabase::connectionNames()) {
        QStringList dbInto;
        QSqlDatabase m_Db = QSqlDatabase::database(connectName);
        dbInto<<m_Db.driverName()<<m_Db.hostName()<<m_Db.databaseName()<<m_Db.userName()<<m_Db.password()<<m_Db.connectionName();
        t_dbInfo.append(dbInto);
    }
    return t_dbInfo;
}
/*!
 * \brief AExecDbThread::execSql  执行耗时操作
 * \param connectName  根据连接名字寻找操作的数据库
 * \param sql   执行的sql语句
 * \return 没有返回值
 */
bool AExecDbThread::execSql(QString connectName, QString sql)
{
    QSqlDatabase db = QSqlDatabase::database(connectName);
    if(db.isValid()) {
        return db.exec(sql).isValid();
    }
    return false;
}
bool AExecDbThread::execSql(QString connectName, QString sql, QByteArray data)
{
    QSqlDatabase db = QSqlDatabase::database(connectName);
    if(db.isValid()) {
        QSqlQuery query(db);
        query.prepare(sql);
        query.bindValue(0, data, QSql::Binary);
        return query.exec();
    }
    return true;
}

QSqlQuery AExecDbThread::getTableData(QString connectName, QString tableName)
{
    QSqlDatabase db = QSqlDatabase::database(connectName);
    if(db.isValid())
        return db.exec(QString("select * from %1;").arg(tableName));
    return QSqlQuery();
}


