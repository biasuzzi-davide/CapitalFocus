#ifndef MUSEUM_H
#define MUSEUM_H

#include "Culture.h" // Eredita da Culture

// Rappresenta un museo, un tipo di posto Culture
class Museum : public Culture {
private:
    bool hasAudioGuide; // Ha audioguida

public:
    // Costruttore
    Museum(const QString& name, const QString& city, const QString& description,
           double rating, const weeklyOpenings& open, double cost,
           double studentDiscount, bool guidedTour,
           const QString& culturalFocus,
           bool hasAudioGuide);

    virtual ~Museum() = default; // Distruttore

    // Dice la categoria
    QString getCategory() const override;

    // Per il Visitor
    virtual void acceptVisitor(PlaceVisitorInterface& visitor) const override;

    // Riassunto culturale
    QString getCultureSummary() const override;

    // Getter
    bool hasAudioGuideAvailable() const;
};

#endif // MUSEUM_H
