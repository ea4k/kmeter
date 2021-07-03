#/***************************************************************************
#                         KMeter.pro
#						  -------------------
#    begin                : Apr 2020-2021
#    copyright            : (C) 2020-2021 by Jaime Robles
#    email                : jaime@robles.es
# ***************************************************************************
#/*****************************************************************************
# * This file is part of KMeter.                                                *
# *                                                                           *
# *    KMeter is free software: you can redistribute it and/or modify           *
# *    it under the terms of the GNU General Public License as published by   *
# *    the Free Software Foundation, either version 3 of the License, or      *
# *    (at your option) any later version.                                    *
# *                                                                           *
# *    KMeter is distributed in the hope that it will be useful,                *
# *    but WITHOUT ANY WARRANTY; without even the implied warranty of         *
# *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
# *    GNU General Public License for more details.                           *
# *                                                                           *
# *    You should have received a copy of the GNU General Public License      *
# *    along with KLog.  If not, see <https://www.gnu.org/licenses/>.         *
# *                                                                           *
# *****************************************************************************/
CONFIG += app_bundle
CONFIG += static
CONFIG -=depend_includepath
#CONFIG += release
TEMPLATE = app

VERSION = 0
DEFINES += VERSION_STRING=\\\"$${VERSION}\\\"

APP_NAME = KMetter
DEFINES += APP_NAME="$$APP_NAME"

APP_UNIX_NAME = kmeter
DEFINES += APP_UNIX_NAME="$$APP_UNIX_NAME"

message(Building $${APP_NAME} $${VERSION})
message(Qt $$[QT_VERSION] in $$[QT_INSTALL_PREFIX])

QT += core \
    gui \
    sql \
    network \
    serialport \
    printsupport \
    charts \
    widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

greaterThan(QT_MAJOR_VERSION, 4):greaterThan(QT_MINOR_VERSION, 4)
{
    macx:QMAKE_LFLAGS += -Wl,-rpath,@executable_path/../Frameworks
}

DEFINES += APP_NAME="$$APP_NAME"

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

message(Sources)
SOURCES += \
        levelmeter.cpp \
        main.cpp \
        mainwindow.cpp \
        numbersmeterwidget.cpp \
        pwrlevelmeter.cpp \
        serialread.cpp \
        setupwidget.cpp \
        swrlevelmeter.cpp

HEADERS += \
        levelmeter.h \
        mainwindow.h \
        numbersmeterwidget.h \
        pwrlevelmeter.h \
        serialread.h \
        setupwidget.h \
        swrlevelmeter.h

message (Other files)

OTHER_FILES += \
    Changelog \
    COPYING \
    AUTHORS \
    README

message (More...)

#RESOURCES += kmeter.qrc
DESTDIR = build/target/
OBJECTS_DIR = build/obj/
MOC_DIR = build/moc/
RCC_DIR = build/rcc/
FORMS +=
# Tell Qt Linguist that we use UTF-8 strings in our sources
CODECFORTR = UTF-8
CODECFORSRC = UTF-8
#include(translations/translations.pri)
message (Translations)

TRANSLATIONS = translations/kmeter_es.ts
    #translations/klog_pl.ts \
    #translations/klog_ja.ts

message(End of translations...)

isEmpty(QMAKE_LRELEASE) {
    win32|os2:QMAKE_LRELEASE = $$[QT_INSTALL_BINS]\lrelease.exe
    else:QMAKE_LRELEASE = $$[QT_INSTALL_BINS]/lrelease
    unix {
        !exists($$QMAKE_LRELEASE) { QMAKE_LRELEASE = lrelease-qt5 }
    } else {
        !exists($$QMAKE_LRELEASE) { QMAKE_LRELEASE = lrelease }
    }
}

updateqm.input = TRANSLATIONS
updateqm.output = $$DESTDIR/translations/${QMAKE_FILE_BASE}.qm
updateqm.commands = $$QMAKE_LRELEASE ${QMAKE_FILE_IN} -qm $$DESTDIR/translations/${QMAKE_FILE_BASE}.qm
updateqm.CONFIG += no_link target_predeps
QMAKE_EXTRA_COMPILERS += updateqm


# deploy
DISTFILES += Changelog COPYING

unix:!mac {
    DEFINES += APP_LINUX
    CONFIG  += c++11
# Translations should be copied in /usr/share/klog/translations
# https://en.wikipedia.org/wiki/Filesystem_Hierarchy_Standard
    isEmpty(PREFIX):PREFIX = /usr
    BINDIR = $$PREFIX/bin
    DATADIR = $$PREFIX/share
    PKGDATADIR = $$DATADIR/kmeter
    INSTALLS += target
    target.path = $$BINDIR
    translations.path = $$PKGDATADIR/translations
    translations.files += $$DESTDIR/translations/*
    #INSTALLS += translations
    datafiles.path = $$PKGDATADIR
    datafiles.files = $$DISTFILES
    INSTALLS += translations
    INSTALLS += datafiles
    #LIBS += -lhamlib
}

macx: {
    #ICON = kmeter.icns
    TARGET = KMeter
    CONFIG += c++11
}

win32: {
    #RC_ICONS = kmeter.ico
    TARGET = kmeter
    QMAKE_TARGET_COMPANY = EA4K
    QMAKE_TARGET_DESCRIPTION = Power and SWR meter
    #LIBS += -L"$$PWD/../libs/hamlib-w32-3.3/lib/gcc" -lhamlib
    #INCLUDEPATH += "$$PWD/../libs/hamlib-w32-3.3/include/"
}
else:
{
    TARGET = kmeter
}
