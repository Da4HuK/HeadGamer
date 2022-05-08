#include "UI/DirectionButton.hpp"

DirectionButton::DirectionButton(const std::vector<QPoint>& points)
    : mPoints(points)
    , mReleasedColor(0, 0, 0)
    , mPresedColor(255, 0, 0)
    , mIsPressed(false)
{
}

DirectionButton::DirectionButton(const DirectionButton& button)
    : mPoints(button.mPoints)
    , mReleasedColor(button.mReleasedColor)
    , mPresedColor(button.mPresedColor)
    , mIsPressed(button.mIsPressed)
{
}

void DirectionButton::draw(QPainter* painter)
{
    mIsPressed ? painter->setBrush(mPresedColor) : painter->setBrush(mReleasedColor);
    painter->save();

    painter->drawConvexPolygon(mPoints.data(), mPoints.size());
    painter->restore();
}

void DirectionButton::setPressed(bool isPressed)
{
    mIsPressed = isPressed;
}

DirectionButton::~DirectionButton()
{

}

void DirectionButton::copyPoints(const QPoint* src, QPoint* dest, const uint32_t count)
{
    if(src == nullptr)
    {
        return;
    }

    for(uint32_t i = 0; i < count; ++i)
    {
       dest[i] = src[i];
    }
}
