QT       += core gui sql multimedia widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    databasemanager.cpp \
    #gamelogic.cpp \
    #gamewindow.cpp \
    #genrewindow.cpp \
    inputhandler.cpp \
    levelwindow.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    #music.cpp \
    #musicfactory.cpp \
    #note.cpp \
    #scoremanager.cpp \
    #song.cpp \
    #songfactory.cpp \
    #modeltest.cpp \
    user.cpp \
    userfactory.cpp

HEADERS += \
    databasemanager.h \
    #gamelogic.h \
    #gamewindow.h \
    #genrewindow.h \
    inputhandler.h \
    levelwindow.h \
    loginwindow.h \
    mainwindow.h \
    #music.h \
    #musicfactory.h \
    #note.h \
    #scoremanager.h \
    #song.h \
    #songfactory.h \
    #modeltest.h \
    user.h \
    userfactory.h

# Default rules for deployment.
# qnx: target.path = /tmp/$${TARGET}/bin
# else: unix:!android: target.path = /opt/$${TARGET}/bin
# !isEmpty(target.path): INSTALLS += target

# # SFML (Alli)
INCLUDEPATH += /usr/local/opt/sfml/include
LIBS += -L/usr/local/opt/sfml/lib
LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio



# # INCLUDEPATH += /opt/homebrew/opt/sfml/include
# # LIBS += -L/opt/homebrew/opt/sfml/lib
# # LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio


# # QT version 6.8.2 (Alli)
QTDIR = /usr/local/Cellar/qt/6.8.2
LIBS += -L$$QTDIR/lib -framework QtCore -framework QtSql -framework QtGui -framework QtWidgets

# QTDIR = /opt/homebrew/opt/qt
# INCLUDEPATH += $$QTDIR/include
# LIBS += -L$$QTDIR/lib -framework QtCore -framework QtSql -framework QtGui -framework QtWidgets
# # Add SFML library paths
# LIBS += -L/path/to/sfml/lib -lsfml-audio -lsfml-system

# # Julie's pathway
# INCLUDEPATH += /usr/local/Cellar/sfml/3.0.0_1/include
# LIBS += -L/usr/local/Cellar/sfml/3.0.0_1/lib
# LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# # Qt version 6.8.2 installed via Homebrew
# QTDIR = /usr/local/Cellar/qt/6.8.2
# INCLUDEPATH += $$QTDIR/include
# LIBS += -L$$QTDIR/lib -framework QtCore -framework QtSql -framework QtGui -framework QtWidgets
# end


RESOURCES += \
    resources.qrc




