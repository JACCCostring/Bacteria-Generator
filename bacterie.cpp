#include "bacterie.h"

Bacterie::Bacterie()
{
    //when instanciating bacteria then create gender as well

    //creating gender randomly
    create_bacteria_gender();
}

void Bacterie::move()
{
    positionGeneratator.generatePosition(); //start generatating

    x = positionGeneratator.getX(); //retrieving x and y coords
    y = positionGeneratator.getY();
}

int Bacterie::axis_x() const
{
    return x;
}

int Bacterie::axis_y() const
{
    return y;
}

int Bacterie::get_bacteria_id() const
{
    return bacteria_id;
}

Bacteria_Gender Bacterie::gender() const
{
    return bacteria_gender;
}

void Bacterie::create_bacteria_gender()
{
    int gender_male = 2, gender_female = 0;

    int random = qrand()  % gender_male + gender_female; //generates bt male and female gender

    if(random == gender_male - 1) bacteria_gender = Bacteria_Gender::male;

    else bacteria_gender = Bacteria_Gender::female;
}
