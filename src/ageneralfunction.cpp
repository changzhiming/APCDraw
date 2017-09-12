#include <ageneralfunction.h>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QNetworkInterface>
#include <QSqlDatabase>
#include <QFile>
#include <QSqlQuery>
#include <QFile>
/*!
  \class AGeneralFunction
  \brief
  \inmodule APCUI
 */

/*!
  \brief GlobalFunction::getStylesheet \a filename 读取qss文件内容
 */
QString AGeneralFunction::getStylesheet(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qWarning() << "Stylesheet " << filename << " not found";
        return QString();
    }
    return file.readAll();
}
/*!
 * \brief AGeneralFunction::getMd5Hash 转换字节数组威MD5
 * \param data 要转换字节数组
 * \return 返回hash值
 */
QByteArray AGeneralFunction::getMd5Hash(const QByteArray& data)
{
    QByteArray hash_byte_array = QCryptographicHash::hash(data, QCryptographicHash::Md5);
    return hash_byte_array.toHex();
}
/*!
 * \brief AGeneralFunction::getLocalMachineMac 获取所有网络接口MAC地址
 * \return
 */
QByteArray AGeneralFunction::getLocalMachineMac()
{
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();
    QString md5;
    foreach(QNetworkInterface ni, nets)
    {
        md5 += ni.hardwareAddress();
    }
    return QByteArray(md5.toUtf8());
}
//DataBase
bool AGeneralFunction::addDbCon(const QString &type, const QString & Host, const QString &DBName, const QString &UserName, const QString &PassWord, const QString &connectName)
{
    if(QSqlDatabase::connectionNames().contains(connectName))
        return false;
    QString t_connectName;
    if(connectName.isEmpty()) {
        for(int i = 0; QSqlDatabase::connectionNames().contains(connectName) ; i++)
        {
            t_connectName = type + QString::number(i);
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

QList<QStringList> AGeneralFunction::getAllDbInfo()
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
bool AGeneralFunction::execSql(const QString &connectName, const QString &sql)
{
    QSqlDatabase db = QSqlDatabase::database(connectName);
    if(db.isValid()) {
        return db.exec(sql).isValid();
    }
    return false;
}
bool AGeneralFunction::execSql(const QString &connectName, const QString &sql, const QByteArray &data)
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

QSqlQuery AGeneralFunction::getTableData(const QString &connectName, const QString &tableName)
{
    QSqlDatabase db = QSqlDatabase::database(connectName);
    if(db.isValid())
        return db.exec(QString("select * from %1;").arg(tableName));
    return QSqlQuery();
}
/*!
 * \brief AJSExecute::createAllQObject 创建所有的可用类到js
 * \param object
 */
void AGeneralFunction::createQObjectToJS(QObject * object,  const QString &objName)
{
    if(objName.isEmpty() || objName.contains(QRegExp("[\\x4e00-\\x9fa5]+")))
        return;
    QJSValue scriptObject = getJsEngine().newQObject(object);
    getJsEngine().globalObject().setProperty(objName, scriptObject);
}

 QJSValue AGeneralFunction::execJS(const QString &js)
 {
     //QtConcurrent::run(QThreadPool::globalInstance(), [this, js](){
     QJSValue result = getJsEngine().evaluate(js);
     Q_ASSERT_X(result.isError() != true, "脚本错误", QString(tr("行号") + result.property("lineNumber").toString() + result.toString()).toUtf8().data());
     return result;
 }
QJSEngine & AGeneralFunction::getJsEngine()
{
    static QJSEngine g_jsEngine;
    return g_jsEngine;
}
