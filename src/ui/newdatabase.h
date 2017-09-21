#ifndef NEWDATABASE_H
#define NEWDATABASE_H

#include <QWidget>

namespace Ui {
class NewDataBase;
}
class DataBaseInfo;
class NewDataBase : public QWidget
{
    Q_OBJECT

public:
    explicit NewDataBase(DataBaseInfo *dbInfo, QWidget *parent = 0);
    ~NewDataBase();
protected:
    void closeEvent(QCloseEvent *event);
signals:
    void ok(DataBaseInfo *dbInfo);
    void cancle(DataBaseInfo *dbInfo);

private slots:
    void on_pushButtonOk_clicked();

    void on_pushButtonCancle_clicked();

private:
    Ui::NewDataBase *ui;
    DataBaseInfo *m_DbInfo = nullptr;

    bool m_ok = false;
    bool m_cancle = false;
};

#endif // NEWDATABASE_H
