#include "common/Types.hpp"

#include <algorithm>

static const QString MODE_KEY("mode");
static const QString MODE_1("MODE_1");
static const QString MODE_2("MODE_2");

static const QString DIRECTIONS_COUNT_KEY("directionsCount");
static const int8_t FOUR_DIRECTIONS = 4;
static const int8_t EIGHT_DIRECTIONS = 8;

static const QString BUTTON_PRESS_TYPE_KEY("buttonPressType");
static const QString HOLD("HOLD");
static const QString HOLD_FOR_TIME("HOLD_FOR_TIME");

static const QString UP("UP");
static const QString DOWN("DOWN");
static const QString LEFT("LEFT");
static const QString RIGHT("RIGHT");

namespace HeadGamer
{

QString modeToJson(const eMode mode)
{
    QString result("");
    switch (mode)
    {
    case eMode::MODE_1:
        result = MODE_1;
        break;
    case eMode::MODE_2:
        result = MODE_2;
        break;
    case eMode::UNDEFINED:
    default:
        break;
    }

    return result;
}

eMode jsonToMode(const QJsonObject& json)
{
    if((json.contains(MODE_KEY) == false) || (json[MODE_KEY].isString() == false))
    {
        return eMode::UNDEFINED;
    }

    QString strMode = json[MODE_KEY].toString();
    if(strMode == MODE_1)
    {
        return eMode::MODE_1;
    }

    if(strMode == MODE_2)
    {
        return eMode::MODE_2;
    }

    return eMode::UNDEFINED;
}

int8_t directionsCountToJson(const eDirectionsCount directionsCount)
{
    int8_t result = FOUR_DIRECTIONS;
    switch (directionsCount)
    {
    case eDirectionsCount::FOUR:
        result = FOUR_DIRECTIONS;
        break;
    case eDirectionsCount::EIGHT:
        result = EIGHT_DIRECTIONS;
        break;
    default:
        break;
    }

    return result;
}

eDirectionsCount jsonToDirectionsCount(const QJsonObject& json)
{
    eDirectionsCount result = eDirectionsCount::FOUR;
    if((json.contains(DIRECTIONS_COUNT_KEY) == false) || (json[DIRECTIONS_COUNT_KEY].isDouble() == false))
    {
        return result;
    }

    int8_t directionCount = json[DIRECTIONS_COUNT_KEY].toInt();
    switch (directionCount)
    {
    case FOUR_DIRECTIONS:
        result = eDirectionsCount::FOUR;
        break;
    case EIGHT_DIRECTIONS:
        result = eDirectionsCount::EIGHT;
        break;
    }

    return result;

}

QString buttonPressTypeToJson(const eButtonPressType buttonPressType)
{
    QString result("");
    switch (buttonPressType)
    {
    case eButtonPressType::HOLD:
        result = HOLD;
        break;
    case eButtonPressType::HOLD_FOR_TIME:
        result = HOLD_FOR_TIME;
        break;
    case eButtonPressType::UNDEFINED:
    default:
        break;
    }

    return result;
}

eButtonPressType jsonToButtonPressType(const QJsonObject& json)
{
    if((json.contains(BUTTON_PRESS_TYPE_KEY) == false) || (json[BUTTON_PRESS_TYPE_KEY].isString() == false))
    {
        return eButtonPressType::UNDEFINED;
    }

    QString strButtonPressType = json[BUTTON_PRESS_TYPE_KEY].toString();
    if(strButtonPressType == HOLD)
    {
        return eButtonPressType::HOLD;
    }

    if(strButtonPressType == HOLD_FOR_TIME)
    {
        return eButtonPressType::HOLD_FOR_TIME;
    }

    return eButtonPressType::UNDEFINED;
}

int32_t jsonToInt32(const QJsonObject& json, const QString& parameterName, const int32_t defaultValue)
{
    if((json.contains(parameterName) == false) || (json[parameterName].isDouble() == false))
    {
        return defaultValue;
    }
    return json[parameterName].toInt(defaultValue);
}

int32_t findVirtualKey(const QString& buttonStr)
{
    auto is_eaqual = [&buttonStr](const tButton& button){ return (button.buttonStr == buttonStr); };
    auto res = std::find_if(VIRTUAL_KEYS.cbegin(), VIRTUAL_KEYS.cend(), is_eaqual);
    if(res != VIRTUAL_KEYS.cend())
    {
        return res->virtualKey;
    }

    return VC_UNDEFINED;
}

QString jsonToString(const QJsonObject& json, const QString& parameterName, const QString& defaultValue)
{
    if((json.contains(parameterName) == false) || (json[parameterName].isString() == false))
    {
        return defaultValue;
    }

    return json[parameterName].toString(defaultValue);
}

QString directionToJson(const eDirection direction)
{
    QString result("");
    switch (direction)
    {
    case HeadGamer::eDirection::UP:
        result = UP;
        break;
    case HeadGamer::eDirection::DOWN:
        result = DOWN;
        break;
    case HeadGamer::eDirection::LEFT:
        result = LEFT;
        break;
    case HeadGamer::eDirection::RIGHT:
        result = RIGHT;
        break;

    default:
        break;
    }

    return result;
}

QJsonObject colorToJson(const QColor& color)
{
    QJsonObject json;
    json[*(HeadGamer::WINDOW_COLOR_R_STR)] = color.red();
    json[*(HeadGamer::WINDOW_COLOR_G_STR)] = color.green();
    json[*(HeadGamer::WINDOW_COLOR_B_STR)] = color.blue();
    json[*(HeadGamer::WINDOW_COLOR_ALPHA_STR)] = color.alpha();
    return json;
}

QColor jsonToColor(const QJsonObject& json)
{
    auto readColorPart = [json] (QString colorPartStr)
    {
        return jsonToInt32(json, colorPartStr, 0);
    };

    int32_t r = readColorPart(*(HeadGamer::WINDOW_COLOR_R_STR));
    int32_t g = readColorPart(*(HeadGamer::WINDOW_COLOR_G_STR));
    int32_t b = readColorPart(*(HeadGamer::WINDOW_COLOR_B_STR));
    int32_t a = readColorPart(*(HeadGamer::WINDOW_COLOR_ALPHA_STR));

    return QColor(r, g, b, a);
}

bool isJsonObjectPresent(const QString& name, const QJsonObject& json)
{
    return ((json.contains(name) == true) && (json[name].isObject() == true));
}

bool isJsonArrayPresent(const QString& name, const QJsonObject& json)
{
    return ((json.contains(name) == true) && (json[name].isArray() == true));
}

QJsonArray actionsVectorToJson(const tActionsVector& vector)
{
    QJsonArray array;
    for (auto&& item : vector)
    {
        array.append(item->toJson());
    }
    return array;
}

tActionsVector jsonToActionsVector(const QJsonArray& array)
{
    tActionsVector result;
    for(auto&& item : array)
    {
        result.push_back(Utils::jsonToAction(item.toObject()));
    }

    return result;
}

}
