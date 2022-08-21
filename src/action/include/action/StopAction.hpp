#ifndef STOPACTION_HPP
#define STOPACTION_HPP

#include "ActionBase.hpp"

#include <memory>

class StopAction : public ActionBase
{
public:
    StopAction();
    virtual ~StopAction() = default;

    // IAction interface
public:
    void action() override;
    void start() override;
    void stop() override;

    // IJson interface
    QJsonObject toJson() const override;
    void fromJson(const QJsonObject& json) override;

};

#endif // STOPACTION_HPP
