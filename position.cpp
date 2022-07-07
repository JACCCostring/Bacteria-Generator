#include "position.h"

Position::Position()
{}

void Position::generatePosition()
{
    x = generateX();
    y = generateY();
}

int Position::getX() const
{
    return x;
}

int Position::getY() const
{
    return y;
}

int Position::generateX()
{
    int random = qrand() % W_Bound;

    if(random <= X_Start_Bound) {
        while(random < X_Start_Bound){
            random += Increase_Coord_X;
        }

        return random;
    }

    return random;
}

int Position::generateY()
{
    int random = qrand() % H_Bound;

    if(random <= Y_Start_Bound) {
        while(random < Y_Start_Bound){
            random += Increase_Coord_Y;
        }
        return random;
    }

    return random;
}
