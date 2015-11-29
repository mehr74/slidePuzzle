#include "puzzlewidget.h"

PuzzleWidget::PuzzleWidget(QWidget *parent, const QSize size)
    :QWidget(parent)
{
    setMinimumSize(size);
}

void PuzzleWidget::addPieces(const QPixmap &pixMap)
{
    QRect mRect;
    pieceLocations.clear();
    piecePixmaps.clear();
    pieceRects.clear();

    for(int y = 0; y < relation.y(); y++)
    {
        for(int x = 0; x < relation.x(); x++)
        {
            mRect = QRect(x*pixMap.width()/relation.x(),
                          y*pixMap.height()/relation.y(),
                          pixMap.width()/relation.x(),
                          pixMap.height()/relation.y());
            QPixmap pieceImage = pixMap.copy(mRect);
            pieceLocations.append(QPoint(x, y));
            piecePixmaps.append(pieceImage);
            pieceRects.append(mRect);

        }
    }
    update();

}
