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

#include "aglobal.h"
#include <QFile>
#include <QSqlDatabase>
QT_BEGIN_NAMESPACE_APC

class AGeneralFunction : public QObject
{
public:
    explicit AGeneralFunction();
    static QString getStylesheet(const QString &filename);

    static QSqlDatabase getDatabaseByConName(const QString &databaseName, const QString &conName);
    static QSqlDatabase getDatabaseByConName(const QString &conName);

    static QByteArray getMd5Hash(QByteArray data);
    static QByteArray get_localmachine_mac();
};
QT_END_NAMESPACE_APC

#endif // AGENERALFUNCTION_H
