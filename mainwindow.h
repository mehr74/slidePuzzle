#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class PuzzleWidget;
class QTime;
class QPixmap;
class NewGame;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

private slots:
    void newGame();
    void saveGame();
    void setTimerVisible();
    void aboutQt();
    void changeFullScreenMode(bool screenMode);
    void changeFileToolBarVisibility(bool fileToolBarMode);
    void changeControlToolBarVisibility(bool controlToolBarMode);

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createContextMenu();
    void createDockWindows();

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
