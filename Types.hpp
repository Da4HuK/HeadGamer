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
    {"None", VK_NONE},

    {"A", VK_A},
    {"B", VK_B},
    {"C", VK_C},
    {"D", VK_D},
    {"E", VK_E},
    {"F", VK_F},
    {"G", VK_G},
    {"H", VK_H},
    {"I", VK_I},
    {"J", VK_J},
    {"K", VK_K},
    {"L", VK_L},
    {"M", VK_M},
    {"N", VK_N},
    {"O", VK_O},
    {"P", VK_P},
    {"Q", VK_Q},
    {"R", VK_R},
    {"S", VK_S},
    {"T", VK_T},
    {"U", VK_U},
    {"V", VK_V},
    {"W", VK_W},
    {"X", VK_X},
    {"Y", VK_Y},
    {"Z", VK_Z},

    {"1", VK_1},
    {"2", VK_2},
    {"3", VK_3},
    {"4", VK_4},
    {"5", VK_5},
    {"6", VK_6},
    {"7", VK_7},
    {"8", VK_8},
    {"9", VK_9},
    {"0", VK_0},

    {"Num Lock", VK_NUMLOCK},
    {"Numpad 1", VK_NUMPAD1},
    {"Numpad 2", VK_NUMPAD2},
    {"Numpad 3", VK_NUMPAD3},
    {"Numpad 4", VK_NUMPAD4},
    {"Numpad 5", VK_NUMPAD5},
    {"Numpad 6", VK_NUMPAD6},
    {"Numpad 7", VK_NUMPAD7},
    {"Numpad 8", VK_NUMPAD8},
    {"Numpad 9", VK_NUMPAD9},
    {"Numpad 0", VK_NUMPAD0},
    {"Numpad +", VK_ADD},
    {"Numpad -", VK_SUBTRACT},
    {"Numpad *", VK_MULTIPLY},
    {"Numpad /", VK_DIVIDE},
    {"Numpad Del.", VK_DECIMAL},

    {"F1", VK_F1},
    {"F2", VK_F2},
    {"F3", VK_F3},
    {"F4", VK_F4},
    {"F5", VK_F5},
    {"F6", VK_F6},
    {"F7", VK_F7},
    {"F8", VK_F8},
    {"F9", VK_F9},
    {"F10", VK_F10},
    {"F11", VK_F11},
    {"F12", VK_F12},

    {"Up", VK_UP},
    {"Down", VK_DOWN},
    {"Left", VK_LEFT},
    {"Right", VK_RIGHT},

    {"Left mouse button", VK_LBUTTON},
    {"Right mouse button", VK_RBUTTON},
    {"Midle mouse button", VK_MBUTTON},
    {"X1 mouse button", VK_XBUTTON1},
    {"X2 mouse button", VK_XBUTTON2},

    {"Space", VK_SPACE},
    {"Enter", VK_RETURN},
    {"Ins", VK_INSERT},
    {"Del", VK_DELETE},
    {"Backspace", VK_BACK},
    {"Home", VK_HOME},
    {"End", VK_END},
    {"Page up", VK_PRIOR},
    {"Page down", VK_NEXT},

    {"Esc", VK_ESCAPE},
    {"Shift", VK_SHIFT},
    {"Ctrl", VK_CONTROL},
    {"Alt", VK_MENU},
    {"Left Shift", VK_LSHIFT},
    {"Right Shift", VK_RSHIFT},
    {"Left Ctrl", VK_LCONTROL},
    {"Right Ctrl", VK_RCONTROL},
    {"Left Alt", VK_LMENU},
    {"Right Alt", VK_RMENU},
    {"Left Win", VK_LWIN},
    {"Right Win", VK_RWIN},
    {"Tab", VK_TAB},
    {"Caps Losk", VK_CAPITAL},
    {"Print screen", VK_SNAPSHOT},

    {";", VK_OEM_1},
    {",", VK_OEM_COMMA},
    {".", VK_OEM_PERIOD},
    {"/?", VK_OEM_2},
    {"\\|", VK_OEM_5},
    {"[{", VK_OEM_4},
    {"]}", VK_OEM_6},
    {"'\"", VK_OEM_7},
    {"`~", VK_OEM_3},
    {"-", VK_OEM_MINUS},
    {"=+", VK_OEM_PLUS},
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
