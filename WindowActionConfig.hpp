#ifndef WINDOWACTIONCONFIG_HPP
#define WINDOWACTIONCONFIG_HPP

#include "action/IAction.hpp"

#include <string>
#include <QColor>

class WindowActionConfig;

using tWindowActionConfigPtr = std::shared_ptr<WindowActionConfig>;
using tContsWindowActionConfigPtr = const std::shared_ptr<const WindowActionConfig>;

class WindowActionConfig
{
public:
    WindowActionConfig();

    QJsonObject toJson() const;
    static void fromJson(const QJsonObject& json, const tWindowActionConfigPtr& windowConfig);

    const QString& getName() const;
    void setName(const QString& newName);
    int32_t getWidth() const;
    void setWidth(int32_t newWidth);
    int32_t getHeight() const;
    void setHeight(int32_t newHeight);
    int32_t getX() const;
    void setX(int32_t newX);
    int32_t getY() const;
    void setY(int32_t newY);
    const QColor& getColor() const;
    void setColor(const QColor& newColor);
    const tActionPtr& getAction() const;
    void setAction(const tActionPtr& newAction);

//    const QString& getPathToMacro() const;
//    void setPathToMacro(const QString& path);

private:
    QString mName;
    int32_t mWidth;
    int32_t mHeight;
    int32_t mX;
    int32_t mY;
    QColor mColor;
    tActionPtr mAction;
//    QString mPathToMacro;
};

#endif // WINDOWACTIONCONFIG_HPP
