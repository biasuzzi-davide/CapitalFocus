#ifndef LOCALMARKET_H
#define LOCALMARKET_H

#include "Shopping.h"

// Classe concreta derivata da Shopping
class LocalMarket : public Shopping {
private:
    bool artisans;   // True se artigiani presenti
    bool seasonal;   // True se mercatino stagionale
    QString period;  // Stringa che indica il periodo

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

    // Getter
    bool hasArtisans() const;
    bool isSeasonal() const;
    QString getPeriod() const;

    // Override del metodo polimorfo della classe base
    QString getCategory() const override;

    virtual ~LocalMarket() = default;

    void acceptVisitor(PlaceVisitorInterface& visitor) const override;

};

#endif // LOCALMARKET_H
