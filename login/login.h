#ifndef LOGIN_H
#define LOGIN_H

#include <QSqlDatabase>
#include <QWidget>
#include "aglobal.h"
class QLabel;
class QPushButton;
class QTimer;
class QLineEdit;
class Login : public QWidget
{
public:
    Login(QString dbname = QString(), QWidget * parent = 0);
    ~Login();
    void setErrorShowText(QString errorName);
    void startAllTime();

private slots:
    void timerAddTimeToDb();
    void okPress();
private:
    QPointer<QTimer> m_allRunTimeTimer;

    QPushButton *m_okPushButton;
    QPushButton *m_closePushButton;
    QLabel *m_loginError;
    QLineEdit *mLineEditName;
    QLineEdit *mLineEditPassWd;
    QString m_dbName;

    qreal m_useAllTime;
};

#endif // LOGIN_H
