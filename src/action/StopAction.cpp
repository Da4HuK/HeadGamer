#include "action/StopAction.hpp"
#include "action/StopEvent.hpp"
#include "common/Types.hpp"


StopAction::StopAction()
    : ActionBase("Stop")
{

}

void StopAction::action()
{
    start();
}

void StopAction::start()
{
    StopEvent::getInstance().sendEvent();
}

void StopAction::stop()
{
    // do nothing
}

QJsonObject StopAction::toJson() const
{
    QJsonObject json;
    json[*(HeadGamer::TYPE_STR)] = *(HeadGamer::STOP_ACTION_STR);
    return json;
}

void StopAction::fromJson(const QJsonObject& /*json*/)
{
    // Do nothing
}
