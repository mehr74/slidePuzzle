#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
class PuzzleWidget;
class QAction;
class QPixmap;
class NewGame;
class QTextEdit;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    void appendToLog(QString *string)const;
signals:
    void puzzleCompleted();
    void blockMoved();

private slots:
    void newGame();
    void saveGame();
    void setTimerVisible();
    void aboutQt();
    void changeFullScreenMode(bool screenMode);
    void changeFileToolBarVisibility(bool fileToolBarMode);
    void changeControlToolBarVisibility(bool controlToolBarMode);
    void changeCounterText(int counter);
    void timerOn();
    void timerOff();
    void timerReset();
    void updateTime();

protected:
   void keyPressEvent(QKeyEvent *event);

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createContextMenu();
    void createDockWindows();
    void createLog();
    void createStatusBar();
    void setTimer(const bool, const QTime = QTime());

    PuzzleWidget *puzzleWidget;

    QMenu *fileMenu;
    QMenu *controlMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
    QMenu *toolBarSubMenu;

    QToolBar *fileToolBar;
    QToolBar *controlToolBar;

    QDockWidget *timerDock;
    QDockWidget *moveDock;

    QLabel *counterLabel;
    QLabel *timerText;

    QTextEdit *statusLog;

    QTimer *puzzleTimer;

    QAction *newAction;
    QAction *saveAction;
    QAction *loadAction;
    QAction *settingsAction;
    QAction *exitAction;
    QAction *fullScreenAction;
    QAction *controlToolBarAction;
    QAction *fileToolBarAction;
    QAction *timerToolBarAction;
    QAction *statusBarAction;
    QAction *soundAction;
    QAction *musicAction;
    QAction *timerAction;
    QAction *showLogAction;
    QAction *redoAction;
    QAction *undoAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
};




#endif // MAINWINDOW_H
