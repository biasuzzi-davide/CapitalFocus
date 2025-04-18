#ifndef WEEKLYOPENINGS_H
#define WEEKLYOPENINGS_H

#include <QMap>
#include <QTime>
#include "weekday.h"
#include "openingFrames.h"

// Classe necessaria per gestire le fasce orarie d'apertura dei locali
class weeklyOpenings {
private:
    QMap<Weekday, openingFrames> schedule;

public:
    // Metodo per impostare una fascia oraria di un weekday
    void setOpening(Weekday day, const QTime& open, const QTime& close);
    weeklyOpenings();
    weeklyOpenings(const weeklyOpenings& other);
    openingFrames getOpening(Weekday day) const;

    // Ritorna True se il locale è aperto un determinato weekday prima di una certa ora
    bool opensBefore(Weekday day, const QTime& time) const;

    // Ritorna True se il locale è aperto un determinato weekday ad una certa ora
    bool isOpenAt(Weekday day, const QTime& time) const;

    // Metodo necessario per l'interfaccia grafica
    QString getOpeningFrameString(Weekday day) const;

    const QMap<Weekday, openingFrames>& getSchedule() const;

};

#endif // WEEKLYOPENINGS_H
