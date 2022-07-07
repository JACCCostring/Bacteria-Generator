#include "bacteriahandler.h"
#include "collided_bacteries_helper.h"

#include <QThread>

BacteriaHandler::BacteriaHandler(QObject *parent) : QObject(parent)
{
    timer_refresh_persecond = 10 * 100; //assigned default value

    trigger_movment.setInterval(timer_refresh_persecond); //setting timer by 1 * 1000 milliseconds
    //connecting timer signals
    connect(&trigger_movment, &QTimer::timeout, this, &BacteriaHandler::onTrigger_Movment);
}

void BacteriaHandler::generate_bacteries(const QVariant ctt)
{
    QVariantList bacteries_gender; //for bacteries gender

        for(int i = 0; i < ctt.toInt(); i++){
            //create bacteries
            Bacterie new_bacterie;

            //adding new bacterie to container
            m_bacteries.append(new_bacterie);

            //adding bacteries properties to properties container
            Bacteria_Gender bacteria_gender = new_bacterie.gender(); //retrieving gender

            if(bacteria_gender == Bacteria_Gender::male) bacteries_gender.append(1); //verifying gender

            else bacteries_gender.append(0);
            }

        setBacteria_properties(bacteries_gender); //setting properties of the bacteries
}

void BacteriaHandler::move_bacteries()
{
    if(m_bacteries.length() > 0) //only start movment if bacteries exist
        trigger_movment.start();
}

void BacteriaHandler::stop_movment()
{
    if(trigger_movment.isActive()) //obly if trigger movment timer is already started
        trigger_movment.stop();
}

const QVariantList &BacteriaHandler::bacteria_container() const
{
    return m_bacteria_container;
}

void BacteriaHandler::setBacteria_container(const QVariantList &newBacteria_container)
{
    if (m_bacteria_container == newBacteria_container)
        return;

    m_bacteria_container = newBacteria_container;

    emit bacteria_containerChanged();
}

bool BacteriaHandler::analyze_bacteries_movment(Bacterie &bacterie)
{
    for(const QVariant &coordX: qAsConst(m_bacteria_container))
    {
        for(const QVariant &coordY: qAsConst(m_bacteria_container_y))
        {
            if(bacterie.axis_x() == coordX && bacterie.axis_y() == coordY)
                return true; // if same coords found that means bacteries had contact each other
           }
     }

    return false;
}

void BacteriaHandler::onTrigger_Movment()
{
    QVariantList coords_container; //for saving bacteries coords when moving
    QVariantList coords_container_y; //for saving bacteries coords when moving

    for( Bacterie &bacterie: m_bacteries){
            bacterie.move(); //moving bacteries

            if(coords_container.length() && coords_container_y.length() > 0){
                //analyze if bacteries coords repeat
               //if repeat then bacteries will reproduce themself
                if(analyze_bacteries_movment(bacterie)){
                       collided_bacteries.append(bacterie); //collecting collided bacteries
                       emit new_bacteria_generated(); //emiting signal when new bacteri generated
                }
            }

            coords_container.append(bacterie.axis_x()); //appeding x, y coords from bacteries
            coords_container_y.append(bacterie.axis_y()); //appeding x, y coords from bacteries
}

    setBacteria_container(coords_container); //setting appended coords
    setBacteria_container_y(coords_container_y);
}

void BacteriaHandler::onCollider_helper_done(const QVariantList &x, const QVariantList &y,
                                                         const QVariantList &gender, const QVariantList &ids)
{
        setCollided_bacteries_x(x); //setting coords x, y, gender and IDs
        setCollided_bacteries_y(y);
        setCollided_bacterie_props(gender);
        setContainer_bacteries_ids(ids);
}

const QVariantList &BacteriaHandler::bacteria_properties() const
{
    return m_bacteria_properties;
}

