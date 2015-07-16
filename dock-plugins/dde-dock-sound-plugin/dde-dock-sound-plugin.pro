#-------------------------------------------------
#
# Project created by QtCreator 2015-07-13T10:27:10
#
#-------------------------------------------------

QT       += core gui widgets dbus

TARGET = dde-dock-sound-plugin
TEMPLATE = lib
CONFIG += plugin c++11
INCLUDEPATH += ../../modules/sound/

SOURCES += soundplugin.cpp \
    ../../modules/sound/dbus/dbusaudio.cpp \
    ../../modules/sound/dbus/dbusaudiosink.cpp \
    soundicon.cpp \
    mainitem.cpp \
    soundcontent.cpp \
    deviceframe.cpp \
    appframe.cpp \
    ../../modules/sound/dbus/dbusaudiosinkinput.cpp \
    appiconslider.cpp \
    deviceiconslider.cpp \
    iconlabel.cpp

HEADERS += soundplugin.h \
    ../../modules/sound/dbus/dbusaudio.h \
    ../../modules/sound/dbus/dbusaudiosink.h \
    soundicon.h \
    mainitem.h \
    soundcontent.h \
    deviceframe.h \
    appframe.h \
    ../../modules/sound/dbus/dbusaudiosinkinput.h \
    appiconslider.h \
    deviceiconslider.h \
    iconlabel.h
DISTFILES += dde-dock-sound-plugin.json

unix {
    target.path = /usr/share/dde-dock/plugins/
    INSTALLS += target
}

PKGCONFIG += gtk+-2.0

RESOURCES += \
    qss.qrc
