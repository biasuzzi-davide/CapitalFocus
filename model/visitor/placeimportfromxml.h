#ifndef PLACEIMPORTFROMXML_H
#define PLACEIMPORTFROMXML_H

#include <QDomDocument>
#include <QString>
#include <vector>
#include <memory>
#include "model/place.h"

class PlaceImportFromXml {
public:
    PlaceImportFromXml() = default;
    std::vector<std::shared_ptr<Place>> importFromFile(const QString& filePath) const;

private:
    weeklyOpenings parseOpenings(const QDomElement& parent) const;
};

#endif // PLACEIMPORTFROMXML_H
