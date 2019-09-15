#-------------------------------------------------
#
# Project created by QtCreator 2017-08-10T15:57:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTables2
TEMPLATE = app

# CONFIG+= Test

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS \
            APP_VERSION='\\"1.00\\"'

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    model/mtable.cpp \
    model/tabledata.cpp \
    model/tableinfo.cpp \
    io/iofileimpl.cpp \
    updatedialog.cpp \
    tmanagerwindow.cpp \
    report/bilanceprint.cpp \
    tablereportwindow.cpp \
    tools/utils.cpp \
    tools/helper.cpp \
    io/appsettings.cpp \
    datasearchwindow.cpp \
    expoimpo/old/impexp.cpp \
    csvexpoimpodlg.cpp \
    selectionwindow.cpp \
    expoimpo/impoexpojson.cpp \
    tools/tablesfilter.cpp

HEADERS += \
        mainwindow.h \
    expoimpo/csvexpoimpo.h \
    expoimpo/iexportimport.h \
    expoimpo/old/impexp.h \
    model/mtable.h \
    model/tabledata.h \
    model/tableinfo.h \
    io/iofileimpl.h \
    model/idatastream.h \
    io/iiofile.h \
    updatedialog.h \
    tmanagerwindow.h \
    report/bilanceprint.h \
    tablereportwindow.h \
    tools/utils.h \
    tools/helper.h \
    io/appsettings.h \
    datasearchwindow.h \
    csvexpoimpodlg.h \
    selectionwindow.h \
    expoimpo/impoexpojson.h \
    tools/tablesfilter.h

FORMS += \
        mainwindow.ui \
    updatedialog.ui \
    tmanagerwindow.ui \
    tablereportwindow.ui \
    datasearchwindow.ui \
    csvexpoimpodlg.ui \
    selectionwindow.ui

CONFIG += mobility
MOBILITY =

Test{
  message(Test build)
QT += testlib
TARGET = QTables2Test
SOURCES -= main.cpp

HEADERS += test/qtables2test.h \
    test/bilanceprinttest.h \
    test/oldimpoexpotest.h \
    test/impoexpojsontest.h


SOURCES += test/main.cpp \
            test/qtables2test.cpp \
    test/bilanceprinttest.cpp \
    test/oldimpoexpotest.cpp \
    test/impoexpojsontest.cpp


RESOURCES += \
    test/testfiles.qrc


} else {
 message(Normal build)
}

RESOURCES += \
    icons.qrc

DISTFILES += \
    Readme.md
