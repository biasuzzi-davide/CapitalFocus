#ifndef PLACEEXPORTTOXMLVISITOR_H
#define PLACEEXPORTTOXMLVISITOR_H

#include "placevisitorinterface.h"
#include <QDomDocument>
#include <QDomElement>

class PlaceExportToXmlVisitor : public PlaceVisitorInterface {
private:
    QDomDocument& doc;
    QDomElement result;

public:
    explicit PlaceExportToXmlVisitor(QDomDocument& document);  // costruttore
    QDomElement getResult() const;  // restituisce l'elemento XML creato
    QDomElement exportWeeklyOpenings(const weeklyOpenings&) const;
    QString weekdayToString(Weekday day) const;
    QDomElement basePlaceToXml(const Place& place, const QString& type) const;     // Implementazioni per ogni tipo concreto
    void visit(const Cafe& cafe) override;
    void visit(const Disco& disco) override;
    void visit(const Mall& mall) override;
    void visit(const LocalMarket& market) override;
    void visit(const Restaurant& restaurant) override;
    void visit(const PanoramicPoints& point) override;
    void visit(const Museum& museum) override;
    void visit(const Monument& monument) override;
};

#endif // PLACEEXPORTTOXMLVISITOR_H
