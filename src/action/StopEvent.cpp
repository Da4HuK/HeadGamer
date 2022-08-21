#include "action/StopEvent.hpp"

StopEvent::StopEvent()
{

}

StopEvent& StopEvent::getInstance()
{
    static StopEvent instance;
    return instance;
}

void StopEvent::sendEvent()
{
    emit stopEmulation();
}
