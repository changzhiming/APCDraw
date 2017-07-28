#ifndef ALOADANDUNLOADPLUGIN_H
#define ALOADANDUNLOADPLUGIN_H

#include <QObject>
#include <QHash>
class QPluginLoader;
class ABaseProtocol;
class ALoadAndUnloadPlugin : public QObject
{
    Q_OBJECT
public:
    static ALoadAndUnloadPlugin & getInstance();
    ~ALoadAndUnloadPlugin();

    QStringList getAllPluginName();

    QByteArray getTickData(QString pluginName, int mainId);
    QByteArray getWriteData(QString pluginName, int mainId, quint32 addr, double value);
    QByteArray getReadData(QString pluginName, int mainId, quint32 addr);

    int getMainId(QString pluginName, QByteArray &data);
    QHash<quint32, double> getParseValue(QString pluginName, QByteArray &data);

private:
    explicit ALoadAndUnloadPlugin(QObject *parent = 0);
    QList<QPluginLoader *> m_pluginList;
    QHash<QString, ABaseProtocol *> m_PluginNameToEntity;  //名称到实体
};

#endif // ALOADANDUNLOADPLUGIN_H
