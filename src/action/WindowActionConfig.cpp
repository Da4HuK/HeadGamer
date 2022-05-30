#include "action/WindowActionConfig.hpp"
#include "common/Types.hpp"

WindowActionConfig::WindowActionConfig()
//    : mPathToMacro("")
{

}

QJsonObject WindowActionConfig::toJson() const
{
    QJsonObject json;
    json[*(HeadGamer::WINDOW_ACTION_NAME_STR)] = mName;
    json[*(HeadGamer::WINDOW_WIDTH_STR)] = mWidth;
    json[*(HeadGamer::WINDOW_HEIGHT_STR)] = mHeight;
    json[*(HeadGamer::WINDOW_POSITION_X_STR)] = mX;
    json[*(HeadGamer::WINDOW_POSITION_Y_STR)] = mY;
    json[*(HeadGamer::WINDOW_COLOR_STR)] = HeadGamer::colorToJson(mColor);
    if (mAction != nullptr)
    {
        json[*(HeadGamer::ACTION_STR)] = mAction->toJson();
//        if (mPathToMacro.isEmpty())
//        {
//        }
//        else
//        {
//            json[*(HeadGamer::ACTION_STR)] = mPathToMacro;
//        }
    }

    return json;
}

void WindowActionConfig::fromJson(const QJsonObject& json, const tWindowActionConfigPtr& windowConfig)
{
    windowConfig->setName(HeadGamer::jsonToString(json, *(HeadGamer::WINDOW_ACTION_NAME_STR), ""));
    windowConfig->setWidth(HeadGamer::jsonToInt32(json, *(HeadGamer::WINDOW_WIDTH_STR), 100));
    windowConfig->setHeight(HeadGamer::jsonToInt32(json, *(HeadGamer::WINDOW_HEIGHT_STR), 100));
    windowConfig->setX(HeadGamer::jsonToInt32(json, *(HeadGamer::WINDOW_POSITION_X_STR), 0));
    windowConfig->setY(HeadGamer::jsonToInt32(json, *(HeadGamer::WINDOW_POSITION_Y_STR), 0));
    windowConfig->setColor(HeadGamer::jsonToColor(json));
    windowConfig->setAction(Utils::jsonToAction(*(HeadGamer::ACTION_STR), json));
}

const QString& WindowActionConfig::getName() const
{
    return mName;
}

void WindowActionConfig::setName(const QString& newName)
{
    mName = newName;
}

int32_t WindowActionConfig::getWidth() const
{
    return mWidth;
}

void WindowActionConfig::setWidth(int32_t newWidth)
{
    mWidth = newWidth;
}

int32_t WindowActionConfig::getHeight() const
{
    return mHeight;
}

void WindowActionConfig::setHeight(int32_t newHeight)
{
    mHeight = newHeight;
}

int32_t WindowActionConfig::getX() const
{
    return mX;
}

void WindowActionConfig::setX(int32_t newX)
{
    mX = newX;
}

int32_t WindowActionConfig::getY() const
{
    return mY;
}

void WindowActionConfig::setY(int32_t newY)
{
    mY = newY;
}

const QColor& WindowActionConfig::getColor() const
{
    return mColor;
}

void WindowActionConfig::setColor(const QColor& newColor)
{
    mColor = newColor;
}

const tActionPtr& WindowActionConfig::getAction() const
{
    return mAction;
}

void WindowActionConfig::setAction(const tActionPtr& newAction)
{
    mAction = newAction;
}

//const QString& WindowActionConfig::getPathToMacro() const
//{
//    return mPathToMacro;
//}

//void WindowActionConfig::setPathToMacro(const QString& path)
//{
//    mPathToMacro = path;
//}
