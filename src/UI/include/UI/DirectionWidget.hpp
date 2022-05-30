#ifndef DIRECTIONWIDGET_HPP
#define DIRECTIONWIDGET_HPP

#include "common/Types.hpp"
#include "UI/DirectionButton.hpp"

#include <QWidget>
#include <map>

class DirectionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DirectionWidget(QWidget *parent = nullptr);
    virtual ~DirectionWidget();
    virtual QSize minimumSizeHint() const override;

public slots:
    void pressed(const HeadGamer::eDirection direction);
    void released(const HeadGamer::eDirection direction);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void draw();

    std::map<HeadGamer::eDirection, DirectionButton> mDirectionButtons;

};

#endif // DIRECTIONWIDGET_HPP
