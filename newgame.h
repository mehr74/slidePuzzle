#ifndef NEWGAME_H
#define NEWGAME_H

#include <QDialog>
#include "ui_newgame.h"

class NewGame : public QDialog, public Ui::NewGame
{
    Q_OBJECT
public:
    NewGame(QWidget *parent = 0);
    QString fileName;
    int difficulty;

signals:
    void newGame(QString);

private slots:
    void imageBrowse();
    void okClicked();
    void on_okButton_clicked();
};



#endif // NEWGAME_H
