#include "newdevice.h"
#include "ui_newdevice.h"
#include "adeviceinfo.h"
#include "ashowinfoanimation.h"
#include <QHostAddress>
#include <QDebug>
#include <ui/ashowinfoanimation.h>
#include <QCloseEvent>
#include "aglobal.h"
NewDevice::NewDevice(ADeviceInfo *deviceinfo, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewDevice), m_deviceinfo(deviceinfo)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(windowFlags()^Qt::WindowContextHelpButtonHint);
    setWindowModality(Qt::WindowModal);

    ui->lineEditTcpIp->setText(QHostAddress(QHostAddress::LocalHost).toString());
    ui->groupBoxSerial->hide();
    //init
    ui->lineEditDeviceName->setText(m_deviceinfo->m_deviceName);
    ui->lineEditDeviceDescribe->setText(m_deviceinfo->m_deviceDescript);
    ui->doubleSpinBoxUpdateCycle->setValue(m_deviceinfo->m_tickInterval);
    ui->doubleSpinBoxTimeOut->setValue(m_deviceinfo->m_timeOut);
    ui->spinBoxDeviceAddr->setValue(m_deviceinfo->m_serverAddr);

    ui->comboBoxComMode->setCurrentIndex(m_deviceinfo->m_connectType);
    ui->comboBoxComProtocol->setCurrentText(m_deviceinfo->m_connectProtocol);
    ui->doubleSpinBoxComInterval->setValue(m_deviceinfo->m_OrderIntervalTime);
    ui->spinBoxReconnectNum->setValue(m_deviceinfo->m_numberOfRetries);

    ui->spinBoxFailNum->setValue(m_deviceinfo->m_sendFailNumDisconnect);
    ui->spinBoxFailRecovery->setValue(m_deviceinfo->m_reconnectionTime);
    ui->lineEditTcpIp->setText(m_deviceinfo->m_ip);
    ui->lineEditPort->setText(QString::number(m_deviceinfo->m_port));
}

NewDevice::~NewDevice()
{
    delete ui;
}
void NewDevice::closeEvent(QCloseEvent *event)
{
    IF_TRUE_RUN(!m_ok && !m_cancle, emit cancle(m_deviceinfo))
    event->accept();
}

void NewDevice::setexistVarName(QStringList varNameList)
{
    m_varNameList = varNameList;
}

bool NewDevice::test()
{
    return true;
}

bool NewDevice::saveDeviceInfo()
{
    m_deviceinfo->m_deviceName = ui->lineEditDeviceName->text();
    m_deviceinfo->m_deviceDescript = ui->lineEditDeviceDescribe->text();
    m_deviceinfo->m_tickInterval = ui->doubleSpinBoxUpdateCycle->value();
    m_deviceinfo->m_timeOut = ui->doubleSpinBoxTimeOut->value();
    m_deviceinfo->m_serverAddr = ui->spinBoxDeviceAddr->value();
    m_deviceinfo->m_connectType = (ModbusConnection)ui->comboBoxComMode->currentIndex();
    m_deviceinfo->m_connectProtocol = ui->comboBoxComProtocol->currentText();
    m_deviceinfo->m_OrderIntervalTime = ui->doubleSpinBoxComInterval->value();
    m_deviceinfo->m_numberOfRetries = ui->spinBoxReconnectNum->value();
    m_deviceinfo->m_sendFailNumDisconnect = ui->spinBoxFailNum->value();
    m_deviceinfo->m_reconnectionTime = ui->spinBoxFailRecovery->value();

    m_deviceinfo->m_ip = ui->lineEditTcpIp->text();
    m_deviceinfo->m_port = ui->lineEditPort->text().toInt();
    return true;
}

void NewDevice::on_pushButtonCancle_clicked()
{
    m_cancle = true;
    emit cancle(m_deviceinfo);
    close();
}

void NewDevice::on_pushButtonOk_clicked()
{
    saveDeviceInfo();
    AShowInfoAnimation *info = new AShowInfoAnimation("保存成功");
    info->show();
    m_ok = true;
    emit ensure(m_deviceinfo);
    close();
}

void NewDevice::on_comboBoxComMode_currentIndexChanged(const QString &arg1)
{
    if(arg1 == QStringLiteral("串口")) {
        ui->groupBoxSerial->show();
        ui->groupBoxNet->hide();
    }
    if(arg1 == QStringLiteral("网络")) {
        ui->groupBoxSerial->hide();
        ui->groupBoxNet->show();
    }
}
