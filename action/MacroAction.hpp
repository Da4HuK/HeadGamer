#ifndef MACROACTION_HPP
#define MACROACTION_HPP

#include "ActionBase.hpp"

#include <vector>

class MacroAction;
using tMacroActionPtr = std::shared_ptr<MacroAction>;
using tContsMacroActionPtr = const std::shared_ptr<const MacroAction>;

class MacroAction : public ActionBase
{
public:
    MacroAction(const QString& name);

    // IAction interface
    void action() override;
    void start() override;
    void stop() override;
    QJsonObject toJson() const override;

    void addAction(tActionPtr action);
    void removeAction(int32_t index);

    // TODO implement swap method

    static tMacroActionPtr jsonToAction(const QJsonObject& json);

    void setPathToMacro(const QString& path);

private:
    std::vector<tActionPtr> mActions;
    // Used to save path to macro as json instead of actions
    QString mPathToMacro;
};

#endif // MACROACTION_HPP
