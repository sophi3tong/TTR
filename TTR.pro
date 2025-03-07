QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gamelogic.cpp \
    gamewindow.cpp \
    genrewindow.cpp \
    inputhandler.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    music.cpp \
    note.cpp \
    scoremanager.cpp \
    song.cpp \
    user.cpp

HEADERS += \
    gamelogic.h \
    gamewindow.h \
    genrewindow.h \
    inputhandler.h \
    loginwindow.h \
    mainwindow.h \
    music.h \
    note.h \
    scoremanager.h \
    song.h \
    user.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
