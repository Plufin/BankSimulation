QT         += core gui
QT         +=network
QT         += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    nosto.cpp \
    tokenmanager.cpp \
    rfidreaderdll.cpp

HEADERS += \
    mainwindow.h \
    menu.h \
    nosto.h \
    tokenmanager.h \
    rfidreaderdll.h

FORMS += \
    mainwindow.ui \
    menu.ui \
    nosto.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
