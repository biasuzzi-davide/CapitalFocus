#ifndef LOCALMARKET_H
#define LOCALMARKET_H

#include "Shopping.h" // Eredita da Shopping

// Rappresenta un mercato locale, un tipo di posto Shopping
class LocalMarket : public Shopping {
private:
    bool artisans; // Artigiani presenti
    bool seasonal; // È stagionale
    QString period; // Periodo di apertura

public:
    // Costruttore
    LocalMarket(const QString& name,
                const QString& city,
                const QString& description,
                double rating,
                const weeklyOpenings& hours,
                double cost,
                bool outdoor,
                bool foodArea,
                int standNumber,
                bool artisans,
                bool seasonal,
                const QString& period);

    virtual ~LocalMarket() = default; // Distruttore

    // Riassunto specifico per LocalMarket
    QString getShoppingSummary() const override;

    // Dice la categoria
    QString getCategory() const override;

    // Per il Visitor
    void acceptVisitor(PlaceVisitorInterface& visitor) const override;

    // Getter
    bool hasArtisans() const;
    bool isSeasonal() const;
    QString getPeriod() const;
};

#endif // LOCALMARKET_H
