#ifndef NEWGAME_H
#define NEWGAME_H

#include <QDialog>
#include "ui_newgame.h"

class NewGame : public QDialog, public Ui::NewGame
{
    Q_OBJECT
public:
    NewGame(QWidget *parent = 0);
};



#endif // NEWGAME_H
