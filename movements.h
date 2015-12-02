#ifndef MOVEMENTS_H
#define MOVEMENTS_H

#include <QList>
#include <QRect>
#include <QMap>

class Movements
{
public:
    Movements();
    void addMove(const QRect &prev, const QRect &next);
    int popMove(QRect *prevRect, QRect *nextRect);
    int incSp(QRect *prevRect, QRect *nextRect);
private:
    QList<QRect> previousRects;
    QList<QRect> nextRects;
    int top = 0;
};


#endif // MOVEMENTSCONTAINER_H
