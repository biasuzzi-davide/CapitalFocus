#ifndef DISCO_H
#define DISCO_H

#include "Entertainment.h" // Eredita da Entertainment

// Rappresenta una disco, un tipo di posto Entertainment
class Disco : public Entertainment {
private:
    QString musicGenre; // Genere musicale
    bool hasPrive; // Ha area privé
    QString dressCode; // Dress code richiesto

public:
    // Costruttore
    Disco(const QString& name, const QString& city, const QString& description,
          double rating, const weeklyOpenings& open, double cost,
          QTime avgStayDuration, int minimumAge, const QString& restrictedEntry,
          const QString& musicGenre, bool hasPrive, const QString& dressCode);

    virtual ~Disco() = default; // Distruttore

    // Dice la categoria
    QString getCategory() const override;

    // Per il Visitor
    void acceptVisitor(PlaceVisitorInterface& visitor) const override;

    // Riassunto specifico per Disco
    QString getEntertainmentSummary() const override;

    // Getter
    QString getMusicGenre() const;
    bool hasPriveAccess() const;
    QString getDressCode() const;
};

#endif // DISCO_H
