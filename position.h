#ifndef POSITION_H
#define POSITION_H

#define X_Start_Bound 165
#define Y_Start_Bound 15
#define W_Bound 860
#define H_Bound 570
#define Increase_Coord_X 100
#define Increase_Coord_Y 100

#include <random>
#include <QDateTime>

class Position
{
public:
    Position();
    void generatePosition();
    //getters
    int getX() const;
    int getY() const;

private:
    int x, y;
    //method will be called inside the class
    int generateX();
    int generateY();
};

#endif // POSITION_H
