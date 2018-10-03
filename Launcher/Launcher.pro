#-------------------------------------------------
#
# Project created by QtCreator 2017-10-02T01:33:43
#
#-------------------------------------------------

VERSION = 1.0.0.0
QMAKE_TARGET_COMPANY = Tian Long Ba Bu
QMAKE_TARGET_PRODUCT = Launch
QMAKE_TARGET_DESCRIPTION = Launcher for game TLBB
QMAKE_TARGET_COPYRIGHT = Tian Long Ba Bu

QT += core gui
QT += network
QT -= app_bundle
win32: QT += axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Launch
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += static
CONFIG += c++11

INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtZlib
INCLUDEPATH += $$PWD/../Dependencies/quazip
DEPENDPATH += $$PWD/../Dependencies/quazip
INCLUDEPATH += $$PWD/../Dependencies/ee/include
DEPENDPATH += $$PWD/../Dependencies/ee/include

# Variables
EE_DIR = $$PWD/../Dependencies/ee

static {
	DEFINES += QUAZIP_STATIC
}

win32:!win32-g++:QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
win32:!win32-g++:LIBS += -L$$EE_DIR/msvc/lib
CONFIG(debug, debug|release) {
  win32:!win32-g++:LIBS += -lquazipd
}
else
{
  win32:!win32-g++:LIBS += -lquazip
  win32 {
# QMAKE#_POST_LINK += mt -nologo -manifest $$PWD/manifest.xml -outputresource:$$OUT_PWD/release/$${TARGET}.exe $$escape_expand(\n\t)
  }
}
win32:RC_ICONS += $$EE_DIR/resources/icons/app_icon.ico

# Build Dir
#DESTDIR = $$OUT_PWD/bin/Launch
#OBJECTS_DIR = .obj
#MOC_DIR = .moc
#RCC_DIR = .rcc
#UI_DIR = .ui

# After built
DATA_TO_COPY = $$PWD/data
copydata.commands += $(COPY_DIR) $$shell_path($$DATA_TO_COPY) $$shell_path($$DESTDIR/..)
win32:win32-g++:BIN_TO_COPY = $$EE_DIR/bin
copybin.commands += $(COPY_DIR) $$shell_path($$BIN_TO_COPY) $$shell_path($$DESTDIR)
first.depends = $(first) copydata copybin
#export(first.depends)
#export(copydata.commands)
#export(copybin.commands)
#QMAKE_EXTRA_TARGETS += first copydata copybin

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    InitCopyApp.cpp \
    PlayGamePushButton.cpp \
    Config.cpp \
    QuitAppPushButton.cpp \
    MinimizeAppPushButton.cpp \
    ../Dependencies/ee/src/UtilsEE.cpp \
    ../Dependencies/ee/src/DownloadLaunchExtends.cpp \
    FileDownloader.cpp \
    PatchInfo.cpp \
    Utils.cpp

HEADERS += \
    MainWindow.hpp \
    InitCopyApp.hpp \
    PlayGamePushButton.hpp \
    Config.hpp \
    QuitAppPushButton.hpp \
    MinimizeAppPushButton.hpp \
    PatchInfo.hpp \
    ../Dependencies/ee/include/UtilsEE.hpp \
    ../Dependencies/ee/include/DownloadLaunchExtends.hpp \
    FileDownloader.hpp \
    Utils.hpp

FORMS += \
    MainWindow.ui

DISTFILES += \
    data/Launch.ini \
    data/Patch/PatchInfo.json \
    data/(version)

RESOURCES += \
    $$EE_DIR/resources/resources.qrc
