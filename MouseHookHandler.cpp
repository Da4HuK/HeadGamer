#include "MouseHookHandler.hpp"


#include <QDebug>


MouseHookHandler* mouseHandlerPtr = nullptr;

#ifdef Q_OS_WIN
LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    //according to msdn if retun 0 then:
    // it may return a nonzero value to prevent the system from passing the message to the rest of the hook chain or the target window procedure.
    //See https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/ms644985(v=vs.85)
    MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
    if (nCode == HC_ACTION && pMouseStruct != nullptr && mouseHandlerPtr != nullptr)
    {
        switch (wParam)
        {
            case WM_MOUSEMOVE:
            emit mouseHandlerPtr->mouseCoordsChanged(pMouseStruct->pt.x, pMouseStruct->pt.y);
            break;
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
#endif // Q_OS_WIN

MouseHookHandler::MouseHookHandler(QObject *parent)
    : QObject(parent)
    //, m_LowLevelMouseHookHandle(nullptr)
{
    qDebug() << "MouseHookHandler()";
    mouseHandlerPtr = this;
}

MouseHookHandler::~MouseHookHandler()
{
    qDebug() << "~MouseHookHandler()";
    mouseHandlerPtr = nullptr;
    stop();
    qDebug() << "~MouseHookHandler() finished";
}

void MouseHookHandler::start()
{
    qDebug() << "MouseHookHandler::start()";
#ifdef Q_OS_WIN
    if(m_LowLevelMouseHookHandle == nullptr)
    {
        m_LowLevelMouseHookHandle = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, 0, 0);
    }
#endif // Q_OS_WIN
}

void MouseHookHandler::stop()
{
    qDebug() << "MouseHookHandler::stop()";
#ifdef Q_OS_WIN
    if(m_LowLevelMouseHookHandle != nullptr)
    {
        UnhookWindowsHookEx(m_LowLevelMouseHookHandle);
        m_LowLevelMouseHookHandle = nullptr;
    }
#endif // Q_OS_WIN
    qDebug() << "MouseHookHandler::stop() finished";
}
