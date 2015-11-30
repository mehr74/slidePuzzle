#include <QtWidgets>
#include <QHBoxLayout>
#include <QLabel>
#include "mainwindow.h"
#include "puzzlewidget.h"
#include "newgame.h"

MainWindow::MainWindow()
{
    createActions();
    createMenus();
    createToolBars();
    createContextMenu();
    puzzleWidget = new PuzzleWidget(this);
    puzzleWidget->addPieces(QPixmap(QString::fromUtf8("/home/mehrshad/spongebob.jpg")));
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(puzzleWidget);
    QLabel *label = new QLabel();
//    label->setPixmap(QPixmap(QString::fromUtf8(":/images/images/background.jpg")));
    layout->addWidget(label);
    setLayout(layout);
    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
}

void MainWindow::createActions()
{
    newAction = new QAction(tr("&New game"), this);
    newAction->setIcon(QIcon(":/icons/images/new.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Start a new game"));
    connect(newAction, SIGNAL(triggered()),
            this, SLOT(newGame()));

    saveAction = new QAction(tr("&Save game"), this);
    saveAction->setIcon(QIcon(":/icons/images/save.png"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save current game"));
//    connect(saveAction, SIGNAL(triggered()),
//            this, SLOT(saveGame()));

    loadAction = new QAction(tr("&Load game"), this);
    loadAction->setIcon(QIcon(":/icons/images/load.png"));
    loadAction->setStatusTip(tr("Load a game"));
    loadAction->setShortcut(QKeySequence::Open);
//    connnect(loadAction, SIGNAL(triggered()),
//             this, SLOT(loadGame()));

    settingsAction = new QAction(tr("&Settings..."), this);
    settingsAction->setIcon(QIcon(":/icons/images/settings.png"));
    settingsAction->setStatusTip("Open settings window");
//    connect(settingsAction,( SIGNAL(triggered()),
//            this, SLOT( settings()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setIcon(QIcon(":/icons/images/exit.png"));
    exitAction->setStatusTip(tr("Close game"));
    connect(exitAction, SIGNAL(triggered()),
            this, SLOT(close()));

    fullScreenAction = new QAction(tr("Fullscreen"), this);
    fullScreenAction->setShortcut(QKeySequence::FullScreen);
    fullScreenAction->setCheckable(true);
    fullScreenAction->setStatusTip(tr("Change the screen mode to fullscreen"
                                      " or default view"));
    connect(fullScreenAction, SIGNAL(toggled(bool)),
            this, SLOT(changeFullScreenMode(bool)));

    fileToolBarAction = new QAction(tr("File Toolbar"), this);
    fileToolBarAction->setCheckable(true);
    fileToolBarAction->setStatusTip(tr("Show or hide file toolbar"));
    fileToolBarAction->setChecked(true);
    connect(fileToolBarAction, SIGNAL(toggled(bool)),
            this, SLOT(changeFileToolBarVisibility(bool)));

    controlToolBarAction = new QAction(tr("Control Toolbar"), this);
    controlToolBarAction->setCheckable(true);
    controlToolBarAction->setStatusTip(tr("Show or hide control toolbar"));
    controlToolBarAction->setChecked(true);
    connect(controlToolBarAction, SIGNAL(toggled(bool)),
            this, SLOT(changeControlToolBarVisibility(bool)));

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
    redoAction->setIcon(QIcon("/home/mehrshad/slidePuzzle/images/redo.png"));
    redoAction->setShortcut(QKeySequence::Redo);

    undoAction = new QAction(tr("Undo"), this);
    undoAction->setIcon(QIcon("/home/mehrshad/slidePuzzle/images/undo.png"));
    undoAction->setShortcut(QKeySequence::Undo);

    aboutAction = new QAction(tr("About"), this);
    aboutQtAction = new QAction(tr("About Qt"), this);
    aboutAction->setIcon(QIcon("/home/mehrshad/slidePuzzle/images/help.png"));

    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    aboutQtAction->setIcon(QIcon("/home/mehrshad/slidePuzzle/images/info.png"));
    connect(aboutQtAction, SIGNAL(triggered()), this, SLOT(aboutQt()));
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
    controlMenu->addAction(undoAction);
    controlMenu->addAction(redoAction);
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

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(saveAction);
    fileToolBar->addAction(loadAction);

    controlToolBar = addToolBar(tr("&Control"));

    controlToolBar->addAction(undoAction);
    controlToolBar->addAction(redoAction);
}

void MainWindow::createContextMenu()
{

}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::newGame()
{
    NewGame dialog(this);
    dialog.exec();
}

void MainWindow::changeFullScreenMode(bool screenMode)
{
    if(screenMode)
        this->showFullScreen();
    else
        this->showNormal();
}

void MainWindow::changeFileToolBarVisibility(bool fileToolBarMode)
{
    if(!fileToolBarMode)
        this->fileToolBar->hide();
    else
        this->fileToolBar->show();
}

void MainWindow::changeControlToolBarVisibility(bool controlToolBarMode)
{
    if(!controlToolBarMode)
        this->controlToolBar->hide();
    else
        this->controlToolBar->show();
}


void MainWindow::saveGame(){}

void MainWindow::setTimerVisible(){}
