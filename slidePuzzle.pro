TEMPLATE = app
TARGET = slidepuzzle

QT  += widgets

INCLUDEPATH += .
DEPENDPATH += .

SOURCES += main.cpp \
    mainwindow.cpp \
    puzzlewidget.cpp \
    newgame.cpp \
    savegame.cpp \
    loadgame.cpp

HEADERS += \
    mainwindow.h \
    puzzlewidget.h \
    newgame.h \
    savegame.h \
    loadgame.h

RESOURCES += \
    slidepuzzle.qrc

FORMS += \
    newgame.ui
