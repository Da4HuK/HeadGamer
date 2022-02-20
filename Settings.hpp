#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "Types.hpp"

#include <vector>
#include <memory>

class Settings;
using tSettingsPtr = std::shared_ptr<Settings>;
using tConstSettingstPtr = const std::shared_ptr<const Settings>;

class Settings
{
public:
    inline static const QString PROFILE_DIR = "settings/profiles";
    inline static const QString PRESET_DIR = "settings/presets";
    inline static const QString SCRIPT_DIR = "settings/scripts";
    inline static const QString WINDOW_DIR = "settings/windows";

    QJsonObject toJson() const;
    static void fromJson(const QJsonObject& json, const tSettingsPtr& settings);

    const HeadGamer::tMouseDirectionBinding& getDirectionBindings() const;
    void setDirectionBindings(const HeadGamer::tMouseDirectionBinding& newDirectionBindings);

    const HeadGamer::tMouseButtonBinding& getMouseButtonBindings() const;
    void setMouseButtonBindings(const HeadGamer::tMouseButtonBinding& newMouseButtonBindings);

    HeadGamer::eMode getMode() const;
    void setMode(HeadGamer::eMode newMode);

    HeadGamer::eDirectionsCount getDirectionsCount() const;
    void setDirectionsCount(HeadGamer::eDirectionsCount newDirectionsCount);

    int32_t getTriggerThreshold() const;
    void setTriggerThreshold(int32_t newTriggerThreshold);

    HeadGamer::eButtonPressType getButtonPressType() const;
    void setButtonPressType(HeadGamer::eButtonPressType newButtonPressType);

    int32_t getButtonPressTimeOut() const;
    void setButtonPressTimeOut(int32_t newButtonPressTimeOut);

    const QString& getPresetName() const;
    void setPresetName(const QString& newPresetName);

    const QString& getWindowCinfigName() const;
    void setWindowCinfigName(const QString& newWindowCinfigName);

private:
    HeadGamer::tMouseDirectionBinding mDirectionBindings;
    HeadGamer::tMouseButtonBinding mMouseButtonBindings;
    HeadGamer::eMode mMode;
    HeadGamer::eDirectionsCount mDirectionsCount;
    int32_t mTriggerThreshold;
    HeadGamer::eButtonPressType mButtonPressType;
    int32_t mButtonPressTimeOut;
    QString mPresetName;
    QString mWindowCinfigName;

};

#endif // SETTINGS_HPP
