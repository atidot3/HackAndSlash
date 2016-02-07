#-------------------------------------------------
#
# Project created by QtCreator 2016-02-04T18:29:07
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkit webkitwidgets uitools xml

TARGET = Launcher
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Config/config.cpp \
    QDownloader/QDownloader.cpp

HEADERS  += mainwindow.h \
    Config/config.h \
    QDownloader/QDownloader.h

FORMS    += mainwindow.ui

RESOURCES += \
    myres.qrc
