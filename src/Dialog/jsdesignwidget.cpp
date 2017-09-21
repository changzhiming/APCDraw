#include "jsdesignwidget.h"
#include <QHBoxLayout>
#include <QTreeWidget>
#include <QTabWidget>
#include <QSplitter>
#include <QTextEdit>
#include <QMessageBox>
#include <QCloseEvent>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include "aglobal.h"

JSDesignWidget::JSDesignWidget(QString title, QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle(title);
    setAttribute(Qt::WA_DeleteOnClose, true);
    setWindowFlags(Qt::Dialog);
    setWindowFlags(windowFlags()^Qt::WindowContextHelpButtonHint);
    setWindowModality(Qt::WindowModal);
    setMinimumSize(800, 600);

    QVBoxLayout *vlayout = new QVBoxLayout(this);

    hLayout = new QHBoxLayout(0);
    vlayout->addLayout(hLayout);

    QSplitter *splitter = new QSplitter(this);
    vlayout->addWidget(splitter);

    hLayout->addStretch();
    QLabel *label = new QLabel(tr("间隔"));
    label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    hLayout->addWidget(label);

    m_timeLine = new QLineEdit(this);
    m_timeLine->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_timeLine->setInputMask("0000");
    m_timeLine->setText("1000");
    hLayout->addWidget(m_timeLine);

    label = new QLabel(tr("毫秒"));
    label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    hLayout->addWidget(label);

    m_treeWidget  = new QTreeWidget(this);
    m_tabWidget = new QTabWidget(this);

    m_treeWidget->setHeaderHidden(true);

    splitter->addWidget(m_treeWidget);
    splitter->addWidget(m_tabWidget);
    splitter->setStretchFactor(1, 1);

}
JSDesignWidget::JSDesignWidget(const QStringList &allDeviceName, ValueChangeScript *valueScript, QString title, QWidget *parent) : JSDesignWidget(title, parent)
{
    setVarChangeEnable(allDeviceName, valueScript);
}

JSDesignWidget::~JSDesignWidget()
{
}
void JSDesignWidget::setIntervalTime(int time)
{
    m_timeLine->setText(QString::number(time));
}

void JSDesignWidget::setTextEditFontSize(qreal size)
{
    foreach (auto *textedit, m_ActionTextList.values()) {
        textedit->setFontPointSize(size);
    }
}

//设置是否是数值改变 窗体
void JSDesignWidget::setVarChangeEnable(const QStringList &allDeviceName, ValueChangeScript *valueScript)
{
    IF_TRUE_RUN(!valueScript, return)

    m_timeLine->hide();
    this->valueScript = valueScript;

    hLayout->insertWidget(1, new QLabel("变量名", this));
    m_valueScriptName = new QLineEdit(valueScript->m_scriptValueName, this);
    hLayout->insertWidget(2, m_valueScriptName);

    hLayout->insertWidget(3, new QLabel("设备名", this));
    m_deviceName = new QComboBox(this);
    m_deviceName->addItem("无");
    m_deviceName->addItems(allDeviceName);
    m_deviceName->setCurrentText(valueScript->m_deviceName);
    hLayout->insertWidget(4, m_deviceName);

    m_deviceType = new QComboBox(this);
    m_deviceType->addItems(QStringList()<<tr("无")<<tr("离散输入")<<tr("线圈")<<tr("输入寄存器")<<tr("保持寄存器"));
    m_deviceType->setCurrentIndex(valueScript->m_deviceType);
    hLayout->insertWidget(5, new QLabel("变量类型", this));
    hLayout->insertWidget(6, m_deviceType);

    hLayout->insertWidget(7, new QLabel("变量地址", this));
    m_deviceAddr = new QLineEdit(this);
    m_deviceAddr->setInputMask("hhhhh");
    m_deviceAddr->setText(QString::number(valueScript->m_deviceAddr));
    hLayout->insertWidget(8, m_deviceAddr);
}

void JSDesignWidget::addJSWidget(QString mouseaction, QString js)
{
    QTextEdit *textEdit = new QTextEdit(this);
    textEdit->setFontPointSize(12);
    textEdit->setText(js);
    m_tabWidget->addTab(textEdit, mouseaction);

    m_ActionTextList.insert(mouseaction, textEdit);
}

void JSDesignWidget::closeEvent(QCloseEvent *event)
{
    if(0 == QMessageBox::information(this, tr("提示"), tr("是否保存脚本"), tr("是"), tr("否"))) {
        if(valueScript && m_ActionTextList.size()) {
            valueScript->m_valueJs = m_ActionTextList.values().first()->toPlainText();
            valueScript->m_deviceName = m_deviceName->currentText();
            valueScript->m_scriptValueName = m_valueScriptName->text();
            valueScript->m_deviceType = m_deviceType->currentIndex();
            valueScript->m_deviceAddr = m_deviceAddr->text().toInt();

            emit okVariableData(valueScript);
            event->accept();
            return;
        }

        QMap<QString, QString> jsmap;
        QList<int> runInterValList;

        for(auto index = m_ActionTextList.begin(); index != m_ActionTextList.end(); index++)
        {
            IF_TRUE_RUN(index.value()->toPlainText().isEmpty(), break)
            jsmap.insert(index.key(), index.value()->toPlainText());
            runInterValList.append(m_timeLine->text().toInt());
        }
        emit okData(jsmap, runInterValList);
    } else {
        emit cancle();
    }
    event->accept();
}
