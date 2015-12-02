#include <QPainter>
#include <QVector>
#include <QMimeData>
#include <QDrag>
#include "puzzlewidget.h"
#include "movements.h"

PuzzleWidget::PuzzleWidget(QWidget *parent, const QSize size, const QPoint pieceNum)
    : QWidget(parent)
{
    setAcceptDrops(true);
    this->relation = pieceNum;
    pnt.setX(size.width()/relation.x());
    pnt.setY(size.height()/relation.y());
    widgetSize = new QSize(size.width(), size.height());
    setMinimumSize(size);
    setMaximumSize(size);
    history = new Movements;
    moves = 0;
}

void PuzzleWidget::addPieces(const QPixmap& pixmap)
{
    // scaledPixMap and mRect are temporarily used for scaling image and
    // tokenizing it into parts
    QRect mRect;
    QPixmap *scaledPixMap = new QPixmap(pixmap.scaled(*widgetSize));
    setAcceptDrops(true);
    pieceLocations.clear();
    piecePixmaps.clear();
    pieceRects.clear();
    for (int y = 0; y < relation.y(); ++y) {
        for (int x = 0; x < relation.x(); ++x) {
                mRect = QRect(pnt.x()*x,
                              pnt.y()*y,
                              pnt.x(),
                              pnt.y());
                QPixmap pieceImage = scaledPixMap->copy(mRect);
                pieceLocations.append(QPoint(x, y));
                piecePixmaps.append(pieceImage);
                pieceRects.append(mRect);
        }
    }
    update();
}


void PuzzleWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);

    painter.fillRect(event->rect(), Qt::white);

    if (highlightedRect.isValid())
    {
        painter.setBrush(QColor("#ffcccc"));
        painter.setPen(Qt::NoPen);
        painter.drawRect(highlightedRect.adjusted(0, 0, -1, -1));
    }

    for (int i = 0; i < pieceRects.size(); ++i)
    {
        painter.drawPixmap(pieceRects[i], piecePixmaps[i]);
    }

    painter.end();
}

void PuzzleWidget::scramble(int diff)
{
    qsrand(QCursor::pos().x() ^ QCursor::pos().y());
    moves = 0;
    int maxid = relation.x()*relation.y() - 1;
    QRect buf;
    int freeRect = qrand()%maxid;
    int i = (int)diff * diff * diff* 10 + qrand() % 10 + 5;
    while (i)
    {
        switch(int(qrand()%4))
        {
            case 0:
                // freeRect is not at the first row
                if (freeRect-relation.x() >= 0) {
                    // swap freeRect with the top rectangle
                    buf = pieceRects[freeRect];
                    pieceRects[freeRect] = pieceRects[freeRect-relation.x()];
                    pieceRects[freeRect-relation.x()] = buf;
                    freeRect = freeRect-relation.x();
                    i--;
                    break;
                }
            case 1:
                // freeRect is not at the last column
                if ((freeRect%relation.x()) != (relation.x()-1)) {
                    // swap freeRect with the right rectangle
                    buf = pieceRects[freeRect];
                    pieceRects[freeRect] = pieceRects[freeRect+1];
                    pieceRects[freeRect+1] = buf;
                    freeRect = freeRect+1;
                    i--;
                    break;
                }
            case 2:
                // freeRect is not at the last row
                if (freeRect+relation.x() <= maxid) {
                    // swap freerect with the button rectangle
                    buf = pieceRects[freeRect];
                    pieceRects[freeRect] = pieceRects[freeRect+relation.x()];
                    pieceRects[freeRect+relation.x()] = buf;
                    freeRect = freeRect+relation.x();
                    i--;
                    break;
                }
            default:
                // freeRect is not at the first column
                if ((freeRect%relation.x()) != 0) {
                    // swap freeRect with the left rectangle
                    buf = pieceRects[freeRect];
                    pieceRects[freeRect] = pieceRects[freeRect-1];
                    pieceRects[freeRect-1] = buf;
                    freeRect = freeRect-1;
                    i--;
                }
        }
    }

    // Remove the freeRect from lists...
    pieceLocations.removeAt(freeRect);
    piecePixmaps.removeAt(freeRect);
    pieceRects.removeAt(freeRect);
    inPlace = 0;
    for (int k = 0; k < pieceRects.size(); ++k) {
        if (pieceLocations[k] == QPoint(pieceRects[k].x()/pnt.x(), pieceRects[k].y()/pnt.y()))
            inPlace++;
    }
    update();
}

