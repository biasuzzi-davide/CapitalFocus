#ifndef MALL_H
#define MALL_H

#include "Shopping.h"

// Classe concreta derivata da Shopping
class Mall : public Shopping {
private:
    int shopCount;       // Numero di negozi
    bool cinema;         // True se presente un cinema
    bool freeParking;    // True se presente parcheggio gratuito

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

    // Getter
    int getShopCount() const;
    bool hasCinema() const;
    bool hasFreeParking() const;

    // Override del metodo polimorfo della classe base
    QString getCategory() const override;

    virtual ~Mall() = default;

    void acceptVisitor(PlaceVisitorInterface& visitor) const override;

};

#endif // MALL_H
