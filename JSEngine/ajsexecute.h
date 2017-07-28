#ifndef AJSEXECUTE_H
#define AJSEXECUTE_H

#include <QObject>
#include <QJSEngine>

class AJSExecute : public QObject
{
    Q_OBJECT
public:   
    static AJSExecute & getInstance();
    ~AJSExecute();
    void createQObjectToJS(QObject * object,  QString objName);

    template<typename T> inline void createProperty(QString proName, T def);

public slots:
    void execJS(QString js);

private:
    explicit AJSExecute(QObject *parent = 0);
    QJSEngine myEngine;
};
template<typename T> inline void AJSExecute::createProperty(QString proName, T def)
{
    myEngine.globalObject().setProperty(proName, def);
}

#endif // AJSEXECUTE_H
