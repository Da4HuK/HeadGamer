#include "Settings.hpp"

QJsonObject Settings::toJson() const
{
    QJsonObject json;
    //TODO use constants
    json["mode"] = HeadGamer::modeToJson(mMode);
    json["presetName"] = mPresetName;
    json["windowCinfigName"] = mWindowCinfigName;
    //MODE_1
    json["directionsCount"] = HeadGamer::directionsCountToJson(mDirectionsCount);
    json["triggerThreshold"] = mTriggerThreshold;
    json["buttonPressType"] = HeadGamer::buttonPressTypeToJson(mButtonPressType);
    json["buttonPressTimeOut"] = mButtonPressTimeOut;
    return json;
}

void Settings::fromJson(const QJsonObject& json, const tSettingsPtr& settings)
{
    settings->setMode(HeadGamer::jsonToMode(json));
    settings->setPresetName(HeadGamer::jsonToString(json, "presetName"));
    settings->setWindowCinfigName(HeadGamer::jsonToString(json, "windowCinfigName"));
    //MODE_1
    settings->setDirectionsCount(HeadGamer::jsonToDirectionsCount(json));
    settings->setTriggerThreshold(HeadGamer::jsonToInt32(json, "triggerThreshold", 100));
    settings->setButtonPressType(HeadGamer::jsonToButtonPressType(json));
    settings->setButtonPressTimeOut(HeadGamer::jsonToInt32(json, "buttonPressTimeOut", 50));
}

const HeadGamer::tMouseDirectionBinding& Settings::getDirectionBindings() const
{
    return mDirectionBindings;
}

void Settings::setDirectionBindings(const HeadGamer::tMouseDirectionBinding& newDirectionBindings)
{
    mDirectionBindings = newDirectionBindings;
}

const HeadGamer::tMouseButtonBinding& Settings::getMouseButtonBindings() const
{
    return mMouseButtonBindings;
}

void Settings::setMouseButtonBindings(const HeadGamer::tMouseButtonBinding& newMouseButtonBindings)
{
    mMouseButtonBindings = newMouseButtonBindings;
}

HeadGamer::eMode Settings::getMode() const
{
    return mMode;
}

void Settings::setMode(HeadGamer::eMode newMode)
{
    mMode = newMode;
}

HeadGamer::eDirectionsCount Settings::getDirectionsCount() const
{
    return mDirectionsCount;
}

void Settings::setDirectionsCount(HeadGamer::eDirectionsCount newDirectionsCount)
{
    mDirectionsCount = newDirectionsCount;
}

int32_t Settings::getTriggerThreshold() const
{
    return mTriggerThreshold;
}

void Settings::setTriggerThreshold(int32_t newTriggerThreshold)
{
    mTriggerThreshold = newTriggerThreshold;
}

HeadGamer::eButtonPressType Settings::getButtonPressType() const
{
    return mButtonPressType;
}

void Settings::setButtonPressType(HeadGamer::eButtonPressType newButtonPressType)
{
    mButtonPressType = newButtonPressType;
}

int32_t Settings::getButtonPressTimeOut() const
{
    return mButtonPressTimeOut;
}

void Settings::setButtonPressTimeOut(int32_t newButtonPressTimeOut)
{
    mButtonPressTimeOut = newButtonPressTimeOut;
}

const QString& Settings::getPresetName() const
{
    return mPresetName;
}

void Settings::setPresetName(const QString& newPresetName)
{
    mPresetName = newPresetName;
}

const QString& Settings::getWindowCinfigName() const
{
    return mWindowCinfigName;
}

void Settings::setWindowCinfigName(const QString& newWindowCinfigName)
{
    mWindowCinfigName = newWindowCinfigName;
}
