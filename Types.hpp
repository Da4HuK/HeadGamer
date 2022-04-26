#ifndef TYPES_HPP
#define TYPES_HPP

#include "VirtualKeys.hpp"
#include "Utils.hpp"
#include <map>
#include <vector>
#include <QJsonObject>
#include <QJsonArray>
#include <QColor>

namespace HeadGamer
{
using tActionsVector = std::vector<tActionPtr>;

enum class eMode
{
    UNDEFINED,
    MODE_1,
    MODE_2
};

QString modeToJson(const eMode mode);
eMode jsonToMode(const QJsonObject& json);

enum class eDirectionsCount
{
    FOUR,
    EIGHT
};

int8_t directionsCountToJson(const eDirectionsCount directionsCount);
eDirectionsCount jsonToDirectionsCount(const QJsonObject& json);

int32_t jsonToInt32(const QJsonObject& json, const QString& parameterName, const int32_t defaultValue = 0);
QString jsonToString(const QJsonObject& json, const QString& parameterName, const QString& defaultValue = "");

bool isJsonObjectPresent(const QString& name, const QJsonObject& json);
bool isJsonArrayPresent(const QString& name, const QJsonObject& json);

enum class eButtonPressType
{
    UNDEFINED,
    HOLD,
    HOLD_FOR_TIME
};

QString buttonPressTypeToJson(const eButtonPressType buttonPressType);
eButtonPressType jsonToButtonPressType(const QJsonObject& json);

enum class eDirection
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

QString directionToJson(const eDirection direction);

enum class eMouseButton
{
    LEFT,
    RIGHT,
    MIDLE
};

enum class eVirtualKeyAction
{
    PRESS,
    RELEASE
};

enum class eVirtualKeyType
{
    KEYBOARD,
    MOUSE
};

enum class eActionType
{
    KEY_PRESS_ACTION,
    MACRO_ACTION,
    SWITCH_PRESET_ACTION
};

//const QString KEY_PRESS_ACTION_STR = {"KeyPressAction"};
//const QString MACRO_ACTION_STR = {"MacroAction"};
//const QString SWITCH_PRESET_ACTION_STR = {"SwitchPresetAction"};

//Json fields names
Q_GLOBAL_STATIC_WITH_ARGS(const QString, TYPE_STR, ("type") );
Q_GLOBAL_STATIC_WITH_ARGS(const QString, KEY_STR, ("key") );
Q_GLOBAL_STATIC_WITH_ARGS(const QString, MACROS_STR, ("macros") );
Q_GLOBAL_STATIC_WITH_ARGS(const QString, PATH_TO_ACTION_STR, ("path") );

//Action names
Q_GLOBAL_STATIC_WITH_ARGS(const QString, KEY_PRESS_ACTION_STR, ("KeyPressAction") );
Q_GLOBAL_STATIC_WITH_ARGS(const QString, MACRO_ACTION_STR, ("MacroAction") );
Q_GLOBAL_STATIC_WITH_ARGS(const QString, SWITCH_PRESET_ACTION_STR, ("SwitchPresetAction") );

//WindowActionConfig fieldnames
Q_GLOBAL_STATIC_WITH_ARGS(const QString, WINDOW_ACTION_NAME_STR, ("name") );
Q_GLOBAL_STATIC_WITH_ARGS(const QString, WINDOW_WIDTH_STR, ("width") );
Q_GLOBAL_STATIC_WITH_ARGS(const QString, WINDOW_HEIGHT_STR, ("height") );
Q_GLOBAL_STATIC_WITH_ARGS(const QString, WINDOW_POSITION_X_STR, ("x") );
Q_GLOBAL_STATIC_WITH_ARGS(const QString, WINDOW_POSITION_Y_STR, ("y") );
Q_GLOBAL_STATIC_WITH_ARGS(const QString, WINDOW_COLOR_STR, ("color") );
Q_GLOBAL_STATIC_WITH_ARGS(const QString, WINDOW_COLOR_R_STR, ("R") );
Q_GLOBAL_STATIC_WITH_ARGS(const QString, WINDOW_COLOR_G_STR, ("G") );
Q_GLOBAL_STATIC_WITH_ARGS(const QString, WINDOW_COLOR_B_STR, ("B") );
Q_GLOBAL_STATIC_WITH_ARGS(const QString, WINDOW_COLOR_ALPHA_STR, ("ALPHA") );

Q_GLOBAL_STATIC_WITH_ARGS(const QString, ACTION_STR, ("action") );

//Key: direction, value: button/action name
using tMouseDirectionBinding = std::map<eDirection, QString>;

//Key: direction, value: button/action name
using tMouseButtonBinding = std::map<eMouseButton, QString>;

using tButtonsPresets = std::vector<QString>;

struct tButton
{
    QString buttonStr;
    int32_t virtualKey;
};

//Key: Button name, value: Virtual key code
using tVirtualKeys = std::vector<tButton>;
int32_t findVirtualKey(const QString& buttonStr);

static const tVirtualKeys VIRTUAL_KEYS
{
    {"None", KEY_NONE},

    {"A", KEY_A},
    {"B", KEY_B},
    {"C", KEY_C},
    {"D", KEY_D},
    {"E", KEY_E},
    {"F", KEY_F},
    {"G", KEY_G},
    {"H", KEY_H},
    {"I", KEY_I},
    {"J", KEY_J},
    {"K", KEY_K},
    {"L", KEY_L},
    {"M", KEY_M},
    {"N", KEY_N},
    {"O", KEY_O},
    {"P", KEY_P},
    {"Q", KEY_Q},
    {"R", KEY_R},
    {"S", KEY_S},
    {"T", KEY_T},
    {"U", KEY_U},
    {"V", KEY_V},
    {"W", KEY_W},
    {"X", KEY_X},
    {"Y", KEY_Y},
    {"Z", KEY_Z},

    {"1", KEY_1},
    {"2", KEY_2},
    {"3", KEY_3},
    {"4", KEY_4},
    {"5", KEY_5},
    {"6", KEY_6},
    {"7", KEY_7},
    {"8", KEY_8},
    {"9", KEY_9},
    {"0", KEY_0},

    {"Num Lock", KEY_NUM_LOCK},
    {"Numpad 1", KEY_NUMPAD_1},
    {"Numpad 2", KEY_NUMPAD_2},
    {"Numpad 3", KEY_NUMPAD_3},
    {"Numpad 4", KEY_NUMPAD_4},
    {"Numpad 5", KEY_NUMPAD_5},
    {"Numpad 6", KEY_NUMPAD_6},
    {"Numpad 7", KEY_NUMPAD_7},
    {"Numpad 8", KEY_NUMPAD_8},
    {"Numpad 9", KEY_NUMPAD_9},
    {"Numpad 0", KEY_NUMPAD_0},
    {"Numpad +", KEY_NUMPAD_ADD},
    {"Numpad -", KEY_NUMPAD_SUBTRACT},
    {"Numpad *", KEY_NUMPAD_MULTIPLY},
    {"Numpad /", KEY_NUMPAD_DIVIDE},
    {"Numpad Del.", KEY_NUMPAD_DECIMAL},

    {"F1", KEY_F1},
    {"F2", KEY_F2},
    {"F3", KEY_F3},
    {"F4", KEY_F4},
    {"F5", KEY_F5},
    {"F6", KEY_F6},
    {"F7", KEY_F7},
    {"F8", KEY_F8},
    {"F9", KEY_F9},
    {"F10", KEY_F10},
    {"F11", KEY_F11},
    {"F12", KEY_F12},

    {"Up", KEY_UP},
    {"Down", KEY_DOWN},
    {"Left", KEY_LEFT},
    {"Right", KEY_RIGHT},

    {"Left mouse button", KEY_LEFT_BUTTON},
    {"Right mouse button", KEY_RIGHT_BUTTON},
    {"Midle mouse button", KEY_MIDLE_BUTTON},
    {"Mouse wheel up", KEY_WHEELUP},
    {"Mouse wheel down", KEY_WHEELDOWN},
//    {"X1 mouse button", KEY_XBUTTON1},
//    {"X2 mouse button", KEY_XBUTTON2},

    {"Space", KEY_SPACE},
    {"Enter", KEY_RETURN},
    {"Ins", KEY_INSERT},
    {"Del", KEY_DELETE},
    {"Backspace", KEY_BACKSPACE},
    {"Home", KEY_HOME},
    {"End", KEY_END},
    {"Page up", KEY_PRIOR},
    {"Page down", KEY_NEXT},

    {"Esc", KEY_ESCAPE},
//    {"Shift", KEY_SHIFT},
//    {"Ctrl", KEY_CONTROL},
    {"Menu", KEY_MENU},
    {"Left Shift", KEY_SHIFT_L},
    {"Right Shift", KEY_SHIFT_R},
    {"Left Ctrl", KEY_CONTROL_L},
    {"Right Ctrl", KEY_CONTROL_R},
    {"Left Alt", KEY_ALT_L},
    {"Right Alt", KEY_ALT_R},
    {"Left Win", KEY_SUPER_L},
    {"Right Win", KEY_SUPER_R},
    {"Tab", KEY_TAB},
    {"Caps Losk", KEY_CAPS_LOCK},
//    {"Print screen", KEY_SNAPSHOT},

    {";", KEY_SEMICOLON},
    {",", KEY_COMMA},
    {".", KEY_PERIOD},
    {"/?", KEY_SLASH},
    {"\\", KEY_BACKSLASH},
    {"'\"", KEY_APOSTROPHE},
    {"\\|", KEY_INTERNATIONAL},
    {"[{", KEY_BRACKETLEFT},
    {"]}", KEY_BRACKETRIGHT},
    {"`~", KEY_GRAVE},
    {"-", KEY_MINUS},
    {"=+", KEY_EQUAL},
};

struct tVirtualKeyEvent
{
    int32_t virtualKey;
    eVirtualKeyAction action;
    eVirtualKeyType keyType;

};

QJsonObject colorToJson(const QColor& color);
QColor jsonToColor(const QJsonObject& json);

QJsonArray actionsVectorToJson(const tActionsVector& vector);
tActionsVector jsonToActionsVector(const QJsonArray& array);

}


#endif // TYPES_HPP
