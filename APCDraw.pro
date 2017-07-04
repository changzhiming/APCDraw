#-------------------------------------------------
#
# Project created by changzhiming 017-06-13T11:14:02
#
#-------------------------------------------------

QT       += core gui quick sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# QT Commonly used attributes
CONFIG   += c++11 link_pkgconfig

TEMPLATE = app

CONFIG(debug, debug|release) {
    TARGET = APCDrawd
} else {
    TARGET = APCDraw
}
win32 {
    LIBS += -ldbghelp
    #QT += winextras
}

OBJDIR = obj_temp
UI_DIR = $$OBJDIR/ui
RCC_DIR = $$OBJDIR/rcc
MOC_DIR = $$OBJDIR/moc
OBJECTS_DIR = $$OBJDIR/obj
DESTDIR = $$PWD/bin

# Set the QRC resource compression level
QMAKE_RESOURCE_FLAGS += -compress 9 -threshold 0

CONFIG   += warn_on exceptions_off
CONFIG   += link_pkgconfig

# Rules for creating/updating {ts|qm}-files
include(translations/i18n.pri)

# Build all the qm files now, to make RCC happy
system($$fromfile(translations/i18n.pri, updateallqm))

# Source and resource files
SOURCES += main.cpp\
        adrawmainwindow.cpp \
    projectdirectory/aprojectdirectorywindow.cpp \
    ageneralfunction.cpp \
#    drawCore/Widgets/Button.cpp \
#    drawCore/Widgets/InputEdit.cpp \
#    drawCore/Widgets/Table.cpp \
#    drawCore/Widgets/Widgets.cpp \
    drawCore/Graphics/Arc.cpp \
    drawCore/Graphics/Curve.cpp \
    drawCore/Graphics/Ellipse.cpp \
    drawCore/Graphics/Graphics.cpp \
    drawCore/Graphics/Light.cpp \
    drawCore/Graphics/Line.cpp \
    drawCore/Graphics/Meter.cpp \
    drawCore/Graphics/Pixmap.cpp \
    drawCore/Graphics/Point.cpp \
    drawCore/Graphics/Polygon.cpp \
    drawCore/Graphics/ProcessBar.cpp \
    drawCore/Graphics/Rect.cpp \
    drawCore/Graphics/Text.cpp \
    drawCore/Graphics/ValueText.cpp \
    drawCore/Item/Item.cpp \
    drawCore/Item/ItemEx.cpp \
    drawCore/Item/ItemFactory.cpp \
    drawCore/Scene/Scene.cpp \
    drawCore/Undo/Undo.cpp \
    drawCore/Undo/UndoAddDel.cpp \
    drawCore/Undo/UndoMoveDrag.cpp \
    drawCore/View/View.cpp \
    Dialog/aobjectanimation.cpp \
    login/login.cpp \
    Dialog/jsdesignwidget.cpp

HEADERS  += adrawmainwindow.h \
    aglobal.h \
    projectdirectory/aprojectdirectorywindow.h \
    ageneralfunction.h \
#    drawCore/Widgets/Button.h \
#    drawCore/Widgets/InputEdit.h \
#    drawCore/Widgets/Table.h \
#    drawCore/Widgets/Widgets.h \
#    drawCore/Widgets/WidgetsPub.h \
    drawCore/Graphics/Arc.h \
    drawCore/Graphics/Curve.h \
    drawCore/Graphics/Ellipse.h \
     drawCore/Graphics/Graphics.h \
    drawCore/Graphics/GraphicsPub.h \
    drawCore/Graphics/Light.h \
    drawCore/Graphics/Line.h \
    drawCore/Graphics/Meter.h \
    drawCore/Graphics/Pixmap.h \
    drawCore/Graphics/Point.h \
    drawCore/Graphics/Polygon.h \
    drawCore/Graphics/ProcessBar.h \
    drawCore/Graphics/Rect.h \
    drawCore/Graphics/Text.h \
    drawCore/Graphics/ValueText.h \
    drawCore/Item/Item.h \
    drawCore/Item/ItemEx.h \
    drawCore/Item/ItemFactory.h \
    drawCore/Scene/Scene.h \
    drawCore/Undo/Undo.h \
    drawCore/Undo/UndoAddDel.h \
    drawCore/Undo/UndoMoveDrag.h \
    drawCore/View/View.h \
    Dialog/aobjectanimation.h \
    login/login.h \
    Dialog/jsdesignwidget.h

RESOURCES += \
    image.qrc \

RC_ICONS = image/APCDraw1.ico

FORMS += \
    Dialog/aobjectanimation.ui \
    Dialog/jsdesignwidget.ui
