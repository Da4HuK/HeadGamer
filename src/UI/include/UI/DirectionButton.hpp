#ifndef DIRECTIONBUTTON_HPP
#define DIRECTIONBUTTON_HPP

#include <QPainter>
#include <vector>

class DirectionButton
{
public:
    DirectionButton(const std::vector<QPoint>& points);
    DirectionButton(const DirectionButton& button);
    void draw(QPainter* painter);
    void setPressed(bool isPressed);

    virtual ~DirectionButton();

private:
    void copyPoints(const QPoint* src, QPoint* dest, const uint32_t count);

    const std::vector<QPoint> mPoints;

    const QColor mReleasedColor;
    const QColor mPresedColor;

    bool mIsPressed;
};

#endif // DIRECTIONBUTTON_HPP
