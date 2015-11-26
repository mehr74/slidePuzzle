#include <QtWidgets>
#include "mainwindow.h"

MainWindow::MainWindow()
{
    createActions();
    createMenus();
}

void MainWindow::createActions()
{
    newAction = new QAction(tr("&New game"), this);
    newAction->setIcon(QIcon(":/images/new.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Start a new game"));
//    connect(newAction, SIGNAL(triggered()),
//            this, SLOT(newGame()));

    saveAction = new QAction(tr("&Save game"), this);
    saveAction->setIcon(QIcon(":/images/save.png"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save current game"));
//    connect(saveAction, SIGNAL(triggered()),
//            this, SLOT(saveGame()));

    loadAction = new QAction(tr("&Load game"), this);
    loadAction->setIcon(QIcon(":/images/load.png"));
    loadAction->setStatusTip(tr("Load a game"));
    loadAction->setShortcut(QKeySequence::Open);
//    connnect(loadAction, SIGNAL(triggered()),
//             this, SLOT(loadGame()));

    settingsAction = new QAction(tr("&Settings..."), this);
    settingsAction->setStatusTip("Open settings window");
//    connect(settingsAction,( SIGNAL(triggered()),
//            this, SLOT( settings()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setStatusTip(tr("Close game"));
    connect(exitAction, SIGNAL(triggered()),
            this, SLOT(close()));

    fullScreenAction = new QAction(tr("Fullscreen"), this);
    fullScreenAction->setShortcut(QKeySequence::FullScreen);
    fullScreenAction->setCheckable(true);

    fileToolBarAction = new QAction(tr("File Toolbar"), this);
    fileToolBarAction->setCheckable(true);

    controlToolBarAction = new QAction(tr("Control Toolbar"), this);
    controlToolBarAction->setCheckable(true);

    timerToolBarAction = new QAction(tr("Timer ToolBar"), this);
    timerToolBarAction->setCheckable(true);

    showLogAction = new QAction(tr("Show Log"),this);
    showLogAction->setCheckable(true);

    statusBarAction = new QAction(tr("Status bar"), this);
    statusBarAction->setCheckable(true);

    soundAction = new QAction(tr("Sound"), this);
    soundAction->setCheckable(true);

    timerAction = new QAction(tr("timer"), this);
    timerAction->setCheckable(true);

    musicAction = new QAction(tr("Music"), this);
    musicAction->setCheckable(true);

    redoAction = new QAction(tr("Redo"), this);
    undoAction = new QAction(tr("Undo"), this);
    aboutAction = new QAction(tr("About"), this);
    aboutQtAction = new QAction(tr("About Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
//    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(loadAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(settingsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    controlMenu = menuBar()->addMenu(tr("&Control"));
    controlMenu->addAction(redoAction);
    controlMenu->addAction(undoAction);
    controlMenu->addSeparator();
    controlMenu->addAction(soundAction);
    controlMenu->addAction(musicAction);
    controlMenu->addAction(timerAction);
    controlMenu->addAction(showLogAction);

    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(fullScreenAction);
    viewMenu->addAction(fileToolBarAction);
    viewMenu->addAction(controlToolBarAction);


    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

}
