#ifndef KEYBOARDHANDLER_HPP
#define KEYBOARDHANDLER_HPP

#include "Types.hpp"

#include <QObject>
#include <vector>
#include <memory>



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

signals:

private:
    explicit KeyboardHandler(QObject *parent = nullptr);

    KeyboardHandler(KeyboardHandler const&) = delete;
    ~KeyboardHandler() {}

    KeyboardHandler& operator= (KeyboardHandler const&) = delete;

    void fillInput(INPUT& input, const HeadGamer::tVirtualKeyEvent& virtualKey);
    std::shared_ptr<INPUT> fillInputsArray(std::vector<HeadGamer::tVirtualKeyEvent> virtualKeys);

};

#endif // KEYBOARDHANDLER_HPP
