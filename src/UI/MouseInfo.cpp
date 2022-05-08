#include "UI/MouseInfo.hpp"
#include "ui_MouseInfo.h"

#include <QDebug>

MouseInfo::MouseInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MouseInfo),
    mDirectWidget(nullptr)
{
    ui->setupUi(this);
    mDirectWidget = new DirectionWidget(this);
    ui->horizontalLayoutDirections->insertWidget(0, mDirectWidget);

    setWidgetProperties();

    qDebug() << "~MouseInfo()";
    mDirectWidget->show();
}

MouseInfo::~MouseInfo()
{
    qDebug() << "~MouseInfo()";
    delete ui;
    delete mDirectWidget;
}

void MouseInfo::presed(const HeadGamer::eDirection direction)
{
    mDirectWidget->pressed(direction);
}

void MouseInfo::released(const HeadGamer::eDirection direction)
{
    mDirectWidget->released(direction);
}

void MouseInfo::releaseAll()
{
    mDirectWidget->released(HeadGamer::eDirection::DOWN);
    mDirectWidget->released(HeadGamer::eDirection::LEFT);
    mDirectWidget->released(HeadGamer::eDirection::RIGHT);
    mDirectWidget->released(HeadGamer::eDirection::UP);
    update();
}

void MouseInfo::mouseCoordinatesChanged(const int32_t x, const int32_t y)
{
    ui->label_X_Value->setText(std::to_string(x).c_str());
    ui->label_Y_Value->setText(std::to_string(y).c_str());
}

void MouseInfo::setWidgetProperties()
{
    Qt::WindowFlags flags = (Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    setWindowFlags(flags);
    setWindowOpacity(0.7);
//    setAttribute(Qt::WA_NoSystemBackground);
//    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_TransparentForMouseEvents);

    QPalette pal = palette();

    // set black background
    QColor color(255,255,127,255);
    pal.setColor(QPalette::Window, color);
    setPalette(pal);
}

