#include "Mouse4DirectionsHandler.hpp"
#include "MouseHookHandler.hpp"

#include "MouseInfo.hpp"

#include <QDebug>
#include <cmath>

static const int32_t WAIT_FOR_MOVE_TIMEOUT = 50;

Mouse4DirectionsHandler::Mouse4DirectionsHandler(std::shared_ptr<MouseHookHandler> mouseHookHandler, QObject *parent)
    : QObject(parent)
    , mMouseHookHandler(mouseHookHandler)
    , mHorizontalDirection()
    , mVerticalDirection()
    , mStartX(0)
    , mStartY(0)
    , mMouseInfoWidget(nullptr)
    , mHorizontalTimer(nullptr)
    , mVerticalTimer(nullptr)
{
    qDebug() << "Mouse4DirectionsHandler()";
    connect(mMouseHookHandler.get(), &MouseHookHandler::mouseCoordsChanged, this, &Mouse4DirectionsHandler::onMouseCoordsChanged);

    mHorizontalTimer = std::make_shared<QTimer>(this);
    mHorizontalTimer->setSingleShot(true);
    mVerticalTimer = std::make_shared<QTimer>(this);
    mVerticalTimer->setSingleShot(true);

    connect(mHorizontalTimer.get(), &QTimer::timeout, this, &Mouse4DirectionsHandler::onHorizontalTimeout);
    connect(mVerticalTimer.get(), &QTimer::timeout, this, &Mouse4DirectionsHandler::onVerticalTimeout);

    mMouseInfoWidget = std::make_shared<MouseInfo>();
}

Mouse4DirectionsHandler::~Mouse4DirectionsHandler()
{
    qDebug() << "~Mouse4DirectionsHandler()";
    if(mMouseHookHandler != nullptr)
    {
        mMouseHookHandler->stop();
    }

    mMouseInfoWidget->close();
    qDebug() << "~Mouse4DirectionsHandler() finished";
}

void Mouse4DirectionsHandler::start()
{
    initStartPoint();
    mMouseInfoWidget->move(1700, 0);
    mMouseInfoWidget->show();
    mMouseHookHandler->start();
}

void Mouse4DirectionsHandler::stop()
{
    mMouseInfoWidget->releaseAll();
    mMouseInfoWidget->close();
    mMouseHookHandler->stop();
}

void Mouse4DirectionsHandler::onMouseCoordsChanged(const int32_t x, const int32_t y)
{
    checkX(x, y);
    checkY(x, y);
    mMouseInfoWidget->mouseCoordinatesChanged(x, y);
}

void Mouse4DirectionsHandler::onHorizontalTimeout()
{
    qDebug() << "onHorizontalTimeout";
    mHorizontalDirection.isActive = false;
    sendMouseDirectionChanged(mHorizontalDirection);
}

void Mouse4DirectionsHandler::onVerticalTimeout()
{
    qDebug() << "onVerticalTimeout";
    mVerticalDirection.isActive = false;
    sendMouseDirectionChanged(mVerticalDirection);
}

void Mouse4DirectionsHandler::sendMouseDirectionChanged(const sDirectionState& directionState)
{
    qDebug() << "sendMouseDirectionChanged: direction = " << HeadGamer::directionToJson(directionState.direction)
             << " isActive = " << directionState.isActive;
    emit mouseDirectionChanged(directionState.direction, directionState.isActive);
    directionState.isActive ? mMouseInfoWidget->presed(directionState.direction)
                            : mMouseInfoWidget->released(directionState.direction);
}

