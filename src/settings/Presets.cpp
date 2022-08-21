#include "settings/Presets.hpp"
#include "common/Utils.hpp"
#include "common/Types.hpp"

static const QString UP_ACTION_NAME = {"Up"};
static const QString DOWN_ACTION_NAME = {"Down"};
static const QString LEFT_ACTION_NAME = {"Left"};
static const QString RIGHT_ACTION_NAME = {"Right"};

static const QString LEFT_MOUSE_ACTION_NAME = {"LMB"};
static const QString RIGHT_MOUSE_ACTION_NAME = {"RMB"};
static const QString MIDDLE_MOUSE_ACTION_NAME = {"MMB"};

QJsonObject Presets::toJson() const
{
    QJsonObject json;
    //Save mouse direction actions
    actionToJson(UP_ACTION_NAME, mUpAction, json);
    actionToJson(DOWN_ACTION_NAME, mDownAction, json);
    actionToJson(LEFT_ACTION_NAME, mLeftAction, json);
    actionToJson(RIGHT_ACTION_NAME, mRightAction, json);

    //Save mouse buttons actions
    actionToJson(LEFT_MOUSE_ACTION_NAME, mLeftMouseAction, json);
    actionToJson(RIGHT_MOUSE_ACTION_NAME, mRightMouseAction, json);
    actionToJson(MIDDLE_MOUSE_ACTION_NAME, mMiddleMouseAction, json);

    return json;
}

void Presets::fromJson(const QJsonObject& json)
{
    setUpAction( Utils::jsonToAction(UP_ACTION_NAME, json));
    setDownAction( Utils::jsonToAction(DOWN_ACTION_NAME, json));
    setLeftAction( Utils::jsonToAction(LEFT_ACTION_NAME, json));
    setRightAction( Utils::jsonToAction(RIGHT_ACTION_NAME, json));

    setLeftMouseAction(Utils::jsonToAction(LEFT_MOUSE_ACTION_NAME, json));
    setRightMouseAction(Utils::jsonToAction(RIGHT_MOUSE_ACTION_NAME, json));
    setMiddleMouseAction(Utils::jsonToAction(MIDDLE_MOUSE_ACTION_NAME, json));
}

void Presets::actionToJson(const QString& name, tConstActionPtr action, QJsonObject& json)
{
    if(name.isEmpty())
    {
        //Throw exception
    }

    if(action == nullptr)
    {
        json[name] = *(HeadGamer::ACTION_NONE_STR);
    }
    else
    {
        json[name] = action->toJson();
    }
}

const tActionPtr& Presets::getUpAction() const
{
    return mUpAction;
}

void Presets::setUpAction(const tActionPtr& newUpAction)
{
    mUpAction = newUpAction;
}

const tActionPtr& Presets::getDownAction() const
{
    return mDownAction;
}

void Presets::setDownAction(const tActionPtr& newDownAction)
{
    mDownAction = newDownAction;
}

const tActionPtr& Presets::getLeftAction() const
{
    return mLeftAction;
}

void Presets::setLeftAction(const tActionPtr& newLeftAction)
{
    mLeftAction = newLeftAction;
}

const tActionPtr& Presets::getRightAction() const
{
    return mRightAction;
}

void Presets::setRightAction(const tActionPtr& newRightAction)
{
    mRightAction = newRightAction;
}

void Presets::setLeftMouseAction(const tActionPtr& newLeftMouseAction)
{
    mLeftMouseAction = newLeftMouseAction;
}

const tActionPtr& Presets::getLeftMouseAction() const
{
    return mLeftMouseAction;
}

const tActionPtr& Presets::getRightMouseAction() const
{
    return mRightMouseAction;
}

void Presets::setRightMouseAction(const tActionPtr& newRightMouseAction)
{
    mRightMouseAction = newRightMouseAction;
}

const tActionPtr& Presets::getMiddleMouseAction() const
{
    return mMiddleMouseAction;
}

void Presets::setMiddleMouseAction(const tActionPtr& newMiddleMouseAction)
{
    mMiddleMouseAction = newMiddleMouseAction;
}
