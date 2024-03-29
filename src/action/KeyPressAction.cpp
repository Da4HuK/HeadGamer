#include "action/KeyPressAction.hpp"
#include "common/Types.hpp"
#include "keyboard/KeyboardHandler.hpp"

#include <QDebug>

KeyPressAction::KeyPressAction()
    : ActionBase("")
    , mKey("")
    , mVirtualKey(VC_UNDEFINED)
    , mKeyboardHandler(KeyboardHandler::getInstance())
{

}

KeyPressAction::KeyPressAction(const QString& key, const int32_t virtualKey)
    : ActionBase(key)
    , mKey(key)
    , mVirtualKey(virtualKey)
    , mKeyboardHandler(KeyboardHandler::getInstance())
{

}

KeyPressAction::~KeyPressAction()
{
    qDebug() << "KeyPressAction::~KeyPressAction: mKey = " << mKey;
}

void KeyPressAction::action()
{
    //Press and release
    start();
    stop();
}

void KeyPressAction::start()
{
    qDebug() << "KeyPressAction::start: mKey = " << mKey;
    mKeyboardHandler.pressKeyboardButton(mVirtualKey);
}

void KeyPressAction::stop()
{
    qDebug() << "KeyPressAction::stop: mKey = " << mKey;
    mKeyboardHandler.releaseKeyboardButton(mVirtualKey);
}

QJsonObject KeyPressAction::toJson() const
{
    QJsonObject json;
    json[*(HeadGamer::TYPE_STR)] = *(HeadGamer::KEY_PRESS_ACTION_STR);
    json[*(HeadGamer::KEY_STR)] = mKey;
//    json["virtualKey"] = mVirtualKey;
    return json;
}

void KeyPressAction::fromJson(const QJsonObject& json)
{
    auto key = HeadGamer::jsonToString(json, *(HeadGamer::KEY_STR), "");
    auto virtualKey = HeadGamer::findVirtualKey(key);

    if(virtualKey != VC_UNDEFINED)
    {
        mKey = key;
        mVirtualKey = virtualKey;
        setName(mKey);
    }
}
