QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
QT += network #Для работы с сетью

QT += sql #для базы данных
TEMPLATE = app

SOURCES += \
    tst_testmed.cpp \
    database.cpp \
    functions.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    database.h \
    functions.h
