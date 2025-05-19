#ifndef ENTERTAINMENT_H
#define ENTERTAINMENT_H

#include "Place.h" // Eredita da Place
#include <QTime>

// Base per posti legati all'intrattenimento
class Entertainment : public Place {
private:
    QTime avgStayDuration; // Durata media della visita
    int minimumAge; // Età minima
    QString restrictedEntry; // Restrizioni ingresso

public:
    // Costruttore
    Entertainment(const QString& name, const QString& city, const QString& description,
                  double rating, const weeklyOpenings& open, double cost,
                  QTime avgStayDuration, int minimumAge, const QString& restrictedEntry);

    virtual ~Entertainment() = default; // Distruttore

    // Riassunto intrattenimento
    virtual QString getEntertainmentSummary() const = 0;

    // Getter
    QTime getAvgStayDuration() const;
    int getMinAge() const;
    QString getRestrictedEntry() const;
};

#endif // ENTERTAINMENT_H
