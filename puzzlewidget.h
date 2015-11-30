#ifndef PUZZLEWIDGET_H
#define PUZZLEWIDGET_H

#include <QList>
#include <QPoint>
#include <QPixmap>
#include <QWidget>
#include <QMouseEvent>

class PuzzleWidget : public QWidget
{
   Q_OBJECT
public:
   PuzzleWidget(QWidget * Parent = 0,
                const QSize WidgetSize = QSize(512, 384),
                const QPoint PiecesNumber = QPoint(3, 3));
   void addPieces(const QPixmap& = QPixmap());

protected:
   void paintEvent(QPaintEvent *);

private:
   int findPiece(const QRect &) const;
   QRect findPieceToMove(const QRect) const;
   const QRect targetSquare(const QPoint &) const;
   QList<QPixmap> piecePixmaps;
   QList<QRect> pieceRects;
   QList<QPoint> pieceLocations;
   QRect highlightedRect;
   int inPlace;
   QPoint pnt;
   QPoint relation;
   QSize *widgetSize;

   int moves;
};

#endif
