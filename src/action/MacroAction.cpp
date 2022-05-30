#include "action/MacroAction.hpp"
#include "common/Types.hpp"

#include <QJsonArray>

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

tMacroActionPtr MacroAction::jsonToAction(const QJsonObject& json)
{
    if (HeadGamer::isJsonArrayPresent(*(HeadGamer::MACROS_STR), json))
    {
        QJsonArray array = json[*(HeadGamer::MACROS_STR)].toArray();
        // TODO store and read macro name in/from json
        tMacroActionPtr macroAction = std::make_shared<MacroAction>("Macro");
        for (auto&& item : array)
        {
            auto action = Utils::jsonToAction(item.toObject());
            if (action != nullptr)
            {
                macroAction->addAction(action);
            }
        }
        QString pathToMacro = HeadGamer::jsonToString(json, *(HeadGamer::PATH_TO_ACTION_STR));
        if (pathToMacro.isEmpty() == false)
        {
            macroAction->setPathToMacro(pathToMacro);
        }
        return macroAction;
    }

    // Try to read action by file path
//    return Utils::jsonToAction(*(HeadGamer::MACROS_STR), json);
    return nullptr;
}

void MacroAction::setPathToMacro(const QString& path)
{
    mPathToMacro = path;
}
