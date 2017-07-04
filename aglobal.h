﻿/*
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
#include <QDebug>
#include <QPointer>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#define QT_BEGIN_NAMESPACE_APC namespace QAPC {
#define QT_END_NAMESPACE_APC  }
#define QAPC_USE_NAMESPACE using namespace QAPC;

#if !defined(QT_STATIC) && !defined(QAPC_NO_LIB)
#  if defined(QT_BUILD_APC_LIB)
#    define Q_APC_EXPORT Q_DECL_EXPORT
#  else
#    define Q_APC_EXPORT Q_DECL_IMPORT
#  endif
#else
#  define Q_APC_EXPORT
#endif

#endif // AGLOBAL_H
