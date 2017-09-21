#include "newdatabase.h"
#include "ui_newdatabase.h"
#include "aglobal.h"
#include <QCloseEvent>
#include <QSqlDatabase>

NewDataBase::NewDataBase(DataBaseInfo *dbInfo, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewDataBase), m_DbInfo(dbInfo)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(windowFlags()^Qt::WindowContextHelpButtonHint);
    setWindowModality(Qt::WindowModal);
    IF_TRUE_RUN(!dbInfo, return)
    ui->lineEditDBexplain->setText(dbInfo->m_DataBaseInfoName);
    ui->comboBoxDataBaseType->addItems(QSqlDatabase::drivers());
    ui->lineEditHostName->setText(dbInfo->m_HostName);
    ui->lineEditDatabaseName->setText(dbInfo->m_DbName);
    ui->lineEditUserName->setText(dbInfo->m_UserName);
    ui->lineEditPasswd->setText(dbInfo->m_Passwd);
}

NewDataBase::~NewDataBase()
{
    delete ui;
}
void NewDataBase::closeEvent(QCloseEvent *event)
{
    IF_TRUE_RUN(!m_ok && !m_cancle, emit cancle(m_DbInfo))
    event->accept();
}

void NewDataBase::on_pushButtonOk_clicked()
{
    m_DbInfo->m_DataBaseInfoName = ui->lineEditDBexplain->text();
    m_DbInfo->m_DbType = ui->comboBoxDataBaseType->currentText();
    m_DbInfo->m_HostName = ui->lineEditHostName->text();
    m_DbInfo->m_DbName = ui->lineEditDatabaseName->text();
    m_DbInfo->m_UserName = ui->lineEditUserName->text();
    m_DbInfo->m_Passwd = ui->lineEditPasswd->text();
    m_ok = true;
    emit ok(m_DbInfo);
    close();
}

void NewDataBase::on_pushButtonCancle_clicked()
{
    m_cancle = true;
    emit cancle(m_DbInfo);
    close();
}
