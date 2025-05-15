#ifndef WEEKLYOPENINGS_H
#define WEEKLYOPENINGS_H

#include <QMap>
#include <QTime>
#include <QStringList>
#include "weekday.h"
#include "openingFrames.h"

// Gestisce gli orari di apertura di tutta la settimana
class weeklyOpenings {
private:
    QMap<Weekday, openingFrames> schedule; // Orari per ogni giorno

public:
    // Costruttore di default
    weeklyOpenings();
    // Costruttore di copia
    weeklyOpenings(const weeklyOpenings& other);

    // Imposta orario per un giorno
    void setOpening(Weekday day, const QTime& open, const QTime& close);

    // Imposta un giorno come chiuso
    void setClosed(Weekday day);

    // Imposta un giorno come sempre aperto
    void setAlwaysOpen(Weekday d);

    // Controlla se è chiuso in un giorno
    bool isClosed(Weekday day) const;

    // Controlla se è sempre aperto in un giorno
    bool isAlwaysOpen(Weekday day) const;

    // Controlla se apre prima di un'ora in un giorno
    bool opensBefore(Weekday day, const QTime& time) const;

    // Controlla se è aperto a una certa ora in un giorno
    bool isOpenAt(Weekday day, const QTime& time) const;

    // Formatta gli orari di un giorno come stringa
    QString getOpeningFrameString(Weekday day) const;

    // Formatta tutti gli orari come stringa multilinea
    QString toQStringMultiline() const;

    // Converte da Weekday a stringa
    static QString weekdayToString(const Weekday day);

    // Converte da stringa a Weekday
    static Weekday weekdayFromString(const QString& dayStr);

    // Getter
    openingFrames getOpening(Weekday day) const;
    QTime openTime(Weekday day) const;
    QTime closeTime(Weekday day) const;
    const QMap<Weekday, openingFrames>& getSchedule() const;
};

#endif // WEEKLYOPENINGS_H
