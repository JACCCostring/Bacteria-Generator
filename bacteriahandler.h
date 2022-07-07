#ifndef BACTERIAHANDLER_H
#define BACTERIAHANDLER_H

#include <QObject>
#include <QVariant>
#include <QTimer>

#include "bacterie.h"

class BacteriaHandler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantList bacteria_container READ bacteria_container
               WRITE setBacteria_container NOTIFY bacteria_containerChanged)

    Q_PROPERTY(QVariantList bacteria_container_y READ bacteria_container_y
               WRITE setBacteria_container_y NOTIFY bacteria_container_yChanged)

    Q_PROPERTY(QVariantList bacteria_properties READ bacteria_properties
               WRITE setBacteria_properties NOTIFY bacteria_propertiesChanged)

    Q_PROPERTY(QVariantList collided_bacteries_x READ collided_bacteries_x
               WRITE setCollided_bacteries_x NOTIFY collided_bacteries_xChanged)

    Q_PROPERTY(QVariantList collided_bacteries_y READ collided_bacteries_y
               WRITE setCollided_bacteries_y NOTIFY collided_bacteries_yChanged)

    Q_PROPERTY(QVariantList collided_bacterie_props READ collided_bacterie_props
               WRITE setCollided_bacterie_props NOTIFY collided_bacterie_propsChanged)

    Q_PROPERTY(QVariantList container_bacteries_ids READ container_bacteries_ids
               WRITE setContainer_bacteries_ids NOTIFY container_bacteries_idsChanged)

public:
    explicit BacteriaHandler(QObject *parent = nullptr);

    Q_INVOKABLE void generate_bacteries(QVariant); //methot to generate bacteries
    Q_INVOKABLE void move_bacteries(); //methot to move bacteries
    Q_INVOKABLE void stop_movment(); //methot to stop bacteries movment
    Q_INVOKABLE void set_to_time_refresh(QVariant); //method for timer refresh
    Q_INVOKABLE void supervise_collided_bacteries(QVariant, QVariant); //method for retrieve collided bacteries
    Q_INVOKABLE int collided_bacteries_length(); //method for collided bacteries container length

    const QVariantList &bacteria_container() const; //getter
    void setBacteria_container(const QVariantList &newBacteria_container); //setter

    const QVariantList &bacteria_properties() const; //getter
    void setBacteria_properties(const QVariantList &newBacteria_properties); //setter

    const QVariantList &bacteria_container_y() const; //getter
    void setBacteria_container_y(const QVariantList &newBacteria_container_y); //setter

    const QVariantList &collided_bacteries_x() const; //getter
    void setCollided_bacteries_x(const QVariantList &newCollided_bacteries_x); //setter

    const QVariantList &collided_bacteries_y() const; //getter
    void setCollided_bacteries_y(const QVariantList &newCollided_bacteries_y); //setter

    const QVariantList &collided_bacterie_props() const; //getter
    void setCollided_bacterie_props(const QVariantList &newCollided_bacterie_props); //setter

    const QVariantList &container_bacteries_ids() const;
    void setContainer_bacteries_ids(const QVariantList &newContainer_bacteries_ids);

private:
    bool analyze_bacteries_movment(Bacterie &); //to analyze bacteries movment

private slots:
    void onTrigger_Movment();
    void onCollider_helper_done(const QVariantList &, const QVariantList &, const QVariantList &, const QVariantList &);

signals:
    void bacteria_containerChanged();
    void bacteria_propertiesChanged();
    void bacteria_container_yChanged();
    void new_bacteria_generated();
    void collided_bacteries_xChanged();
    void collided_bacteries_yChanged();
    void collided_bacterie_propsChanged();

    void container_bacteries_idsChanged();

private:
    QVariantList m_bacteria_container; //for saving all bacteries changes for QML exposing property

    QVariantList m_bacteria_properties; //for collecting bacteries properties, Ex. gender, age and color
    QVariantList m_collided_bacterie_props;

    QVariantList m_collided_bacteries_x;
    QVariantList m_collided_bacteries_y;

    QList<Bacterie> m_bacteries; //for collecting created bacteries
    QList<Bacterie> collided_bacteries;

    QTimer trigger_movment;
    QVariantList m_bacteria_container_y;

    //value for timer
    int timer_refresh_persecond;
    QVariantList m_container_bacteries_ids;
};

#endif // BACTERIAHANDLER_H
