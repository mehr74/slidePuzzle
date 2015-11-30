TEMPLATE = app
TARGET = slidepuzzle

QT  += widgets

INCLUDEPATH += .
DEPENDPATH += .

SOURCES += main.cpp \
    mainwindow.cpp \
    puzzlewidget.cpp \
    newgame.cpp

HEADERS += \
    mainwindow.h \
    puzzlewidget.h \
    newgame.h

RESOURCES += \
    slidepuzzle.qrc

FORMS += \
    newgame.ui
