#ifndef PUZZLEWIDGET_H
#define PUZZLEWIDGET_H
#include <QWidget>

class PuzzleWidget : public QWidget
{
    Q_OBJECT
public:
    PuzzleWidget(QWidget *parent = 0, const QSize = QSize(400, 400));

 //   QVariant data(const QModelIndex &, int = Qt::DisplayRole) const;
    void addPieces(const QPixmap &pixMap = QPixmap());

private:
    QList<QPixmap> piecePixmaps;
    QList<QRect> pieceRects;
    QList<QPoint> pieceLocations;
    QRect highlightedRect;
    int inPlace;
    QPoint pnt;
    QPoint relation;
    int gameType;
    int moves;
};

#endif // PUZZLEWIDGET_H
