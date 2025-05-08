#ifndef PANORAMICPOINTS_H
#define PANORAMICPOINTS_H

#include "Entertainment.h"

class PanoramicPoints : public Entertainment {
private:
    double altitude;
    bool hasBinocular;
    bool nightLighting;

public:
    PanoramicPoints(const QString& name, const QString& city, const QString& description,
                    double rating, const weeklyOpenings& open, double cost,
                    double avgStayDuration, int minimumAge, const QString& restrictedEntry,
                    double altitude, bool hasBinocular, bool nightLighting);

    QString getCategory() const override;

    void acceptVisitor(PlaceVisitorInterface& visitor) const override;
    double getAltitude() const;
    bool hasBinoculars() const;
    bool isNightLit() const;
    QString getEntertainmentSummary() const override;
};

#endif // PANORAMICPOINTS_H
