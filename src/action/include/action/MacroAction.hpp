#ifndef MACROACTION_HPP
#define MACROACTION_HPP

#include "ActionBase.hpp"

#include <vector>

class MacroAction;
using tMacroActionPtr = std::shared_ptr<MacroAction>;
using tConstMacroActionPtr = const std::shared_ptr<const MacroAction>;

class MacroAction : public ActionBase
{
public:
    MacroAction();
    MacroAction(const QString& name);
    virtual ~MacroAction() = default;

    // IAction interface
    void action() override;
    void start() override;
    void stop() override;

    //IJson interface
    QJsonObject toJson() const override;
    void fromJson(const QJsonObject& json) override;

    void addAction(tActionPtr action);
    void removeAction(int32_t index);

    // TODO implement swap method


    void setPathToMacro(const QString& path);

private:
    std::vector<tActionPtr> mActions;
    // Used to save path to macro as json instead of actions
    QString mPathToMacro;
};

#endif // MACROACTION_HPP
