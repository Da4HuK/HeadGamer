#include "common/Types.hpp"

#include <algorithm>

namespace HeadGamer
{

QString modeToJson(const eMode mode)
{
    QString result("");
    switch (mode)
    {
    case eMode::MODE_1:
        result = "MODE_1";
        break;
    case eMode::MODE_2:
        result = "MODE_2";
        break;
    case eMode::UNDEFINED:
    default:
        break;
    }

    return result;
}

eMode jsonToMode(const QJsonObject& json)
{
    if((json.contains("mode") == false) || (json["mode"].isString() == false))
    {
        return eMode::UNDEFINED;
    }

    QString strMode = json["mode"].toString();
    if(strMode == "MODE_1")
    {
        return eMode::MODE_1;
    }

    if(strMode == "MODE_2")
    {
        return eMode::MODE_2;
    }

    return eMode::UNDEFINED;
}

int8_t directionsCountToJson(const eDirectionsCount directionsCount)
{
    int8_t result = 4;
    switch (directionsCount)
    {
    case eDirectionsCount::FOUR:
        result = 4;
        break;
    case eDirectionsCount::EIGHT:
        result = 8;
        break;
    default:
        break;
    }

    return result;
}

eDirectionsCount jsonToDirectionsCount(const QJsonObject& json)
{
    eDirectionsCount result = eDirectionsCount::FOUR;
    if((json.contains("directionsCount") == false) || (json["directionsCount"].isDouble() == false))
    {
        return result;
    }

    int8_t directionCount = json["directionsCount"].toInt();
    switch (directionCount)
    {
    case 4:
        result = eDirectionsCount::FOUR;
        break;
    case 8:
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
        result = "HOLD";
        break;
    case eButtonPressType::HOLD_FOR_TIME:
        result = "HOLD_FOR_TIME";
        break;
    case eButtonPressType::UNDEFINED:
    default:
        break;
    }

    return result;
}

eButtonPressType jsonToButtonPressType(const QJsonObject& json)
{
    if((json.contains("buttonPressType") == false) || (json["buttonPressType"].isString() == false))
    {
        return eButtonPressType::UNDEFINED;
    }

    QString strButtonPressType = json["mode"].toString();
    if(strButtonPressType == "HOLD")
    {
        return eButtonPressType::HOLD;
    }

    if(strButtonPressType == "HOLD_FOR_TIME")
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

    return KEY_NONE;
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
        result = "UP";
        break;
    case HeadGamer::eDirection::DOWN:
        result = "DOWN";
        break;
    case HeadGamer::eDirection::LEFT:
        result = "LEFT";
        break;
    case HeadGamer::eDirection::RIGHT:
        result = "RIGHT";
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
