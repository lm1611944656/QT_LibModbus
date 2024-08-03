QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# 包含子模块
include($$PWD/3rd_libmodbus/3rd_libmodbus.pri)

CONFIG += c++17

LIBS += -L$$PWD -lws2_32

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

INCLUDEPATH += $$PWD/3rd_libmodbus

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
