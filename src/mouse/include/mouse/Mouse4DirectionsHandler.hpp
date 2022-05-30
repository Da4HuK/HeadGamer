#ifndef MOUSE4DIRECTIONSHANDLER_HPP
#define MOUSE4DIRECTIONSHANDLER_HPP

#include "common/Types.hpp"

#include <QObject>
#include <QTimer>
#include <memory>

class MouseInfo;

struct sDirectionState
{
    sDirectionState() : direction(HeadGamer::eDirection::DOWN), isActive(false)
    {}
    HeadGamer::eDirection direction;
    bool isActive;
};

class HookHandler;

class Mouse4DirectionsHandler : public QObject
{
    Q_OBJECT
public:
    explicit Mouse4DirectionsHandler(std::shared_ptr<HookHandler> hookHandler, QObject *parent = nullptr);
    virtual ~Mouse4DirectionsHandler();

    void start();
    void stop();

signals:
    void mouseDirectionChanged(HeadGamer::eDirection direction, bool isActive);


public slots:
    void onMouseCoordsChanged(const int32_t x, const int32_t y);
    void onHorizontalTimeout();
    void onVerticalTimeout();

private:
    void sendMouseDirectionChanged(const sDirectionState& directionState);
    void checkX(const int32_t x, const int32_t y);
    void checkY(const int32_t x, const int32_t y);
    void initStartPoint();

    HeadGamer::eDirection deltaXToDirection(const int32_t dX);
    HeadGamer::eDirection deltaYToDirection(const int32_t dY);

    std::shared_ptr<HookHandler> mHookHandler;
    sDirectionState mHorizontalDirection;
    sDirectionState mVerticalDirection;
    int32_t mStartX;
    int32_t mStartY;

    const int32_t mThreshold = 100;
    const int32_t mDeadZone = 10;

    std::shared_ptr<MouseInfo> mMouseInfoWidget;
    std::shared_ptr<QTimer> mHorizontalTimer;
    std::shared_ptr<QTimer> mVerticalTimer;

};

#endif // MOUSE4DIRECTIONSHANDLER_HPP
