#ifndef BACTERIE_H
#define BACTERIE_H

#include "position.h"

enum class Bacteria_Gender{male, female}; //for bacteries gender

class Bacterie
{
public:
    Bacterie();


//    methods to move bacteria
      void move();

//      getters
      int axis_x() const;
      int axis_y() const;
      int get_bacteria_id() const;
      Bacteria_Gender gender() const;

private:
      void create_bacteria_gender(); //to create bacteria gender

private:
      inline static int id = 0;

      int x, y; //for coords
      int bacteria_id = {id++};

      Bacteria_Gender bacteria_gender;
      Position positionGeneratator;
};

#endif // BACTERIE_H
