#include "action/MacroAction.hpp"
#include "common/Types.hpp"

#include <QJsonArray>

MacroAction::MacroAction()
    : ActionBase("")
    , mActions()
    , mPathToMacro("")
{

}

MacroAction::MacroAction(const QString& name)
    : ActionBase(name)
    , mActions()
    , mPathToMacro("")
{

}


void MacroAction::action()
{
    for (auto&& action : mActions)
    {
        action->action();
    }
}

void MacroAction::start()
{
    // What about do nothing??
    for (auto&& action : mActions)
    {
        action->start();
    }
}

void MacroAction::stop()
{
    for (auto&& action : mActions)
    {
        action->stop();
    }
}

QJsonObject MacroAction::toJson() const
{
    QJsonObject json;
    json[*(HeadGamer::TYPE_STR)] = *(HeadGamer::MACRO_ACTION_STR);

    if (mPathToMacro.isEmpty() == false)
    {
        json[*(HeadGamer::MACROS_STR)] = mPathToMacro;
    }
    else
    {
        json[*(HeadGamer::MACROS_STR)] = HeadGamer::actionsVectorToJson(mActions);
    }

    return json;
}

void MacroAction::addAction(tActionPtr action)
{
    mActions.push_back(action);
}

void MacroAction::removeAction(int32_t index)
{
    mActions.erase(mActions.begin() + index);
}

void MacroAction::fromJson(const QJsonObject& json)
{
    if (HeadGamer::isJsonArrayPresent(*(HeadGamer::MACROS_STR), json))
    {
        QJsonArray array = json[*(HeadGamer::MACROS_STR)].toArray();
        // TODO store and read macro name in/from json
        for (auto&& item : array)
        {
            auto action = Utils::jsonToAction(item.toObject());
            if (action != nullptr)
            {
                addAction(action);
            }
        }

        QString pathToMacro = HeadGamer::jsonToString(json, *(HeadGamer::PATH_TO_ACTION_STR));
        if (pathToMacro.isEmpty() == false)
        {
            setPathToMacro(pathToMacro);
        }
    }
}

void MacroAction::setPathToMacro(const QString& path)
{
    mPathToMacro = path;
}
