/*!
* @file
* @brief 全局通用函数
*
* @author 常志明
* @version v1.0
* @date
*/

#ifndef AGENERALFUNCTION_H
#define AGENERALFUNCTION_H
#include <QSqlDatabase>
#include <QJSEngine>

class AGeneralFunction : public QObject
{
    Q_OBJECT
public:
    // style
    static QString getStylesheet(const QString &filename);
    static QByteArray getMd5Hash(const QByteArray &data);
    static QByteArray getLocalMachineMac();
    //DB
    static bool addDbCon(const QString &type, const QString & Host, const QString &DBName, const QString &UserName = "", const QString &PassWord = "", const QString &connectName = "");
    static QSqlDatabase getDb(const QString &connectName) { return QSqlDatabase::database(connectName, true); }
    static void removeDbCon(const QString &connectName) { QSqlDatabase::removeDatabase(connectName); }
    static QList<QStringList> getAllDbInfo();
    static bool execSql(const QString &connectName, const QString &sql);
    static bool createTable(const QString &connectName, const QString &tableName, const QStringList &property, const QStringList &datatype);
    static QSqlQuery getTableData(const QString &connectName, const QString &tableName);

    //js init
    static void createQObjectToJS(QObject * object,  const QString &objName);
    static inline void createProperty(const QString &proName, const QJSValue &value) { getJsEngine().globalObject().setProperty(proName, value); }
    static QJSValue execJS(const QString &js);
private:
    static QJSEngine & getJsEngine();
};
#endif // AGENERALFUNCTION_H
