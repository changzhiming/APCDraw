#ifndef NEWDEVICE_H
#define NEWDEVICE_H

#include <QWidget>
class ADeviceInfo;
namespace Ui {
class NewDevice;
}

class NewDevice : public QWidget
{
    Q_OBJECT

public:
    explicit NewDevice(ADeviceInfo *deviceinfo, QWidget *parent = 0);
    ~NewDevice();

    void setexistVarName(QStringList varNameList);
protected:
    void closeEvent(QCloseEvent *event);
signals:
    void ensure(ADeviceInfo *deviceinfo);
    void cancle(ADeviceInfo *deviceinfo);

private slots:
    bool test();
    bool saveDeviceInfo();
    void on_pushButtonCancle_clicked();

    void on_pushButtonOk_clicked();

    void on_comboBoxComMode_currentIndexChanged(const QString &arg1);

private:

    Ui::NewDevice *ui;
    ADeviceInfo *m_deviceinfo = nullptr;
    QStringList m_varNameList;

    bool m_ok = false;
    bool m_cancle = false;
};

#endif // NEWDEVICE_H
