#include "KeyboardHandler.hpp"
#include <QtDebug>

//#include <Windows.h>

KeyboardHandler::KeyboardHandler(QObject *parent) : QObject(parent)
{

}

void KeyboardHandler::pressKeyboardButton(const int32_t virtualKey)
{
    HeadGamer::tVirtualKeyEvent virtualKeyEvent = {virtualKey, HeadGamer::eVirtualKeyAction::PRESS, HeadGamer::eVirtualKeyType::KEYBOARD};
    sendVirtualKeyEvent(virtualKeyEvent);
}

void KeyboardHandler::releaseKeyboardButton(const int32_t virtualKey)
{
    HeadGamer::tVirtualKeyEvent virtualKeyEvent = {virtualKey, HeadGamer::eVirtualKeyAction::RELEASE, HeadGamer::eVirtualKeyType::KEYBOARD};
    sendVirtualKeyEvent(virtualKeyEvent);
}

#ifdef Q_OS_WIN
bool KeyboardHandler::sendVirtualKeyEvent(const HeadGamer::tVirtualKeyEvent& virtualKey)
{
    INPUT input;
    const uint32_t keysCount = 1;
    fillInput(input, virtualKey);

    qDebug() << "sendVirtualKeyEvent: virtualKey = " << virtualKey.virtualKey << " action = " << (int)virtualKey.action;
    uint32_t sentKeys = SendInput(keysCount, &input, sizeof(INPUT));

    if (sentKeys != keysCount)
    {
        //OutputString(L"SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
        return false;
    }
    return true;
}

bool KeyboardHandler::sendVirtualKeyEvent(const std::vector<HeadGamer::tVirtualKeyEvent>& virtualKeys)
{
    std::shared_ptr<INPUT> inputs(fillInputsArray(virtualKeys));

    if (inputs == nullptr)
    {
        return false;
    }

    const uint32_t keysCount = virtualKeys.size();
    uint32_t sentKeys = SendInput(keysCount, inputs.get(), sizeof(INPUT));

    if (sentKeys != keysCount)
    {
        //OutputString(L"SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
        return false;
    }
    return true;
}

void KeyboardHandler::fillInput(INPUT& input, const HeadGamer::tVirtualKeyEvent& virtualKey)
{
    input.type = virtualKey.keyType == HeadGamer::eVirtualKeyType::KEYBOARD ? INPUT_KEYBOARD : INPUT_MOUSE;
    input.ki.wVk = virtualKey.virtualKey;
    if (virtualKey.action == HeadGamer::eVirtualKeyAction::RELEASE)
    {
        input.ki.dwFlags = KEYEVENTF_KEYUP;
    }
}

std::shared_ptr<INPUT> KeyboardHandler::fillInputsArray(std::vector<HeadGamer::tVirtualKeyEvent> virtualKeys)
{
    uint32_t keysCount = virtualKeys.size();
    if(keysCount < 1)
    {
        return nullptr;
    }

    std::shared_ptr<INPUT> inputs(new INPUT[keysCount]);

    for(uint32_t i = 0; i < keysCount; ++i)
    {
        fillInput(inputs.get()[i], virtualKeys[i]);
    }

    return inputs;
}
#endif // Q_OS_WIN

#ifdef Q_OS_UNIX
bool KeyboardHandler::sendVirtualKeyEvent(const HeadGamer::tVirtualKeyEvent& virtualKey)
{
    qDebug() << "sendVirtualKeyEvent: virtualKey = " << virtualKey.virtualKey << " action = " << (int)virtualKey.action;
    Display *display;
    display = XOpenDisplay(NULL);
    bool isPress = (virtualKey.action == HeadGamer::eVirtualKeyAction::PRESS);
    int res = 0;
    if(virtualKey.virtualKey >= KEY_LEFT_BUTTON || virtualKey.virtualKey <= KEY_WHEELDOWN)
    {
        res = XTestFakeButtonEvent(display, virtualKey.virtualKey, isPress, 0);
    }
    else
    {
        res = XTestFakeKeyEvent(display, virtualKey.virtualKey, isPress, 0);
    }
    XCloseDisplay(display);

    return (res != 0);
}

bool KeyboardHandler::sendVirtualKeyEvent(const std::vector<HeadGamer::tVirtualKeyEvent>& virtualKeys)
{
    for(auto virtualKey : virtualKeys)
    {
        if(!sendVirtualKeyEvent(virtualKey))
        {
            qDebug() << "sendVirtualKeyEvent: failed to send virtualKey = " << virtualKey.virtualKey << " action = " << (int)virtualKey.action;
            return false;
        }
    }
    return true;
}
#endif