void BacteriaHandler::setBacteria_properties(const QVariantList &newBacteria_properties)
{
    if (m_bacteria_properties == newBacteria_properties)
        return;

    m_bacteria_properties = newBacteria_properties;

    emit bacteria_propertiesChanged();
}

const QVariantList &BacteriaHandler::bacteria_container_y() const
{
    return m_bacteria_container_y;
}

void BacteriaHandler::setBacteria_container_y(const QVariantList &newBacteria_container_y)
{
    if (m_bacteria_container_y == newBacteria_container_y)
        return;

    m_bacteria_container_y = newBacteria_container_y;

    emit bacteria_container_yChanged();
}

void BacteriaHandler::set_to_time_refresh(QVariant value_refresh)
{
    if(value_refresh.toInt() <= 10) //if value to refresh less then 10 then assign value * 100
    {
        timer_refresh_persecond = value_refresh.toInt() * 100;
        trigger_movment.setInterval(timer_refresh_persecond); //setting new time refresh

        return;
    }

    timer_refresh_persecond = 10 * 100; //if not then assign default value
    trigger_movment.setInterval(timer_refresh_persecond);
}

void BacteriaHandler::supervise_collided_bacteries(QVariant start, QVariant end)
{

       QThread *thread_helper = new QThread;

       Collided_Bacteries_Helper *collider_helper = //collided helper initialised with collided bacteries
               new Collided_Bacteries_Helper(collided_bacteries, start.toInt(), end.toInt());

       connect(thread_helper, &QThread::started, collider_helper, //connecting to execute process_done when thread started
               &Collided_Bacteries_Helper::start_process);

       connect(collider_helper, &Collided_Bacteries_Helper::process_done, //connecting to work with data from helper when helper is done
               this, &BacteriaHandler::onCollider_helper_done);

       connect(collider_helper, &Collided_Bacteries_Helper::process_done, //connecting to delete itself when helper is finished
               collider_helper, &Collided_Bacteries_Helper::deleteLater);

       connect(thread_helper, &QThread::finished, //connecting to delete itself when thread finished
               thread_helper, &QThread::deleteLater);

      collider_helper->moveToThread(thread_helper); //moving to thread

      thread_helper->start(); //starting thread
}

int BacteriaHandler::collided_bacteries_length()
{
    return collided_bacteries.length();
}

const QVariantList &BacteriaHandler::collided_bacteries_x() const
{
    return m_collided_bacteries_x;
}

void BacteriaHandler::setCollided_bacteries_x(const QVariantList &newCollided_bacteries_x)
{
    if (m_collided_bacteries_x == newCollided_bacteries_x)
        return;

    m_collided_bacteries_x = newCollided_bacteries_x;

    emit collided_bacteries_xChanged();
}

const QVariantList &BacteriaHandler::collided_bacteries_y() const
{
    return m_collided_bacteries_y;
}

void BacteriaHandler::setCollided_bacteries_y(const QVariantList &newCollided_bacteries_y)
{
    if (m_collided_bacteries_y == newCollided_bacteries_y)
        return;

    m_collided_bacteries_y = newCollided_bacteries_y;

    emit collided_bacteries_yChanged();
}

const QVariantList &BacteriaHandler::collided_bacterie_props() const
{
    return m_collided_bacterie_props;
}

void BacteriaHandler::setCollided_bacterie_props(const QVariantList &newCollided_bacterie_props)
{
    if (m_collided_bacterie_props == newCollided_bacterie_props)
        return;

    m_collided_bacterie_props = newCollided_bacterie_props;

    emit collided_bacterie_propsChanged();
}

const QVariantList &BacteriaHandler::container_bacteries_ids() const
{
    return m_container_bacteries_ids;
}

void BacteriaHandler::setContainer_bacteries_ids(const QVariantList &newContainer_bacteries_ids)
{
    if (m_container_bacteries_ids == newContainer_bacteries_ids)
        return;

    m_container_bacteries_ids = newContainer_bacteries_ids;

    emit container_bacteries_idsChanged();
}
