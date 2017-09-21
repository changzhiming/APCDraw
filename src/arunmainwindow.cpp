#include "arunmainwindow.h"
#include "ui_arunmainwindow.h"

ARunMainWindow::ARunMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ARunMainWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}
ARunMainWindow *ARunMainWindow::getInstance()
{
    static ARunMainWindow *runMainwindow = new ARunMainWindow(0);
    return runMainwindow;
}

ARunMainWindow::~ARunMainWindow()
{
    delete ui;
}
