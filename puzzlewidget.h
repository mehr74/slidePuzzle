#ifndef PUZZLEWIDGET_H
#define PUZZLEWIDGET_H

#include <QList>
#include <QPoint>
#include <QPixmap>
#include <QWidget>
#include <QMouseEvent>

class MainWindow;
class Movements;

class PuzzleWidget : public QWidget
{
   Q_OBJECT
public:
   PuzzleWidget(QWidget * Parent = 0,
                const QPoint PiecesNumber = QPoint(3, 3),
                int difficulty= 0,
                const QSize WidgetSize = QSize(512, 384));
   void addPieces(const QPixmap&image = QPixmap());
   // TODO : use an enum to specify the game difficulty
   void scramble();
      void keyPressed(int key);

public slots:
      void undo(void);
      void redo(void);

signals:
   void puzzleCompleted();
   void blockMoved();
   void moveCounter(int moves);
   void gameStarted();

protected:
   void paintEvent(QPaintEvent *);
   void mousePressEvent(QMouseEvent *);

private:
   MainWindow *parent;
   int findPiece(const QRect &) const;
   QRect findFreePiece(void) const;
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
   Movements *history;
   bool isGameStarted;
   int diff;
   int moves;
};

#endif
