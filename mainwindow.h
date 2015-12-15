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
class QGridLayout;
class QListWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

signals:
    void puzzleCompleted();
    void blockMoved();

private slots:
    void appendToLog(QString *string)const;
    void newGame(QString fileName, int rows = 3, int cols = 5, int difficulty = 3);
    void openNewGameDialog();
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

    NewGame *newGameDialog;

    QMenu *fileMenu;
    QMenu *controlMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
    QMenu *toolBarSubMenu;

    QToolBar *fileToolBar;
    QToolBar *controlToolBar;

    QGridLayout *grid;

    QLabel *counterLabel;
    QLabel *timerText;

    QTextEdit *statusLog;

    QTimer *puzzleTimer;

    QListWidget *listWidget;

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
