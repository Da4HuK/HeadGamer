#ifndef IACTION_HPP
#define IACTION_HPP

#include "common/IJson.hpp"

#include <QJsonObject>
#include <memory>

class IAction : public IJson
{
public:
    virtual ~IAction() = default;

    virtual void action() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual const QString& getName() const = 0;
};

using tActionPtr = std::shared_ptr<IAction>;
using tContsActionPtr = const std::shared_ptr<const IAction>;

#endif // IACTION_HPP
