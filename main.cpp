#include <QApplication>
#include <qsound.h>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow *win = new MainWindow();
/*    QSound sound(":/sounds/sounds/background.wav");
    sound.play(); */
    win->show();
    return app.exec();
}
