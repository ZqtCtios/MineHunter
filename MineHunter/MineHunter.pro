#-------------------------------------------------
#
# Project created by QtCreator 2016-09-02T12:03:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MineHunter
TEMPLATE = app
RC_FILE+= ico.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    passwindow.cpp \
    aboutwindow.cpp \
    challengewindow.cpp \
    block.cpp \
    gameoverwindow.cpp

HEADERS  += mainwindow.h \
    passwindow.h \
    aboutwindow.h \
    challengewindow.h \
    block.h \
    gameoverwindow.h

FORMS    += mainwindow.ui \
    passwindow.ui \
    aboutwindow.ui \
    challengewindow.ui \
    gameoverwindow.ui

RESOURCES += \
    media.qrc

OTHER_FILES += \
    ico.rc
