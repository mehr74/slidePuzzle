TEMPLATE = app
TARGET = slidepuzzle

QT  += widgets \


INCLUDEPATH += .
DEPENDPATH += .

SOURCES += main.cpp \
    mainwindow.cpp \
    puzzlewidget.cpp \
    newgame.cpp \
    loadgame.cpp \
    movements.cpp \
    audio.cpp

HEADERS += \
    mainwindow.h \
    puzzlewidget.h \
    newgame.h \
    loadgame.h \
    movements.h \
    audio.h

RESOURCES += \
    slidepuzzle.qrc

FORMS += \
    newgame.ui
