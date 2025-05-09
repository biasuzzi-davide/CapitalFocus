#ifndef PLACEIMPORTFROMJSON_H
#define PLACEIMPORTFROMJSON_H

#include<QJsonArray>
#include<QString>
#include<vector>
#include <memory>
#include "model/Place.h"

class PlaceImportFromJson{
private:
    weeklyOpenings parseOpenings(const QJsonArray& parent) const;

public:
    PlaceImportFromJson()=default;
    std::vector<std::shared_ptr<Place>> importFromJson(const QString& filePath) const;
};

#endif // PLACEIMPORTFROMJSON_H
