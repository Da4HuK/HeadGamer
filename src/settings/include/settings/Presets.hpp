#ifndef PRESETS_H
#define PRESETS_H

#include "action/IAction.hpp"
#include "common/IJson.hpp"

#include <memory>
class Presets;
using tPresetPtr = std::shared_ptr<Presets>;
using tConstPresetPtr = const std::shared_ptr<const Presets>;

class Presets : public IJson
{
public:
    QJsonObject toJson()  const override;
    void fromJson(const QJsonObject& json) override;

    const tActionPtr& getUpAction() const;
    void setUpAction(const tActionPtr& newUpAction);

    const tActionPtr& getDownAction() const;
    void setDownAction(const tActionPtr& newDownAction);

    const tActionPtr& getLeftAction() const;
    void setLeftAction(const tActionPtr& newLeftAction);

    const tActionPtr& getRightAction() const;
    void setRightAction(const tActionPtr& newRightAction);

    const tActionPtr& getLeftMouseAction() const;
    void setLeftMouseAction(const tActionPtr& newLeftMouseAction);

    const tActionPtr& getRightMouseAction() const;
    void setRightMouseAction(const tActionPtr& newRightMouseAction);

    const tActionPtr& getMiddleMouseAction() const;
    void setMiddleMouseAction(const tActionPtr& newMiddleMouseAction);

private:
    static void actionToJson(const QString& name, tConstActionPtr action, QJsonObject& json);

    tActionPtr mUpAction;
    tActionPtr mDownAction;
    tActionPtr mLeftAction;
    tActionPtr mRightAction;
    tActionPtr mLeftMouseAction;
    tActionPtr mRightMouseAction;
    tActionPtr mMiddleMouseAction;
};

#endif // PRESETS_H
