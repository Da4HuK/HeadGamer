#ifndef MOUSEHOOKHANDLER_H
#define MOUSEHOOKHANDLER_H

#include <QObject>

#include <Windows.h>

class MouseHookHandler : public QObject
{
    Q_OBJECT
public:
    explicit MouseHookHandler(QObject *parent = nullptr);
    virtual ~MouseHookHandler();

    void start();
    void stop();

signals:
    void mouseCoordsChanged(const int x, const int y);

private:
    HHOOK m_LowLevelMouseHookHandle;
};

#endif // MOUSEHOOKHANDLER_H
