#include <QtWidgets>
#include <QHBoxLayout>
#include <QLabel>
#include <QDockWidget>
#include <QTextEdit>
#include <QSpacerItem>
#include <QVBoxLayout>
#include "mainwindow.h"
#include "puzzlewidget.h"
#include "newgame.h"

#define TIME_FORMAT "hh:mm:ss"

MainWindow::MainWindow()
{
    puzzleWidget = new PuzzleWidget(this);
    puzzleWidget->addPieces(QPixmap(QString::fromUtf8("/home/mehrshad/spongebob.jpg")));

    createActions();
    createMenus();
    createToolBars();
    createContextMenu();
    createDockWindows();
    createLog();
    createStatusBar();
    puzzleTimer = new QTimer(this);
    connect(puzzleTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
    connect(puzzleWidget, SIGNAL(gameStarted()), this, SLOT(timerOn()));
    setTimer(true);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(puzzleWidget);
    layout->addWidget(statusLog);
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
    connect(undoAction, SIGNAL(triggered()),
            puzzleWidget, SLOT(undo()));

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

void MainWindow::createDockWindows()
{
    timerDock = new QDockWidget(tr("Timer"), this);
    QLabel *timerImg = new QLabel();
    timerImg->setPixmap(QPixmap(QString::fromUtf8(":/icons/images/timer.png")));
    timerText = new QLabel("<h2>00:00:00</h2>");
    QHBoxLayout *timerLayout = new QHBoxLayout();
    timerLayout->addWidget(timerImg);
    timerLayout->addWidget(timerText);
    QWidget *timerWidget = new QWidget();
    timerWidget->setLayout(timerLayout);
    timerDock->setWidget(timerWidget);
    timerDock->setFixedSize(240, 200);
    timerDock->setTitleBarWidget(new QLabel("<h2>Timer</h2>"));
    addDockWidget(Qt::RightDockWidgetArea, timerDock);

    moveDock = new QDockWidget(tr("Move"), this);
    moveDock->setAllowedAreas(Qt::LeftDockWidgetArea);
    QLabel *moveImg = new QLabel();
    moveImg->setPixmap(QPixmap(QString::fromUtf8(":/icons/images/move.png")));
    counterLabel = new QLabel("<h2>000</h2>");
    connect(puzzleWidget, SIGNAL(moveCounter(int)),
            this, SLOT(changeCounterText(int)));
    QHBoxLayout *moveLayout = new QHBoxLayout();
    moveLayout->addWidget(moveImg);
    moveLayout->addWidget(counterLabel);
    QWidget *moveWidget = new QWidget();
    moveWidget->setLayout(moveLayout);
    moveDock->setWidget(moveWidget);
    moveDock->setTitleBarWidget(new QLabel("<h2>Move</h2>"));
    // TODO : change font of timer and move to nice one
    moveDock->setFixedSize(240,200);
    addDockWidget(Qt::RightDockWidgetArea, moveDock);
}

void MainWindow::createLog()
{
    statusLog = new QTextEdit();
    statusLog->setReadOnly(true);
    statusLog->setMaximumHeight(100);
    statusLog->setFrameStyle(3);
    statusLog->append(tr("<h4>Welcome</h4>"));
}

void MainWindow::createStatusBar()
{
    statusBar()->addWidget(new QLabel("StatusBar"));
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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    puzzleWidget->keyPressed(event->key());
}

void MainWindow::saveGame()
{}

void MainWindow::setTimerVisible(){}

void MainWindow::appendToLog(QString *string) const
{
    statusLog->append(*string);
}

void MainWindow::changeCounterText(int counter)
{
    QString str = QString("%1").arg(counter, 3, 10, QChar('0'));
    str.append("</h2>");
    str.insert(0, QString("<h2>"));
    counterLabel->setText(str);
}

void MainWindow::timerOn()
{
    timerAction->setChecked(true);
    timerText->setEnabled(true);
    puzzleTimer->start(1000);
}
void MainWindow::timerOff()
{
    timerAction->setChecked(false);
    timerText->setEnabled(false);
    setTimer(true);
}

void MainWindow::timerReset()
{
    setTimer(true);
}
void MainWindow::updateTime()
{
    QTime curTime = QTime::fromString(timerText->text(), TIME_FORMAT).addSecs(1);
    setTimer(false, curTime);
}

void MainWindow::setTimer(const bool reset, const QTime time)
{
    static QString timeStr;
    if (reset)
    {
        timerText->setText(trUtf8("00:00:00"));
    }
    else
    {
        timerText->setText(time.toString(TIME_FORMAT));
    }
}

