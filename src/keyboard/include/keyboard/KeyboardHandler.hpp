#ifndef KEYBOARDHANDLER_HPP
#define KEYBOARDHANDLER_HPP

#include "common/Types.hpp"

#include <QObject>
#include <vector>
#include <memory>

#include "uiohook.h"

class KeyboardHandler : public QObject
{
    Q_OBJECT
public:
    static KeyboardHandler& getInstance() {
            static KeyboardHandler keyboardHandler;
            return keyboardHandler;
        }

    void pressKeyboardButton(const int32_t virtualKey);
    void releaseKeyboardButton(const int32_t virtualKey);
    bool sendVirtualKeyEvent(const HeadGamer::tVirtualKeyEvent& virtualKey);
    bool sendVirtualKeyEvent(const std::vector<HeadGamer::tVirtualKeyEvent>& virtualKeys);

//Check if I need a signals
//If not => remove inheritance from QObject
signals:

private:
    explicit KeyboardHandler(QObject *parent = nullptr);

    KeyboardHandler(KeyboardHandler const&) = delete;
    virtual ~KeyboardHandler();

    KeyboardHandler& operator= (KeyboardHandler const&) = delete;

    uiohook_event* mKeyboardEvent;
};

#endif // KEYBOARDHANDLER_HPP
