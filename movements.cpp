#include <QList>
#include "movements.h"
#include <QMap>

Movements::Movements()
{

}

void Movements::addMove(const QRect &prev, const QRect &next)
{
    previousRects.append(prev);
    nextRects.append(next);
}

void Movements::popMove(QRect *prevRect, QRect *nextRect)
{

    *prevRect = previousRects.back();
    *nextRect = nextRects.back();
}
