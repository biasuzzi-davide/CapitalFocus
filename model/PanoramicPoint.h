#ifndef PanoramicPoint_H
#define PanoramicPoint_H

#include "Entertainment.h" // Eredita da Entertainment

// Rappresenta un punto panoramico, un tipo di posto Entertainment
class PanoramicPoint : public Entertainment {
private:
    double altitude; // Altitudine
    bool hasBinocular; // Ha binocoli d'osservazione
    bool nightLighting; // Ha l'illuminazione notturna

public:
    // Costruttore
    PanoramicPoint(const QString& name, const QString& city, const QString& description,
                    double rating, const weeklyOpenings& open, double cost,
                    QTime avgStayDuration, int minimumAge, const QString& restrictedEntry,
                    double altitude, bool hasBinocular, bool nightLighting);

    virtual ~PanoramicPoint() = default; // Distruttore

    // Dice la categoria
    QString getCategory() const override;

    // Per il Visitor
    void acceptVisitor(PlaceVisitorInterface& visitor) const override;

    // Riassunto intrattenimento
    QString getEntertainmentSummary() const override;

    // Getter
    double getAltitude() const;
    bool hasBinoculars() const;
    bool isNightLit() const;
};

#endif // PanoramicPoint_H
