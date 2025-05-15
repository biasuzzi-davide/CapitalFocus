#ifndef MONUMENT_H
#define MONUMENT_H

#include "Culture.h" // Eredita da Culture

// Rappresenta un monumento, un tipo di posto Culture
class Monument : public Culture {
private:
    bool isUnescoHeritage; // Patrimonio UNESCO
    QString conservationStatus; // Stato conservazione
    bool openToPublic; // Aperto al pubblico

public:
    // Costruttore
    Monument(const QString& name, const QString& city, const QString& description,
             double rating, const weeklyOpenings& open, double cost,
             double studentDiscount, bool guidedTour,
             const QString& culturalFocus,
             bool isUnescoHeritage, const QString& conservationStatus, bool openToPublic);

    virtual ~Monument() = default; // Distruttore

    // Dice la categoria
    QString getCategory() const override;

    // Per il Visitor
    virtual void acceptVisitor(PlaceVisitorInterface& visitor) const override;

    // Riassunto culturale
    QString getCultureSummary() const override;

    // Getter
    bool isUnesco() const;
    QString getConservationStatus() const;
    bool isOpenToPublic() const;
};

#endif // MONUMENT_H
