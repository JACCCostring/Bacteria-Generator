#ifndef COLLIDED_BACTERIES_HELPER_H
#define COLLIDED_BACTERIES_HELPER_H

#include <QObject>
#include <QVariantList>

#include "bacterie.h"

class Collided_Bacteries_Helper : public QObject
{
    Q_OBJECT

public:
    explicit Collided_Bacteries_Helper(const QList<Bacterie> &m_bacteries, int nd, int st,
                                       QObject *parent = nullptr);

public slots:
    void start_process();

signals:
    void process_done(const QVariantList &, const QVariantList &,
                            const QVariantList &, const QVariantList &);

private:
    QList<Bacterie> collided_bacteries;

    int start;
    int end;
};

#endif // COLLIDED_BACTERIES_HELPER_H
