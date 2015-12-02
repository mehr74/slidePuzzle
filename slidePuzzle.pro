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
    loadgame.cpp \
    movements.cpp

HEADERS += \
    mainwindow.h \
    puzzlewidget.h \
    newgame.h \
    savegame.h \
    loadgame.h \
    movements.h

RESOURCES += \
    slidepuzzle.qrc

FORMS += \
    newgame.ui
