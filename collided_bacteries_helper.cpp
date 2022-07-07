#include "collided_bacteries_helper.h"
#include <QDebug>

Collided_Bacteries_Helper::Collided_Bacteries_Helper
    (const QList<Bacterie> &m_bacteries, int st, int nd, QObject *parent)

    : QObject(parent),
      collided_bacteries(m_bacteries), //initialised collided bacteries
      start(st), //init ... start
      end(nd) //init ... end
{

}

void Collided_Bacteries_Helper::start_process()
{
    QVariantList collided_bacterie_coord_x;
    QVariantList collided_bacterie_coord_y;
    QVariantList ids_container;
    QVariantList bacteries_gender;

    for(int i = start; i < end; i++)
    //for(const Bacterie &bacterie: qAsConst(collided_bacteries))
    {
             collided_bacterie_coord_x.append(collided_bacteries.at(i).axis_x());
             collided_bacterie_coord_y.append(collided_bacteries.at(i).axis_y());

             //adding bacteries properties to properties container
             ids_container.append(collided_bacteries.at(i).get_bacteria_id()); //retrieving IDs
             Bacteria_Gender bacteria_gender = collided_bacteries.at(i).gender(); //retrieving gender

             if(bacteria_gender == Bacteria_Gender::male) bacteries_gender.append(1); //verifying gender

             else bacteries_gender.append(0);
    }

    emit process_done(collided_bacterie_coord_x, collided_bacterie_coord_y, bacteries_gender, ids_container);
//    emit done();
}
