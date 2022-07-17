#ifndef IJSON_H
#define IJSON_H

#include <QJsonObject>

class IJson
{
public:
    virtual QJsonObject toJson() const = 0;
    virtual void fromJson(const QJsonObject& json) = 0;
};

#endif // IJSON_H
