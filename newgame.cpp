#include "newgame.h"

NewGame::NewGame(QWidget *parent)
    :QDialog(parent)
{
    setupUi(this);

    columnSpinBox->setRange(2, 99);
    rowSpinBox->setRange(2, 99);
    secondaryGroupBox->hide();
    tertiaryGroupBox->hide();
    layout()->setSizeConstraint(QLayout::SetFixedSize);

}
