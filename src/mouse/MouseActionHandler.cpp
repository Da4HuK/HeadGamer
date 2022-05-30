#include "mouse/MouseActionHandler.hpp"

#include <QDebug>


MouseActionHandler::MouseActionHandler(tPresetPtr& presets,
                                       const std::shared_ptr<Mouse4DirectionsHandler>& mouseDirectionHandler,
                                       QObject *parent)
    : QObject(parent)
    , mPresets(presets)
{
    connect(mouseDirectionHandler.get(), &Mouse4DirectionsHandler::mouseDirectionChanged,
            this, &MouseActionHandler::onMouseDirectionChanged);
}

void MouseActionHandler::executeDirectionAction(tActionPtr action, bool isActive) const
{
    if(action == nullptr)
    {
        qDebug() << "executeDirectionAction: ignore acttion";
        return;
    }

    qDebug() << "executeDirectionAction:";
    isActive ? action->start() : action->stop();
}

void MouseActionHandler::onMouseDirectionChanged(HeadGamer::eDirection direction, bool isActive)
{
    qDebug() << "onMouseDirectionChanged: direction = " << HeadGamer::directionToJson(direction) << " isActive = " << isActive;
    switch (direction)
    {
    case HeadGamer::eDirection::UP:
        executeDirectionAction(mPresets->getUpAction(), isActive);
        break;
    case HeadGamer::eDirection::DOWN:
        executeDirectionAction(mPresets->getDownAction(), isActive);
        break;
    case HeadGamer::eDirection::LEFT:
        executeDirectionAction(mPresets->getLeftAction(), isActive);
        break;
    case HeadGamer::eDirection::RIGHT:
        executeDirectionAction(mPresets->getRightAction(), isActive);
        break;

    }
}
