#include "hook/HookHandler.hpp"
#include "uiohook.h"
#include <QDebug>


HookHandler* hookHandlerPtr = nullptr;

void hookProc(uiohook_event* const event, void* /*user_data*/)
{
    if(hookHandlerPtr == nullptr)
    {
        return;
    }

//    qDebug() << "hookProc: type = " << event->type << " time = " << event->time << " mask = " << event->mask;

    switch (event->type) {
        case EVENT_HOOK_ENABLED:
            break;
        case EVENT_HOOK_DISABLED:
            break;
        case EVENT_KEY_PRESSED:
            break;
        case EVENT_KEY_RELEASED:
            break;
        case EVENT_KEY_TYPED:
            break;
        case EVENT_MOUSE_PRESSED:
            break;
        case EVENT_MOUSE_RELEASED:
            break;
        case EVENT_MOUSE_CLICKED:
            break;
        case EVENT_MOUSE_MOVED:
            emit hookHandlerPtr->mouseCoordsChanged(event->data.mouse.x, event->data.mouse.y);
            break;
        case EVENT_MOUSE_DRAGGED:
            break;
        case EVENT_MOUSE_WHEEL:
            break;
        default:
            break;
    }
}

HookHandler::HookHandler()
    : mHookThread(nullptr)
{
    qDebug() << "HookHandler()";
    hook_set_dispatch_proc(&hookProc, NULL);
    hookHandlerPtr = this;
}

HookHandler::~HookHandler()
{
    qDebug() << "~HookHandler()";
    hookHandlerPtr = nullptr;
    stop();
}

void HookHandler::start()
{
    if(mHookThread == nullptr)
    {
        mHookThread = std::make_unique<std::thread>(&HookHandler::hookRun, this);
    }
}

void HookHandler::stop()
{
    int status = hook_stop();
    qDebug() << "hook_stop finished with status " << status;
    if (mHookThread && mHookThread->joinable())
    {
        mHookThread->join();
    }
}

void HookHandler::hookRun()
{
    int status = hook_run();
    if (status != UIOHOOK_SUCCESS)
    {
        qDebug() << "hook_run finished with status " << status;
    }
}

