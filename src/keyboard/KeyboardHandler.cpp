#include "keyboard/KeyboardHandler.hpp"
#include <QtDebug>

static void logger_proc(unsigned int level, void *user_data, const char *format, va_list args) {
    switch (level) {
        case LOG_LEVEL_INFO:
            vfprintf(stdout, format, args);
            break;

        case LOG_LEVEL_WARN:
        case LOG_LEVEL_ERROR:
            vfprintf(stderr, format, args);
            break;
    }
}

KeyboardHandler::KeyboardHandler(QObject *parent) : QObject(parent)
{
    mKeyboardEvent = new uiohook_event();
    mKeyboardEvent->mask = 0x00;
    mKeyboardEvent->data.keyboard.keychar = CHAR_UNDEFINED;
    hook_set_logger_proc(&logger_proc, NULL);
}

KeyboardHandler::~KeyboardHandler()
{
    delete mKeyboardEvent;
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

bool KeyboardHandler::sendVirtualKeyEvent(const HeadGamer::tVirtualKeyEvent& virtualKey)
{
    qDebug() << "sendVirtualKeyEvent: virtualKey = " << virtualKey.virtualKey << " action = " << (int)virtualKey.action;
    // TODO use event_type instead of eVirtualKeyAction
    mKeyboardEvent->type = (virtualKey.action == HeadGamer::eVirtualKeyAction::PRESS) ? EVENT_KEY_PRESSED : EVENT_KEY_RELEASED;
    mKeyboardEvent->data.keyboard.keycode = virtualKey.virtualKey;
    hook_post_event(mKeyboardEvent);
    qDebug() << "sendVirtualKeyEvent: finished";
    return true;
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
