#include "DirectionWidget.hpp"

#include <QPainter>
#include <vector>

#include <QDebug>

DirectionWidget::DirectionWidget(QWidget *parent)
    : QWidget(parent)
    , mDirectionButtons()
{
//    setWindowTitle(tr("Directions window"));
    //    resize(200, 200);

    std::vector<QPoint> leftArrow = {
            QPoint(-95, -30),
            QPoint(-35, -30),
            QPoint(-5, 0),
            QPoint(-35, 30),
            QPoint(-95, 30)
        };

    std::vector<QPoint> rightArrow = {
        QPoint(95, -30),
        QPoint(35, -30),
        QPoint(5, 0),
        QPoint(35, 30),
        QPoint(95, 30)
    };

    std::vector<QPoint> upArrow = {
        QPoint(-30, -95 ),
        QPoint(-30, -35),
        QPoint(0, -5),
        QPoint(30, -35),
        QPoint(30, -95)
    };

    std::vector<QPoint> downArrow = {
        QPoint(-30, 95 ),
        QPoint(-30, 35),
        QPoint(0, 5),
        QPoint(30, 35),
        QPoint(30, 95)
    };

    mDirectionButtons.emplace(std::pair{HeadGamer::eDirection::LEFT, DirectionButton(leftArrow)});
    mDirectionButtons.emplace(std::pair{HeadGamer::eDirection::RIGHT, DirectionButton(rightArrow)});
    mDirectionButtons.emplace(std::pair{HeadGamer::eDirection::UP, DirectionButton(upArrow)});
    mDirectionButtons.emplace(std::pair{HeadGamer::eDirection::DOWN, DirectionButton(downArrow)});
    qDebug() << "DirectionWidget()";
}

DirectionWidget::~DirectionWidget()
{
    qDebug() << "~DirectionWidget()";
}

QSize DirectionWidget::minimumSizeHint() const
{
    static QSize minimalSize(50, 50);
    return minimalSize;
}

void DirectionWidget::pressed(const HeadGamer::eDirection direction)
{
    mDirectionButtons.at(direction).setPressed(true);
    this->update();
}

void DirectionWidget::released(const HeadGamer::eDirection direction)
{
    mDirectionButtons.at(direction).setPressed(false);
    this->update();
}

void DirectionWidget::paintEvent(QPaintEvent* )
{
    draw();
}

void DirectionWidget::draw()
{
    int side = qMin(width(), height());

    QPainter* painter = new QPainter(this);

    painter->translate(width() / 2, height() / 2);
    painter->scale(side / 200.0, side / 200.0);
    painter->save();

    for (auto&& button : mDirectionButtons)
    {
        button.second.draw(painter);
    }

    painter->restore();
    delete painter;
}
