#ifndef STOPEVENT_HPP
#define STOPEVENT_HPP

#include <QObject>

class StopEvent : public QObject
{
    Q_OBJECT

public:
    static StopEvent& getInstance();

    virtual ~StopEvent() = default;

    void sendEvent();

signals:
    void stopEmulation();

private:
    StopEvent();

};

#endif // STOPEVENT_HPP
