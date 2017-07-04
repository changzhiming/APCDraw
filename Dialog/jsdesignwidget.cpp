#include "jsdesignwidget.h"
#include "ui_jsdesignwidget.h"
#include <QHBoxLayout>
#include <QTreeWidget>
#include <QTabWidget>

JSDesignWidget::JSDesignWidget(QStringList listName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JSDesignWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true);
    setWindowFlags(windowFlags()^Qt::WindowMaximizeButtonHint^Qt::WindowMinimizeButtonHint);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    QTreeWidget *treeWidget  = new QTreeWidget(this);
    QTabWidget *tabWidget = new QTabWidget(this);

    mainLayout->addWidget(treeWidget);
    mainLayout->addWidget(tabWidget);
}

JSDesignWidget::~JSDesignWidget()
{
    delete ui;
}
