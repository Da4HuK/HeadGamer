#ifndef MOUSEINFO_HPP
#define MOUSEINFO_HPP

#include <QWidget>

#include "UI/DirectionWidget.hpp"

namespace Ui {
class MouseInfo;
}

class MouseInfo : public QWidget
{
    Q_OBJECT

public:
    explicit MouseInfo(QWidget *parent = nullptr);
    virtual ~MouseInfo();

public slots:
    void presed(const HeadGamer::eDirection direction);
    void released(const HeadGamer::eDirection direction);
    void releaseAll();
    void mouseCoordinatesChanged(const int32_t x, const int32_t y);

private:
    void setWidgetProperties();

    Ui::MouseInfo *ui;
    DirectionWidget* mDirectWidget;
};

#endif // MOUSEINFO_HPP
