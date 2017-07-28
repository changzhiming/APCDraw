#ifndef AEXECDBTHREAD_H
#define AEXECDBTHREAD_H
#include <QSqlDatabase>
#include <QObject>
#include <QHash>
#include <QThread>
#include <QSqlQuery>

class AExecDbThread : public QObject
{
    Q_OBJECT
public:
    static bool addDbCon(QString type, QString Host, QString DBName, QString UserName, QString PassWord, QString connectName = QString());
    static QSqlDatabase &getDb(QString connectName);
    static inline void removeDbCon(QString connectName);
    static QList<QStringList> getAllDbInfo();
    static bool execSql(QString connectName, QString sql);
    static bool execSql(QString connectName, QString sql, QByteArray data);

    static QSqlQuery getTableData(QString connectName, QString tableName);
private:
    explicit AExecDbThread(QObject *parent = 0);
};
inline void AExecDbThread::removeDbCon(QString connectName)
{
    QSqlDatabase::removeDatabase(connectName);
}
#endif // AEXECDBTHREAD_H
