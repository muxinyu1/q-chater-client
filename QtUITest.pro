QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatwindow.cpp \
    clickablelabel.cpp \
    friendcard.cpp \
    loginhint.cpp \
    loginwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    msgbubble.cpp \
    signup.cpp \
    utility.cpp \
    style.cpp \
    variable.cpp

HEADERS += \
    chatwindow.h \
    clickablelabel.h \
    friendcard.h \
    loginhint.h \
    loginwidget.h \
    mainwindow.h \
    msgbubble.h \
    signup.h \
    utility.h \
    style.h \
    variable.h

FORMS += \
    chatwindow.ui \
    loginhint.ui \
    mainwindow.ui \
    signup.ui \
    style.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
