#include <QtWidgets>
#include "newgame.h"

NewGame::NewGame(QWidget *parent)
    :QDialog(parent)
{
    setupUi(this);

    mediumRadio->setChecked(true);
    columnSpinBox->setRange(2, 99);
    columnSpinBox->setValue(4);
    rowSpinBox->setRange(2, 99);
    rowSpinBox->setValue(4);
    secondaryGroupBox->hide();
    tertiaryGroupBox->hide();
    fileNameLabel->hide();
    classicType->setChecked(true);

    fileName = QString(":/images/images/classic.png");

    connect(browseButton, SIGNAL(clicked()), this, SLOT(imageBrowse()));
    connect(columnSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setColumn(int)));

    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void NewGame::imageBrowse()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.jpg *.xpm)"));
    if(dialog.exec())
    {
        QStringList result = dialog.selectedFiles();
        fileName = result[0];
        fileNameLabel->setText(fileName);
        fileNameLabel->show();
    }
}
