#ifndef KEYPRESSACTION_HPP
#define KEYPRESSACTION_HPP

#include "action/ActionBase.hpp"

#include <memory>

class KeyPressAction;
using tKeyPressActionPtr = const std::shared_ptr<const KeyPressAction>;

class KeyboardHandler;

class KeyPressAction : public ActionBase
{
public:
    KeyPressAction(const QString& key, const int32_t virtualKey);

    virtual ~KeyPressAction() override;

    // IAction interface
    virtual void action() override;
    virtual void start() override;
    virtual void stop() override;
    virtual QJsonObject toJson() const override;

    static tActionPtr jsonToAction(const QJsonObject& json);

private:
    QString mKey;
    int32_t mVirtualKey;
    KeyboardHandler& mKeyboardHandler;
};

#endif // KEYPRESSACTION_HPP
