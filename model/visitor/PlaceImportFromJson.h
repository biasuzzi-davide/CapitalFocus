#ifndef PLACEIMPORTFROMJSON_H
#define PLACEIMPORTFROMJSON_H

#include <QJsonArray>
#include <QString>
#include <vector>
#include <memory>
#include "model/Place.h"
#include "model/weeklyOpenings.h"

// Classe per importare dati Place da un file JSON
class PlaceImportFromJson{
private:
    // Parsa gli orari di apertura da un array JSON
    weeklyOpenings parseOpenings(const QJsonArray& parent) const;

public:
    // Costruttore di default
    PlaceImportFromJson() = default;

    // Legge i Place da un file JSON
    std::vector<std::shared_ptr<Place>> importFromJson(const QString& filePath) const;
};

#endif // PLACEIMPORTFROMJSON_H
