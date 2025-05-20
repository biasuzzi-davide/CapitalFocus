#ifndef PLACEEXPORTTOJSONVISITOR_H
#define PLACEEXPORTTOJSONVISITOR_H

#include "placevisitorinterface.h"
#include <QJsonObject>
#include <QJsonArray>

// Un Visitor per esportare Place in formato JSON
class PlaceExportToJsonVisitor: public PlaceVisitorInterface{
private:
    QJsonObject result; // L'oggetto JSON creato per il Place visitato

    // Crea array JSON per gli orari
    QJsonArray exportWeeklyOpenings(const weeklyOpenings&) const;

    // Crea oggetto JSON per i dati base di Place
    QJsonObject basePlaceToJson(const Place& place, const QString& type) const;

public:
    // Costruttore di default
    PlaceExportToJsonVisitor()=default;

    // Ritorna l'oggetto JSON creato dopo la visita
    QJsonObject getResult() const;

    // Implementazioni dei metodi visit per i vari tipi di Place, creano l'oggetto JSON per il Place visitato
    void visit(const Place& p) override; // Per la classe base
    void visit(const Cafe& cafe) override;
    void visit(const Disco& disco) override;
    void visit(const Mall& mall) override;
    void visit(const LocalMarket& market) override;
    void visit(const Restaurant& restaurant) override;
    void visit(const PanoramicPoint& point) override;
    void visit(const Museum& museum) override;
    void visit(const Monument& monument) override;
};

#endif // PLACEEXPORTTOJSONVISITOR_H
