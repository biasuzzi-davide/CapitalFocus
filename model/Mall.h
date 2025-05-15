#ifndef MALL_H
#define MALL_H

#include "Shopping.h" // Eredita da Shopping

// Rappresenta un centro commerciale, un tipo di posto Shopping
class Mall : public Shopping {
private:
    int shopCount; // Numero negozi
    bool cinema; // Ha cinema
    bool freeParking; // Parcheggio gratuito

public:
    // Costruttore
    Mall(const QString& name,
         const QString& city,
         const QString& description,
         double rating,
         const weeklyOpenings& hours,
         double cost,
         bool outdoor,
         bool foodArea,
         int standNumber,
         int shopCount,
         bool cinema,
         bool freeParking);

    virtual ~Mall() = default; // Distruttore

    // Riassunto shopping
    QString getShoppingSummary() const override;

    // Dice la categoria
    QString getCategory() const override;

    // Per il Visitor
    void acceptVisitor(PlaceVisitorInterface& visitor) const override;

    // Getter
    int getShopCount() const;
    bool hasCinema() const;
    bool hasFreeParking() const;
};

#endif // MALL_H