void Mouse4DirectionsHandler::checkX(const int32_t x, const int32_t y)
{
    const int32_t dX = x - mStartX;

    //nothing changed
    if(dX == 0)
    {
        return;
    }

    const HeadGamer::eDirection newDirection = deltaXToDirection(dX);
    const bool isDirectionChanged = (mHorizontalDirection.direction != newDirection);
    //if direction changed => stop current direction
    if(isDirectionChanged && (std::abs(dX) > mDeadZone) && mHorizontalDirection.isActive)
    {
//        qDebug() << "checkX 1: mStartX = " << mStartX << "x = " << x << " dX = " << dX
//                 << " direction = " << HeadGamer::directionToJson(mHorizontalDirection.direction)
//                 << " newDirection = " << HeadGamer::directionToJson(newDirection);
        mHorizontalDirection.isActive = false;
        sendMouseDirectionChanged(mHorizontalDirection);
        mStartX = x;
        mHorizontalTimer->stop();
        return;
    }

    if(mHorizontalDirection.isActive)
    {
        if(!isDirectionChanged)
        {
//            qDebug() << "checkX 2";
            mStartX = x;
            mHorizontalTimer->stop();
            mHorizontalTimer->start(WAIT_FOR_MOVE_TIMEOUT);
        }
        return;
    }

    if(std::abs(dX) >= mThreshold)
    {
        //Deactivate active vertical direction button
        //TODO add check for direcction
        if(mVerticalDirection.isActive)
        {
//            qDebug() << "checkX 3";
            mVerticalDirection.isActive = false;
            sendMouseDirectionChanged(mVerticalDirection);
            mStartY = y;
            mVerticalTimer->stop();
        }

//        qDebug() << "checkX 4";
        mHorizontalDirection.isActive = true;
        mHorizontalDirection.direction = newDirection;
        sendMouseDirectionChanged(mHorizontalDirection);
        mStartX = x;
        mStartY = y;
        mHorizontalTimer->start(WAIT_FOR_MOVE_TIMEOUT);
    }
}

void Mouse4DirectionsHandler::checkY(const int32_t x, const int32_t y)
{
    const int32_t dY = y - mStartY;

    //nothing changed
    if(dY == 0)
    {
        return;
    }

    const HeadGamer::eDirection newDirection = deltaYToDirection(dY);
    const bool isDirectionChanged = (mVerticalDirection.direction != newDirection);
    //if direction changed => stop current direction
    if(isDirectionChanged && (std::abs(dY) > mDeadZone) && mVerticalDirection.isActive)
    {
//        qDebug() << "checkY 1";
        mVerticalDirection.isActive = false;
        sendMouseDirectionChanged(mVerticalDirection);
        mStartY = y;
        mVerticalTimer->stop();
        return;
    }

    if(mVerticalDirection.isActive)
    {
        if(!isDirectionChanged)
        {
//            qDebug() << "checkY 2";
            mStartY = y;
            mVerticalTimer->stop();
            mVerticalTimer->start(WAIT_FOR_MOVE_TIMEOUT);
        }
        return;
    }

    if(std::abs(dY) >= mThreshold)
    {
        //Deactivate active horizintal direction button
        //TODO add check for direcction
        if(mHorizontalDirection.isActive)
        {
//            qDebug() << "checkY 3";
            mHorizontalDirection.isActive = false;
            sendMouseDirectionChanged(mHorizontalDirection);
            mStartY = y;
            mHorizontalTimer->stop();
        }

//        qDebug() << "checkY 4";
        mVerticalDirection.isActive = true;
        mVerticalDirection.direction = newDirection;
        sendMouseDirectionChanged(mVerticalDirection);
        mStartY = y;
        mStartX = x;
        mVerticalTimer->start(WAIT_FOR_MOVE_TIMEOUT);
    }
}

void Mouse4DirectionsHandler::initStartPoint()
{
    QPoint p = mMouseInfoWidget->mapFromGlobal(QCursor::pos());
    mStartX = p.x() + mMouseInfoWidget->x();
    mStartY = p.y() + mMouseInfoWidget->y();
    qDebug() << "start point: x = " << mStartX << "y = " << mStartY;
}

HeadGamer::eDirection Mouse4DirectionsHandler::deltaXToDirection(const int32_t dX)
{
    return (dX > 0) ? HeadGamer::eDirection::RIGHT : HeadGamer::eDirection::LEFT;
}

HeadGamer::eDirection Mouse4DirectionsHandler::deltaYToDirection(const int32_t dY)
{
    return (dY > 0) ? HeadGamer::eDirection::DOWN : HeadGamer::eDirection::UP;
}
