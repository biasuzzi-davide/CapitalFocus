#ifndef PLACEVISITORINTERFACE_H
#define PLACEVISITORINTERFACE_H
#include "../Cafe.h"
#include "../Disco.h"
#include "../Mall.h"
#include "../LocalMarket.h"
#include "../Restaurant.h"
#include "../PanoramicPoints.h"
#include "../Museum.h"
#include "../Monument.h"

class PlaceVisitorInterface
{
public:
    virtual ~PlaceVisitorInterface() = default;

    virtual void visit(const Cafe& cafe) = 0;
    virtual void visit(const Disco& disco) = 0;
    virtual void visit(const Mall& mall) = 0;
    virtual void visit(const LocalMarket& market) = 0;
    virtual void visit(const Restaurant& restaurant) = 0;
    virtual void visit(const PanoramicPoints& point) = 0;
    virtual void visit(const Museum& museum) = 0;
    virtual void visit(const Monument& monument) = 0;
};

#endif // PLACEVISITORINTERFACE_H
