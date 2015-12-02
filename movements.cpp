#include <QList>
#include "movements.h"
#include <QMap>

Movements::Movements()
{

}

void Movements::addMove(const QRect &prev, const QRect &next)
{
    if(top < previousRects.size())
    {
        previousRects[top] = prev;
        nextRects[top] = next;
    }
    else
    {
        previousRects.append(prev);
        nextRects.append(next);
    }
    top++;
}

int Movements::popMove(QRect *prevRect, QRect *nextRect)
{
    if(top <= 0)
        return -1;
    top--;
    *prevRect = previousRects[top];
    *nextRect = nextRects[top];
    return 0;
}

int Movements::incSp(QRect *prevRect, QRect *nextRect)
{
    if(top < previousRects.size())
    {
        top++;
        *prevRect = previousRects[top];
        *nextRect = nextRects[top];
        return 0;
    }
    return -1;
}
