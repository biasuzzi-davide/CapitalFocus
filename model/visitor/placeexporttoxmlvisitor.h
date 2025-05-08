#ifndef PLACEEXPORTTOXMLVISITOR_H
#define PLACEEXPORTTOXMLVISITOR_H

#include "placevisitorinterface.h"
#include <QDomDocument>
#include <QDomElement>
#include <QString>
#include "../weeklyOpenings.h"
#include "../Place.h"
#include "../Food.h"
#include "../Shopping.h"
#include "../Entertainment.h"
#include "../Cafe.h"
#include "../Restaurant.h"
#include "../Disco.h"
#include "../PanoramicPoints.h"
#include "../LocalMarket.h"
#include "../Mall.h"
#include "../Museum.h"
#include "../Monument.h"

class PlaceExportToXmlVisitor : public PlaceVisitorInterface {
private:
    QDomDocument& doc;
    QDomElement result;

    QDomElement exportWeeklyOpenings(const weeklyOpenings& w) const;
    QDomElement basePlaceToXml(const Place& place, const QString& type) const;
    QDomElement exportFoodData(const Food& f) const;
    QDomElement exportShoppingData(const Shopping& s) const;
    QDomElement exportEntertainmentData(const Entertainment& e) const;

public:
    explicit PlaceExportToXmlVisitor(QDomDocument& document);
    QDomElement getResult() const;

    void visit(const Place& place) override;
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
