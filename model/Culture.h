#ifndef CULTURE_H
#define CULTURE_H

#include "Place.h" // Eredita da Place

// Base per luoghi culturali
class Culture : public Place {
protected:
    double studentDiscount; // Sconto studenti
    bool guidedTour; // Tour guidato
    QString culturalFocus; // Focus culturale

public:
    // Costruttore
    Culture(const QString& name, const QString& city, const QString& description,
            double rating, const weeklyOpenings& open, double cost,
            double studentDiscount, bool guidedTour,
            const QString& culturalFocus);

    virtual ~Culture() = default; // Distruttore

    // Riassunto culturale
    virtual QString getCultureSummary() const = 0;

    // Getter
    double getStudentDiscount() const;
    bool hasGuidedTour() const;
    QString getCulturalFocus() const;
};

#endif // CULTURE_H
