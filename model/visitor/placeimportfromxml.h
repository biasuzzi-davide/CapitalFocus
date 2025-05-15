#ifndef PLACEIMPORTFROMXML_H
#define PLACEIMPORTFROMXML_H

#include <QDomDocument>
#include <QString>
#include <vector>
#include <memory>
#include "model/Place.h"
#include "model/weeklyOpenings.h"

// Classe per importare dati Place da un file XML
class PlaceImportFromXml {
private:
    // Parsa gli orari di apertura da un elemento XML
    weeklyOpenings parseOpenings(const QDomElement& parent) const;

public:
    // Costruttore di default
    PlaceImportFromXml() = default;

    // Legge i Place da un file XML
    std::vector<std::shared_ptr<Place>> importFromFile(const QString& filePath) const;
};

#endif // PLACEIMPORTFROMXML_H