void PuzzleWidget::mousePressEvent(QMouseEvent *event)
{
    QRect square = targetSquare(event->pos());
    int found = findPiece(square);

    if (found == -1)
        return;

    QPoint location = pieceLocations[found];
    pieceRects.removeAt(found);

    // If the user change the position of a right piece ...
    if (location == QPoint(square.x()/pnt.x(), square.y()/pnt.y()))
        inPlace--;

    QRect newpos = findPieceToMove(square);
    if (newpos == square) {
        emit blockMoved();
    }

    history->addMove(square, newpos);
    pieceRects.insert(found, newpos);

    if (inPlace == (relation.x()*relation.y() - 1))
        emit puzzleCompleted();

    update();
}

int PuzzleWidget::findPiece(const QRect &pieceRect) const
{
    for (int i = 0; i < pieceRects.size(); ++i)
    {
        if (pieceRect == pieceRects[i])
        {
            return i;
        }
    }
    return -1;
}

const QRect PuzzleWidget::targetSquare(const QPoint &position) const
{
    return QRect((position.x()/pnt.x()) * pnt.x(), (position.y()/pnt.y()) * pnt.y(), pnt.x(), pnt.y());
}

void PuzzleWidget::keyPressed(int keyPressed)
{
    QRect freePiece = findFreePiece();
    QRect *movingPiece;
    int movingId;

    if(keyPressed == Qt::Key_D)
    {
        if(freePiece.x() > 0)
        {
            movingPiece = new QRect(freePiece.x()-pnt.x(), freePiece.y(), pnt.x(), pnt.y());
        }
        else
        {
            emit blockMoved();
            return;
        }
    }
    else if(keyPressed == Qt::Key_A)
    {
        if(freePiece.x() < pnt.x()*(relation.x()-1))
        {
            movingPiece = new QRect(freePiece.x()+pnt.x(), freePiece.y(), pnt.x(), pnt.y());
        }
        else
        {
            emit blockMoved();
            return;
        }
    }
    else if(keyPressed == Qt::Key_S)
    {
        if(freePiece.y() > 0)
        {
            movingPiece = new QRect(freePiece.x(), freePiece.y()-pnt.y(), pnt.x(), pnt.y());
        }
        else
        {
            emit blockMoved();
            return;
        }
    }
    else if(keyPressed == Qt::Key_W)
    {
        if(freePiece.y() < pnt.y()*(relation.y()-1))
        {
            movingPiece = new QRect(freePiece.x(), freePiece.y()+pnt.y(), pnt.x(), pnt.y());
        }
        else
        {
            emit blockMoved();
            return;
        }
    }
    else
    {
        return;
    }

    history->addMove(*movingPiece, freePiece);
    movingId = findPiece(*movingPiece);
    pieceRects.removeAt(movingId);
    pieceRects.insert(movingId, freePiece);

    update();
}

QRect PuzzleWidget::findFreePiece() const
{
    QRect buf(0, 0, pnt.x(), pnt.y());
    for(int i = 0; i < relation.x(); i++)
    {
        for(int j = 0; j < relation.y(); j++)
        {
            if(findPiece(buf) == -1)
                return buf;
            buf.moveTo(buf.x(), buf.y()+pnt.y());
        }
        buf.moveTo(buf.x()+pnt.x(), 0);
    }
}

QRect PuzzleWidget::findPieceToMove(const QRect found) const
{
    QRect oldPos = found;
    oldPos.moveTo(oldPos.x()+pnt.x(),oldPos.y());
    if (findPiece(oldPos) == -1 && (oldPos.x() < pnt.x()*relation.x()))
        return oldPos;
    oldPos.moveTo(oldPos.x()-2*pnt.x(),oldPos.y());
    if (findPiece(oldPos) == -1 && (oldPos.x() >= 0))
        return oldPos;
    oldPos.moveTo(oldPos.x()+pnt.x(),oldPos.y()+pnt.y());
    if (findPiece(oldPos) == -1 && (oldPos.y() < pnt.y()*relation.y()))
        return oldPos;
    oldPos.moveTo(oldPos.x(),oldPos.y()-2*pnt.y());
    if (findPiece(oldPos) == -1 && (oldPos.y() >= 0))
        return oldPos;
    return found;
}

void PuzzleWidget::undo(void)
{
    QRect moveRect;
    QRect targetRect;
    history->popMove(&moveRect, &targetRect);
    pieceRects.removeAt(findPiece(targetRect));
    pieceRects.insert(findPiece(targetRect), moveRect);
    update();
}
