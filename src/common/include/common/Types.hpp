#ifndef TYPES_HPP
#define TYPES_HPP

//#include "keyboard/VirtualKeys.hpp"
#include "common/Utils.hpp"
#include <uiohook.h>
#include <map>
#include <vector>
#include <QJsonObject>
#include <QJsonArray>
#include <QColor>
#include <QString>

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
Q_GLOBAL_STATIC_WITH_ARGS(const QString, WINDOW_ACTION_CONFIG_LIST_STR, ("windowActionConfigList") );

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
Q_GLOBAL_STATIC_WITH_ARGS(const QString, ACTION_NONE_STR, ("None") );

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

static const int32_t MOUSE_WHEEL_UP = 0xFFE0;
static const int32_t MOUSE_WHEEL_DOWN = 0xFFE1;

static const tVirtualKeys VIRTUAL_KEYS
{
    {*(HeadGamer::ACTION_NONE_STR), VC_UNDEFINED},

    {"A", VC_A},
    {"B", VC_B},
    {"C", VC_C},
    {"D", VC_D},
    {"E", VC_E},
    {"F", VC_F},
    {"G", VC_G},
    {"H", VC_H},
    {"I", VC_I},
    {"J", VC_J},
    {"K", VC_K},
    {"L", VC_L},
    {"M", VC_M},
    {"N", VC_N},
    {"O", VC_O},
    {"P", VC_P},
    {"Q", VC_Q},
    {"R", VC_R},
    {"S", VC_S},
    {"T", VC_T},
    {"U", VC_U},
    {"V", VC_V},
    {"W", VC_W},
    {"X", VC_X},
    {"Y", VC_Y},
    {"Z", VC_Z},

    {"0", VC_0},
    {"1", VC_1},
    {"2", VC_2},
    {"3", VC_3},
    {"4", VC_4},
    {"5", VC_5},
    {"6", VC_6},
    {"7", VC_7},
    {"8", VC_8},
    {"9", VC_9},

    {"Num Lock", VC_NUM_LOCK},
    {"Numpad 1", VC_KP_1},
    {"Numpad 2", VC_KP_2},
    {"Numpad 3", VC_KP_3},
    {"Numpad 4", VC_KP_4},
    {"Numpad 5", VC_KP_5},
    {"Numpad 6", VC_KP_6},
    {"Numpad 7", VC_KP_7},
    {"Numpad 8", VC_KP_8},
    {"Numpad 9", VC_KP_9},
    {"Numpad 0", VC_KP_0},
    {"Numpad +", VC_KP_ADD},
    {"Numpad -", VC_KP_SUBTRACT},
    {"Numpad *", VC_KP_MULTIPLY},
    {"Numpad /", VC_KP_DIVIDE},
    {"Numpad Del.", VC_KP_SEPARATOR},
    {"Numpad Enter", VC_KP_ENTER},

    {"F1", VC_F1},
    {"F2", VC_F2},
    {"F3", VC_F3},
    {"F4", VC_F4},
    {"F5", VC_F5},
    {"F6", VC_F6},
    {"F7", VC_F7},
    {"F8", VC_F8},
    {"F9", VC_F9},
    {"F10", VC_F10},
    {"F11", VC_F11},
    {"F12", VC_F12},

    {"Up", VC_UP},
    {"Down", VC_DOWN},
    {"Left", VC_LEFT},
    {"Right", VC_RIGHT},

    {"Left mouse button", MOUSE_BUTTON1},
    {"Right mouse button", MOUSE_BUTTON2},
    {"Midle mouse button", MOUSE_BUTTON3},
    {"Mouse wheel up", MOUSE_WHEEL_UP},
    {"Mouse wheel down", MOUSE_WHEEL_DOWN},
    {"X1 mouse button", MOUSE_BUTTON4},
    {"X2 mouse button", MOUSE_BUTTON5},

    {"Space", VC_SPACE},
    {"Enter", VC_ENTER},
    {"Ins", VC_INSERT},
    {"Del", VC_DELETE},
    {"Backspace", VC_BACKSPACE},
    {"Home", VC_HOME},
    {"End", VC_END},
    {"Page up", VC_PAGE_UP},
    {"Page down", VC_PAGE_DOWN},

    {"Esc", VC_ESCAPE},
//    {"Shift", VC_SHIFT},
//    {"Ctrl", VC_CONTROL},
    {"Menu", VC_CONTEXT_MENU},
    {"Left Shift", VC_SHIFT_L},
    {"Right Shift", VC_SHIFT_R},
    {"Left Ctrl", VC_CONTROL_L},
    {"Right Ctrl", VC_CONTROL_R},
    {"Left Alt", VC_ALT_L},
    {"Right Alt", VC_ALT_R},
    {"Left Win", VC_META_L},
    {"Right Win", VC_META_R},
    {"Tab", VC_TAB},
    {"Caps Losk", VC_CAPS_LOCK},
    {"Print screen", VC_PRINTSCREEN},

    {";", VC_SEMICOLON},
    {",", VC_COMMA},
    {".", VC_PERIOD},
    {"/?", VC_SLASH},
    {"\\", VC_BACK_SLASH},
    {"'\"", VC_QUOTE},
    {"<>|", VC_LESSER_GREATER},
    {"[{", VC_OPEN_BRACKET},
    {"]}", VC_CLOSE_BRACKET},
    {"`~", VC_BACKQUOTE},
    {"-", VC_MINUS},
    {"=+", VC_EQUALS},
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
