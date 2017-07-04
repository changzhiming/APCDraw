#include <ageneralfunction.h>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QNetworkInterface>
QT_BEGIN_NAMESPACE_APC

/*!
  \class AGeneralFunction
  \brief
  \inmodule APCUI
 */

/*!
 * \brief AGeneralFunction::AGeneralFunction
 */
AGeneralFunction::AGeneralFunction()
{}

/*!
  \brief GlobalFunction::getStylesheet \a filename
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
 * \brief AGeneralFunction::getDatabaseByConName 通过连接名字获取database
 * \return
 */
QSqlDatabase AGeneralFunction::getDatabaseByConName(const QString &databaseName, const QString& conName)
{
    QSqlDatabase db1 = QSqlDatabase::database(conName);
    if(db1.isValid()) {
        if(!db1.open()) {
            db1.open();
        }
        return db1;
    } else {
        QSqlDatabase sqlLiteDb = QSqlDatabase::addDatabase("QSQLITE", "SqliteConnect");
        sqlLiteDb.setDatabaseName(databaseName);
        sqlLiteDb.setUserName("BJM");
        sqlLiteDb.setPassword("chang123.");
        sqlLiteDb.open();
        return sqlLiteDb;
    }
}

QSqlDatabase AGeneralFunction::getDatabaseByConName(const QString &conName)
{
    QSqlDatabase db1 = QSqlDatabase::database(conName);
    if(db1.isValid()) {
        if(!db1.open()) {
            db1.open();
        }
        return db1;
    } else {
        QMessageBox::warning(0, tr("没有可用数据库"), tr("无可用数据库"));
        return QSqlDatabase();
    }
}

QByteArray AGeneralFunction::getMd5Hash(QByteArray data)
{
    QByteArray hash_byte_array = QCryptographicHash::hash(data, QCryptographicHash::Md5);
    return hash_byte_array.toHex();
}

QByteArray AGeneralFunction::get_localmachine_mac()
{
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();
    QString md5;
    foreach(QNetworkInterface ni,nets)
    {
        md5+=ni.hardwareAddress();
    }
    return QByteArray(md5.toUtf8());
}
QT_END_NAMESPACE_APC
