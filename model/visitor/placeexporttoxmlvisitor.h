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
#include "../PanoramicPoint.h"
#include "../LocalMarket.h"
#include "../Mall.h"
#include "../Museum.h"
#include "../Monument.h"

// Visitor per esportare Place in formato XML
class PlaceExportToXmlVisitor : public PlaceVisitorInterface {
private:
    QDomDocument& doc; // Il documento XML su cui lavorare
    QDomElement result; // L'elemento XML creato per il Place visitato

    // Crea elemento XML per gli orari
    QDomElement exportWeeklyOpenings(const weeklyOpenings& w) const;

    // Crea elemento XML per i dati base di Place
    QDomElement basePlaceToXml(const Place& place, const QString& type) const;

    // Crea elemento XML per i dati specifici di Food
    QDomElement exportFoodData(const Food& f) const;
    // Crea elemento XML per i dati specifici di Shopping
    QDomElement exportShoppingData(const Shopping& s) const;
    // Crea elemento XML per i dati specifici di Entertainment
    QDomElement exportEntertainmentData(const Entertainment& ent) const;
    // Crea elemento XML per i dati specifici di Culture
    QDomElement exportCultureData(const Culture& c) const;

public:
    // Costruttore, prende il documento XML di destinazione
    explicit PlaceExportToXmlVisitor(QDomDocument& document);

    // Ritorna l'elemento XML creato dopo la visita
    QDomElement getResult() const;

    // Implementazioni dei metodi visit per i vari tipi di Place, creano l'elemento XML per il Place visitato
    void visit(const Place& place) override; // Per la classe base
    void visit(const Cafe& cafe) override;
    void visit(const Disco& disco) override;
    void visit(const Mall& mall) override;
    void visit(const LocalMarket& market) override;
    void visit(const Restaurant& restaurant) override;
    void visit(const PanoramicPoint& point) override;
    void visit(const Museum& museum) override;
    void visit(const Monument& monument) override;
};

#endif // PLACEEXPORTTOXMLVISITOR_Hs
