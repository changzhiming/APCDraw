#include "jsdesignwidget.h"
#include <QHBoxLayout>
#include <QTreeWidget>
#include <QTabWidget>
#include <drawCore/Item/ItemEx.h>
#include <QSplitter>
#include <QTextEdit>
#include <QMessageBox>
#include <QCloseEvent>

JSDesignWidget::JSDesignWidget(TItemEx *item, QWidget *parent) :
    QWidget(parent), m_Item(item)
{
    setWindowTitle(tr("脚本设计"));
    setAttribute(Qt::WA_DeleteOnClose, true);
    setWindowFlags(windowFlags()^Qt::WindowMaximizeButtonHint^Qt::WindowMinimizeButtonHint);
    setMinimumSize(800, 600);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    QSplitter *splitter = new QSplitter(this);
    vlayout->addWidget(splitter);
    QTreeWidget *treeWidget  = new QTreeWidget(this);
    QTabWidget *tabWidget = new QTabWidget(this); 
    splitter->addWidget(treeWidget);
    splitter->addWidget(tabWidget);
    splitter->setStretchFactor(1,1);

    mousePressTextEdit = new QTextEdit(this);
    tabWidget->insertTab(0, mousePressTextEdit, tr("鼠标按下"));
}

JSDesignWidget::~JSDesignWidget()
{
}
void JSDesignWidget::closeEvent(QCloseEvent *event)
{
    if(0 == QMessageBox::information(this, tr("提示"), tr("是否保存脚本"), tr("是"), tr("否"))) {
        m_Item->fSetMousePressJS(mousePressTextEdit->toPlainText());
        event->accept();
    }
    else {
        event->ignore();
    }
}
