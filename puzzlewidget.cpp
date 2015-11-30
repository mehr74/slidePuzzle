#include <QPainter>
#include <QVector>
#include <QMimeData>
#include <QDrag>
#include "puzzlewidget.h"

PuzzleWidget::PuzzleWidget(QWidget *parent, const QSize size, const QPoint pieceNum)
    : QWidget(parent)
{
    setAcceptDrops(true);
    pnt.setX(size.width()/4);
    pnt.setY(size.height()/4);
    this->relation = pieceNum;
    widgetSize = new QSize(size.width(), size.height());
    setMinimumSize(size);
    setMaximumSize(size);
    moves = 0;
}

void PuzzleWidget::addPieces(const QPixmap& pixmap)
{
    // scaledPixMap and mRect are temporarily used for scaling image and
    // tokenizing it into parts
    QRect mRect;
    QPixmap *scaledPixMap = new QPixmap(pixmap.scaled(*widgetSize));
    pieceLocations.clear();
    piecePixmaps.clear();
    pieceRects.clear();
    for (int y = 0; y < relation.y(); ++y) {
        for (int x = 0; x < relation.x(); ++x) {
                mRect = QRect(x*scaledPixMap->width()/relation.x(),
                              y*scaledPixMap->height()/relation.y(),
                              scaledPixMap->width()/relation.x(),
                              scaledPixMap->height()/relation.y());
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
        if(i != 0)
        painter.drawPixmap(pieceRects[i], piecePixmaps[i]);
    }

    painter.end();
}
