/*
* @file
* @brief 全局变量和参数设定
*
* @author 常志明
* @version v1.0
* @date 2017.6.13
*
* @b 修改记录：
* @li 日期
* @- add setA()
* @- changed getA()
*/

#ifndef AGLOBAL_H
#define AGLOBAL_H
#include <QtGlobal>
#include <QString>
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#if !defined(QT_STATIC) && !defined(QAPC_NO_LIB)
#  if defined(QT_BUILD_APC_LIB)
#    define Q_APC_EXPORT Q_DECL_EXPORT
#  else
#    define Q_APC_EXPORT Q_DECL_IMPORT
#  endif
#else
#  define Q_APC_EXPORT
#endif
//全局结构体
struct CycleRunScript {
    QString m_windowName;
    QString m_enterJs;
    QString m_cycleRunJs;
    QString m_leaveJs;
    int m_cycleRunIntervalTime = 0;
};
struct ValueChangeScript {
    QString m_scriptValueName;
    QString m_deviceName;
    int m_deviceType = 0;
    quint16 m_deviceAddr = 0;
    QString m_valueJs;
};

struct DataBaseInfo {
    QString m_DataBaseInfoName;
    QString m_DbType;
    QString m_HostName;
    QString m_DbName;
    QString m_UserName;
    QString m_Passwd;
};

#define IF_TRUE_RUN(condition, run) if(condition) { run;}  //条件为真 执行后面语句  适合单行run

#endif // AGLOBAL_H
