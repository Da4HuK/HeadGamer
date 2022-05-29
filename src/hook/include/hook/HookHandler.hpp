#ifndef HOOK_HANDLER_HPP
#define HOOK_HANDLER_HPP

#include "uiohook.h"

#include <QObject>
#include <memory>
#include <thread>

class HookHandler;
using tHookHandlerPtr = std::shared_ptr<HookHandler>;
using tConstHookHandlertPtr = const std::shared_ptr<const HookHandler>;

class HookHandler: public QObject
{
    Q_OBJECT
public:
    HookHandler();
    virtual ~HookHandler();
    void start();
    void stop();

signals:
    void mouseCoordsChanged(const int x, const int y);

private:
    void hookRun();

    std::unique_ptr<std::thread> mHookThread;
};

#endif // HookHandler_HPP
