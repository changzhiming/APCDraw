#-------------------------------------------------
#
# Project created by changzhiming 017-06-13T11:14:02
#
#-------------------------------------------------

QT += core gui sql printsupport quick serialbus network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# QT Commonly used attributes
CONFIG   += c++11 link_pkgconfig
#DEFINES += QCUSTOMPLOT_USE_LIBRARY
TEMPLATE = app

DEFINES += APCDraw

CONFIG(debug, debug|release) {
    TARGET = APCDrawd
    LIBS += -L$$PWD/bin/ -lQCustomplotd
} else {
    TARGET = APCDraw
    #DEFINES += QT_NO_DEBUG_OUTPUT
    LIBS += -L$$PWD/bin/ -lQCustomplot
}

OBJDIR = obj_temp
UI_DIR = $$OBJDIR/ui
RCC_DIR = $$OBJDIR/rcc
MOC_DIR = $$OBJDIR/moc
OBJECTS_DIR = $$OBJDIR/obj
DESTDIR = $$PWD/bin

CONFIG   += warn_on exceptions_off
CONFIG   += link_pkgconfig

# Rules for creating/updating {ts|qm}-files
#include(translations/i18n.pri)

# Build all the qm files now, to make RCC happy
#system($$fromfile(translations/i18n.pri, updateallqm))

# Source and resource files
SOURCES += main_draw.cpp\
        adrawmainwindow.cpp \
    ageneralfunction.cpp \
    drawCore/Widgets/Button.cpp \
    drawCore/Widgets/InputEdit.cpp \
    drawCore/Widgets/Table.cpp \
    drawCore/Widgets/Widgets.cpp \
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
    Dialog/jsdesignwidget.cpp \
    drawCore/Plot/abstractplot.cpp \
    drawCore/Plot/graph.cpp \
    drawCore/Plot/bar.cpp \
    drawCore/Plot/piechart.cpp \
    drawCore/Plot/instrumentpanel.cpp \
    ui/login.cpp \
    adeviceinfo.cpp \
    ui/newdevice.cpp \
    ui/ashowinfoanimation.cpp \
    Dialog/itemProperty/apixmapanimation.cpp \
    ui/awindowproperty.cpp \
    ui/newdatabase.cpp

HEADERS  += aglobal.h \
    adrawmainwindow.h \
    ageneralfunction.h \
    drawCore/Widgets/Button.h \
    drawCore/Widgets/InputEdit.h \
    drawCore/Widgets/Table.h \
    drawCore/Widgets/Widgets.h \
    drawCore/Widgets/WidgetsPub.h \
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
    Dialog/jsdesignwidget.h \
    drawCore/Plot/abstractplot.h \
    drawCore/Plot/graph.h \
    drawCore/Plot/bar.h \
    drawCore/Plot/piechart.h \
    drawCore/Plot/instrumentpanel.h \
    ui/login.h \
    adeviceinfo.h \
    drawCore/Plot/plotpub.h \
    ui/newdevice.h \
    ui/ashowinfoanimation.h \
    Dialog/itemProperty/apixmapanimation.h \
    ui/awindowproperty.h \
    ui/newdatabase.h

INCLUDEPATH += $$PWD/include

RESOURCES += \
    Draw.qrc \

#RC_ICONS = image/APCDraw1.ico

FORMS += \
    Dialog/aobjectanimation.ui \
    ui/newdevice.ui \
    ui/ashowinfoanimation.ui \
    Dialog/itemProperty/apixmapanimation.ui \
    ui/awindowproperty.ui \
    ui/newdatabase.ui

