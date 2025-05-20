#ifndef PLACEVISITORINTERFACE_H
#define PLACEVISITORINTERFACE_H

#include "../Cafe.h"
#include "../Disco.h"
#include "../Mall.h"
#include "../LocalMarket.h"
#include "../Restaurant.h"
#include "../PanoramicPoint.h"
#include "../Museum.h"
#include "../Monument.h"
#include "../Place.h"

// Interfaccia per i Visitor, definisce i metodi che ogni Visitor deve implementare
class PlaceVisitorInterface
{
public:
    virtual ~PlaceVisitorInterface() = default;

    // Metodo visit per ogni tipo specifico di Place
    virtual void visit(const Cafe& cafe) = 0;
    virtual void visit(const Disco& disco) = 0;
    virtual void visit(const Mall& mall) = 0;
    virtual void visit(const LocalMarket& market) = 0;
    virtual void visit(const Restaurant& restaurant) = 0;
    virtual void visit(const PanoramicPoint& point) = 0;
    virtual void visit(const Museum& museum) = 0;
    virtual void visit(const Monument& monument) = 0;

    // Metodo visit per la classe base Place
    virtual void visit(const Place& p) = 0;
};

#endif // PLACEVISITORINTERFACE_H
