#ifndef PLACEEXPORTTOJSONVISITOR_H
#define PLACEEXPORTTOJSONVISITOR_H

#include "placevisitorinterface.h"
#include <QJsonObject>
#include <QJsonArray>

class PlaceExportToJsonVisitor: public PlaceVisitorInterface{
private:
    QJsonObject result;

    QJsonObject exportFoodData(const Food& f) const;
    QJsonObject exportShoppingData(const Food& f) const;
    QJsonObject exportEntertainmentData(const Food& f) const;
    QJsonObject exportCultureData(const Food& f) const;

public:
    PlaceExportToJsonVisitor()=default;
    QJsonObject getResult() const;  // restituisce l'elemento Json creato
    QJsonArray exportWeeklyOpenings(const weeklyOpenings&) const;
    QJsonObject basePlaceToJson(const Place& place, const QString& type) const;     // Implementazioni per ogni tipo concreto
    void visit(const Place& p) override;
    void visit(const Cafe& cafe) override;
    void visit(const Disco& disco) override;
    void visit(const Mall& mall) override;
    void visit(const LocalMarket& market) override;
    void visit(const Restaurant& restaurant) override;
    void visit(const PanoramicPoints& point) override;
    void visit(const Museum& museum) override;
    void visit(const Monument& monument) override;
};

#endif // PLACEEXPORTTOJSONVISITOR_H
