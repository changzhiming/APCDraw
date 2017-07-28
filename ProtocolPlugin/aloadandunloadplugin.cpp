#include "aloadandunloadplugin.h"
#include "ProtocolPlugin/abaseprotocol.h"
#include <QApplication>
#include <QPluginLoader>
#include <QDebug>
#include <QDir>

ALoadAndUnloadPlugin::ALoadAndUnloadPlugin(QObject *parent) : QObject(parent)
{
#ifdef QT_DEBUG
    qApp->addLibraryPath(QDir::currentPath() + "/ProtocolPlugin");
    QDir pluginDir("./ProtocolPlugin");
    foreach(QString path, pluginDir.entryList(QDir::Files))
    {
        QPluginLoader *plugin = new QPluginLoader(path, this);
        m_pluginList.append(plugin);
        ABaseProtocol * basePro = qobject_cast<ABaseProtocol *>(plugin->instance());
        if(basePro)
            m_PluginNameToEntity.insert(basePro->getProtocolName(), basePro);
    }
#else
    qApp->addLibraryPath(QDir::currentPath() + "/ProtocolPluginrR");
    QDir pluginDir("./ProtocolPluginR");
    foreach(QString path, pluginDir.entryList(QDir::Files))
    {
        QPluginLoader * plugin = new QPluginLoader(path, this);
        m_pluginList.append(plugin);
        ABaseProtocol * basePro = qobject_cast<ABaseProtocol *>(plugin->instance());
        if(basePro)
            m_PluginNameToEntity.insert(basePro->getProtocolName(), basePro);
    }
#endif

}
ALoadAndUnloadPlugin & ALoadAndUnloadPlugin::getInstance()
{
    static ALoadAndUnloadPlugin loadAndUnloadPlugin;
    return loadAndUnloadPlugin;
}

ALoadAndUnloadPlugin::~ALoadAndUnloadPlugin()
{
    foreach (auto var, m_pluginList) {
        var->unload();
        delete var;
    }
}

QStringList ALoadAndUnloadPlugin::getAllPluginName()
{
    QStringList allProtocolName;
    for(auto protocalName : m_PluginNameToEntity.keys())
    {
        allProtocolName<<protocalName;
    }
    return allProtocolName;
}

QByteArray ALoadAndUnloadPlugin::getTickData(QString pluginName, int mainId)
{
    if(m_PluginNameToEntity.contains(pluginName)) {
        return m_PluginNameToEntity.value(pluginName)->generateTickPackage(mainId);
    }
    return QByteArray();
}

QByteArray ALoadAndUnloadPlugin::getWriteData(QString pluginName, int mainId, quint32 addr, double value)
{
    if(m_PluginNameToEntity.contains(pluginName)) {
        return m_PluginNameToEntity.value(pluginName)->generateWriteProtocolPackage(mainId, addr, value);
    }
    return QByteArray();
}

QByteArray ALoadAndUnloadPlugin::getReadData(QString pluginName, int mainId, quint32 addr)
{
    if(m_PluginNameToEntity.contains(pluginName)) {
        return m_PluginNameToEntity.value(pluginName)->generateReadProtocolPackage(mainId, addr);
    }
    return QByteArray();
}
int ALoadAndUnloadPlugin::getMainId(QString pluginName, QByteArray &data)
{
    if(m_PluginNameToEntity.contains(pluginName)) {
        return m_PluginNameToEntity.value(pluginName)->getMainId(data);
    }
    return 0;
}

QHash<quint32, double> ALoadAndUnloadPlugin::getParseValue(QString pluginName, QByteArray &data)
{
    if(m_PluginNameToEntity.contains(pluginName)) {
        return m_PluginNameToEntity.value(pluginName)->parseProtocolPackage(data);
    }
    return QHash<quint32, double>();
}
