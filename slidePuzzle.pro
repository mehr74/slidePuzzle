TEMPLATE = app
TARGET = slidepuzzle

QT  += widgets

INCLUDEPATH += .
DEPENDPATH += .

SOURCES += main.cpp \
    mainwindow.cpp \
    puzzlewidget.cpp

HEADERS += \
    mainwindow.h \
    puzzlewidget.h

RESOURCES += \
    slidepuzzle.qrc
