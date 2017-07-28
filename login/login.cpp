#include "login.h"
#include "ageneralfunction.h"
#include "database/aexecdbthread.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QTimer>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QFileInfo>
#include <QDateTime>
#include <QApplication>
#include <QInputDialog>

Login::Login(QString dbname, QWidget * parent) : QWidget(parent), m_dbName(dbname)
{
    //授权码
    AExecDbThread::addDbCon("QSQLITE", "", m_dbName, "BJM", "chang123." , "Sqlite1");
    QSqlDatabase sql = AExecDbThread::getDb("Sqlite1");
    QSqlQuery query(sql);
    query.exec(QString("select login.UseTime, login.year_num from login"));
    if(query.next()) {
        if(query.value("UseTime").toLongLong() >= 3153600) {
            bool ok;
            bool authorize = false;
            QString text = QInputDialog::getText(this, tr("注册"), tr("请输入注册码："), QLineEdit::Normal, "", &ok);
            if (ok && !text.isEmpty()) {
                int year = query.value("year_num").toLongLong();
                qDebug()<<QAPC::AGeneralFunction::getMd5Hash(QAPC::AGeneralFunction::get_localmachine_mac().append(QString::number(year)));
                if(text == QAPC::AGeneralFunction::getMd5Hash(QAPC::AGeneralFunction::get_localmachine_mac().append(QString::number(year)))) {

                    QSqlQuery query(sql);
                    query.exec(QString("update login set UseTime = %1").arg(0));
                    query.exec(QString("update login set year_num = %1").arg(++year));
                    authorize = true;
                }
            }
            if(!authorize)
                qApp->quit();
        }
    }
    addTimeToDbQuery = QSqlQuery(AExecDbThread::getDb("Sqlite1"));
    //UI
    mLineEditName = new QLineEdit(this);
    mLineEditPassWd = new QLineEdit(this);

    mLineEditPassWd->setEchoMode(QLineEdit::Password);
    mLineEditPassWd->setStyleSheet("lineedit-password-character: 42");

    QHBoxLayout *mLayoutButton = new QHBoxLayout();

    m_okPushButton = new QPushButton(tr("登录"), this);
    m_closePushButton = new QPushButton(tr("取消"), this);

    mLayoutButton->addWidget(m_okPushButton);
    mLayoutButton->addWidget(m_closePushButton);

    QGridLayout *mLayoutMain = new QGridLayout(this);
    QLabel *labelPixmap=new QLabel(this);
    labelPixmap->setPixmap(QPixmap("login.png"));

    mLayoutMain->addWidget(labelPixmap, 0, 0, 3, 3);
    mLayoutMain->addWidget(new QLabel(tr("用户"), this), 0, 3);
    mLayoutMain->addWidget(mLineEditName, 0, 4);

    mLayoutMain->addWidget(new QLabel(tr("密码")), 1, 3);
    mLayoutMain->addWidget(mLineEditPassWd, 1, 4);

    m_loginError = new QLabel(this);
    mLayoutMain->addWidget(m_loginError, 2, 3, 1, 2);
    m_loginError->hide();
    mLayoutMain->addLayout(mLayoutButton, 3, 3, 1, 2);

    // 设置默认


    m_okPushButton->setFocus();
    m_okPushButton->setShortcut(QKeySequence::InsertParagraphSeparator);
    m_okPushButton->setShortcut(Qt::Key_Enter);
    m_okPushButton->setShortcut(Qt::Key_Return);

    setLayout(mLayoutMain);

    setWindowTitle(tr("建筑节能系统登录"));

    connect(m_okPushButton, &QPushButton::clicked, [=](){okPress();});
    connect(m_closePushButton, &QPushButton::clicked, [=](){close();});

    setWindowFlags(windowFlags()^Qt::WindowMaximizeButtonHint^Qt::WindowMinimizeButtonHint);
}
Login::~Login()
{
    startAllTime();
}

void Login::setErrorShowText(QString errorName)
{
    m_loginError->setText(errorName);
    m_loginError->show();
}
//存储最后文件最后访问时间
void Login::startAllTime()
{
    QFileInfo fileInfo(m_dbName);

    QSqlDatabase sql = AExecDbThread::getDb("Sqlite1");
    QSqlQuery query(sql);
    qDebug()<<query.exec(QString("update login set CreateTime = %1").arg(fileInfo.lastRead().toMSecsSinceEpoch()));
}

void Login::timerAddTimeToDb()
{
    static QSqlQuery query(AExecDbThread::getDb("Sqlite1"));

    m_useAllTime += 60;
    query.exec(QString("update login set UseTime = %1").arg(m_useAllTime));

    query.exec(QString("select login.UseTime from login"));
    if(query.next()) {
        if(query.value("UseTime").toLongLong() >= 3153600) {
            qApp->quit();
        }
    }
}
void Login::okPress()
{
    if(mLineEditName->text().isEmpty() || mLineEditPassWd->text().isEmpty()) {
        setErrorShowText(tr("用户名或密码错误"));
        return;
    } else {
        if(!m_dbName.isEmpty()) {
            QSqlDatabase sql = AExecDbThread::getDb("Sqlite1");

            QSqlQuery query(sql);
            query.exec("SELECT * FROM login");
            while(query.next()) {
                if(mLineEditName->text() == query.value(0).toString() && mLineEditPassWd->text() == query.value(1).toString()) {
                    //
                    m_useAllTime = query.value("UseTime").toInt();

                    QFileInfo fileInfo(m_dbName);
                    qDebug()<<fileInfo.lastRead().toMSecsSinceEpoch()<<query.value("CreateTime").toULongLong();
                    if(fileInfo.lastRead().toMSecsSinceEpoch() != query.value("CreateTime").toULongLong()) {
                        QMessageBox::warning(this, tr("工程文件被损坏"), tr("工程文件被损坏"));
                        return;
                    }
                    m_allRunTimeTimer = new QTimer(this);
                    connect(m_allRunTimeTimer, &QTimer::timeout, this, &Login::timerAddTimeToDb);
                    m_allRunTimeTimer->start(60000);
                }
            }
        } else {
            QMessageBox::warning(this, tr("系统文件丢失"), tr("丢失系统文件请联系厂家"));
        }
    }
}
