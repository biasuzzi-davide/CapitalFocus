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
    bool  isClosed(Weekday day)       const;
    bool  isAlwaysOpen(Weekday day)   const;   // aperto 24 h
    QTime openTime(Weekday day)       const;
    QTime closeTime(Weekday day)      const;
    // Metodo per impostare una fascia oraria di un weekday
    void setOpening(Weekday day, const QTime& open, const QTime& close);
    void setClosed(Weekday day);
    weeklyOpenings();
    weeklyOpenings(const weeklyOpenings& other);
    openingFrames getOpening(Weekday day) const;

    void setAlwaysOpen(Weekday d);

    // Ritorna True se il locale è aperto un determinato weekday prima di una certa ora
    bool opensBefore(Weekday day, const QTime& time) const;

    // Ritorna True se il locale è aperto un determinato weekday ad una certa ora
    bool isOpenAt(Weekday day, const QTime& time) const;

    // Metodo necessario per l'interfaccia grafica
    QString getOpeningFrameString(Weekday day) const;

    const QMap<Weekday, openingFrames>& getSchedule() const;

    static QString weekdayToString(const Weekday day);

    static Weekday weekdayFromString(const QString& dayStr);
    QString toQStringMultiline() const;
};

#endif // WEEKLYOPENINGS_H
