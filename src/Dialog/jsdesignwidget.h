#ifndef JSDESIGNWIDGET_H
#define JSDESIGNWIDGET_H
#include <QWidget>
#include <QMap>
class QLineEdit;
class QTextEdit;
class QTabWidget;
class QTreeWidget;
class QHBoxLayout;
class ValueChangeScript;
class QComboBox;

class JSDesignWidget : public QWidget
{
    Q_OBJECT

public:
    explicit JSDesignWidget(QString title, QWidget *parent = 0);
    explicit JSDesignWidget(const QStringList &allDeviceName, ValueChangeScript *valueScript, QString title, QWidget *parent = 0);
    ~JSDesignWidget();
    void addJSWidget(QString mouseaction, QString js = "");
    void setIntervalTime(int time);

    void setTextEditFontSize(qreal size);
private:
    void setVarChangeEnable(const QStringList &allDeviceName, ValueChangeScript *valueScript);
signals:
    void okData(QMap<QString, QString> jsmap, QList<int> runInterValList);
    void okVariableData(ValueChangeScript *valueScript);
    void cancle();
protected:
    virtual void closeEvent(QCloseEvent *event);
private:
    QHBoxLayout *hLayout;   //功能栏布局
    QTabWidget *m_tabWidget;
    QTreeWidget *m_treeWidget;
    QHash<QString, QTextEdit *> m_ActionTextList;
    QLineEdit *m_timeLine = nullptr;
    //valuechanged
    ValueChangeScript *valueScript = nullptr;
    QComboBox *m_deviceName = nullptr;
    QLineEdit *m_valueScriptName = nullptr;
    QComboBox *m_deviceType = nullptr;
    QLineEdit *m_deviceAddr = nullptr;
};

#endif // JSDESIGNWIDGET_H
