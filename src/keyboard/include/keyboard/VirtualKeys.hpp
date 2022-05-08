#ifndef VIRTUALKEYS_HPP
#define VIRTUALKEYS_HPP

#include <stdint.h>
#include <QtGlobal>

#ifdef Q_OS_WIN
#include <windows.h>
#include <WinUser.h>

static const int32_t VK_NONE = 0x00;
//VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
static const int32_t VK_0 = 0x30;
static const int32_t VK_1 = 0x31;
static const int32_t VK_2 = 0x32;
static const int32_t VK_3 = 0x33;
static const int32_t VK_4 = 0x34;
static const int32_t VK_5 = 0x35;
static const int32_t VK_6 = 0x36;
static const int32_t VK_7 = 0x37;
static const int32_t VK_8 = 0x38;
static const int32_t VK_9 = 0x39;

//VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
static const int32_t VK_A = 0x41;
static const int32_t VK_B = 0x42;
static const int32_t VK_C = 0x43;
static const int32_t VK_D = 0x44;
static const int32_t VK_E = 0x45;
static const int32_t VK_F = 0x46;
static const int32_t VK_G = 0x47;
static const int32_t VK_H = 0x48;
static const int32_t VK_I = 0x49;
static const int32_t VK_J = 0x4A;
static const int32_t VK_K = 0x4B;
static const int32_t VK_L = 0x4C;
static const int32_t VK_M = 0x4D;
static const int32_t VK_N = 0x4E;
static const int32_t VK_O = 0x4F;
static const int32_t VK_P = 0x50;
static const int32_t VK_Q = 0x51;
static const int32_t VK_R = 0x52;
static const int32_t VK_S = 0x53;
static const int32_t VK_T = 0x54;
static const int32_t VK_U = 0x55;
static const int32_t VK_V = 0x56;
static const int32_t VK_W = 0x57;
static const int32_t VK_X = 0x58;
static const int32_t VK_Y = 0x59;
static const int32_t VK_Z = 0x5A;
#endif // Q_OS_WIN

#ifdef Q_OS_UNIX
//enum Keys
//{
//    VK_NONE = 0,

//    VK_A,
//    VK_B,
//    VK_C,
//    VK_D,
//    VK_E,
//    VK_F,
//    VK_G,
//    VK_H,
//    VK_I,
//    VK_J,
//    VK_K,
//    VK_L,
//    VK_M,
//    VK_N,
//    VK_O,
//    VK_P,
//    VK_Q,
//    VK_R,
//    VK_S,
//    VK_T,
//    VK_U,
//    VK_V,
//    VK_W,
//    VK_X,
//    VK_Y,
//    VK_Z,

//    VK_1,
//    VK_2,
//    VK_3,
//    VK_4,
//    VK_5,
//    VK_6,
//    VK_7,
//    VK_8,
//    VK_9,
//    VK_0,

//    VK_NUMLOCK,
//    VK_NUMPAD1,
//    VK_NUMPAD2,
//    VK_NUMPAD3,
//    VK_NUMPAD4,
//    VK_NUMPAD5,
//    VK_NUMPAD6,
//    VK_NUMPAD7,
//    VK_NUMPAD8,
//    VK_NUMPAD9,
//    VK_NUMPAD0,
//    VK_ADD,
//    VK_SUBTRACT,
//    VK_MULTIPLY,
//    VK_DIVIDE,
//    VK_DECIMAL,

//    VK_F1,
//    VK_F2,
//    VK_F3,
//    VK_F4,
//    VK_F5,
//    VK_F6,
//    VK_F7,
//    VK_F8,
//    VK_F9,
//    VK_F10,
//    VK_F11,
//    VK_F12,

//    VK_UP,
//    VK_DOWN,
//    VK_LEFT,
//    VK_RIGHT,

//    VK_LBUTTON,
//    VK_RBUTTON,
//    VK_MBUTTON,
//    VK_XBUTTON1,
//    VK_XBUTTON2,

//    VK_SPACE,
//    VK_RETURN,
//    VK_INSERT,
//    VK_DELETE,
//    VK_BACK,
//    VK_HOME,
//    VK_END,
//    VK_PRIOR,
//    VK_NEXT,

//    VK_ESCAPE,
//    VK_SHIFT,
//    VK_CONTROL,
//    VK_MENU,
//    VK_LSHIFT,
//    VK_RSHIFT,
//    VK_LCONTROL,
//    VK_RCONTROL,
//    VK_LMENU,
//    VK_RMENU,
//    VK_LWIN,
//    VK_RWIN,
//    VK_TAB,
//    VK_CAPITAL,
//    VK_SNAPSHOT,

//    VK_OEM_1,
//    VK_OEM_COMMA,
//    VK_OEM_PERIOD,
//    VK_OEM_2,
//    VK_OEM_5,
//    VK_OEM_4,
//    VK_OEM_6,
//    VK_OEM_7,
//    VK_OEM_3,
//    VK_OEM_MINUS,
//    VK_OEM_PLUS,
//};

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>

#undef Bool
#undef CursorShape
#undef Expose
#undef KeyPress
#undef KeyRelease
#undef FocusIn
#undef FocusOut
#undef FontChange
#undef None
#undef Status
#undef Unsorted

static const int32_t KEY_NONE = 0;
////////Alphabet chars////////////////
static const int32_t KEY_A = 38;
static const int32_t KEY_B = 56;
static const int32_t KEY_C = 54;
static const int32_t KEY_D = 40;
static const int32_t KEY_E = 26;
static const int32_t KEY_F = 41;
static const int32_t KEY_G = 42;
static const int32_t KEY_H = 43;
static const int32_t KEY_I = 31;
static const int32_t KEY_J = 44;
static const int32_t KEY_K = 45;
static const int32_t KEY_L = 46;
static const int32_t KEY_M = 58;
static const int32_t KEY_N = 57;
static const int32_t KEY_O = 32;
static const int32_t KEY_P = 33;
static const int32_t KEY_Q = 24;
static const int32_t KEY_R = 27;
static const int32_t KEY_S = 39;
static const int32_t KEY_T = 28;
static const int32_t KEY_U = 30;
static const int32_t KEY_V = 55;
static const int32_t KEY_W = 25;
static const int32_t KEY_X = 53;
static const int32_t KEY_Y = 29;
static const int32_t KEY_Z = 52;

//////////Digits//////////////
static const int32_t KEY_0 = 19;
static const int32_t KEY_1 = 10;
static const int32_t KEY_2 = 11;
static const int32_t KEY_3 = 12;
static const int32_t KEY_4 = 13;
static const int32_t KEY_5 = 14;
static const int32_t KEY_6 = 15;
static const int32_t KEY_7 = 16;
static const int32_t KEY_8 = 17;
static const int32_t KEY_9 = 18;

//////NUM Pad//////////
static const int32_t KEY_NUM_LOCK = 77;
static const int32_t KEY_NUMPAD_0 = 90;
static const int32_t KEY_NUMPAD_1 = 87;
static const int32_t KEY_NUMPAD_2 = 88;
static const int32_t KEY_NUMPAD_3 = 89;
static const int32_t KEY_NUMPAD_4 = 83;
static const int32_t KEY_NUMPAD_5 = 84;
static const int32_t KEY_NUMPAD_6 = 85;
static const int32_t KEY_NUMPAD_7 = 79;
static const int32_t KEY_NUMPAD_8 = 80;
static const int32_t KEY_NUMPAD_9 = 81;
static const int32_t KEY_NUMPAD_DIVIDE = 106;
static const int32_t KEY_NUMPAD_MULTIPLY = 63;
static const int32_t KEY_NUMPAD_SUBTRACT = 82;
static const int32_t KEY_NUMPAD_ADD = 86;
static const int32_t KEY_NUMPAD_DECIMAL = 91;
static const int32_t KEY_NUMPAD_ENTER = 104;

//////////F1-F12/////////////////
static const int32_t KEY_F1 = 67;
static const int32_t KEY_F2 = 68;
static const int32_t KEY_F3 = 69;
static const int32_t KEY_F4 = 70;
static const int32_t KEY_F5 = 71;
static const int32_t KEY_F6 = 72;
static const int32_t KEY_F7 = 73;
static const int32_t KEY_F8 = 74;
static const int32_t KEY_F9 = 75;
static const int32_t KEY_F10 = 76;
static const int32_t KEY_F11 = 95;
static const int32_t KEY_F12 = 96;

//////////Arrows////////////
static const int32_t KEY_UP = 111;
static const int32_t KEY_LEFT = 113;
static const int32_t KEY_DOWN = 116;
static const int32_t KEY_RIGHT = 114;

///////////Mouse bottons//////////////
static const int32_t KEY_LEFT_BUTTON = Button1;
static const int32_t KEY_MIDLE_BUTTON = Button2;
static const int32_t KEY_RIGHT_BUTTON = Button3;
static const int32_t KEY_WHEELUP = Button4;
static const int32_t KEY_WHEELDOWN = Button5;

//////////Special////////////////
static const int32_t KEY_SPACE = 65;
static const int32_t KEY_SHIFT_L = 50;
static const int32_t KEY_SHIFT_R = 62;
static const int32_t KEY_CONTROL_L = 37;
static const int32_t KEY_CONTROL_R = 105;
static const int32_t KEY_SUPER_L = 133;
static const int32_t KEY_SUPER_R = 134;
static const int32_t KEY_ALT_L = 64;
static const int32_t KEY_ALT_R = 108;
static const int32_t KEY_MENU = 135;
static const int32_t KEY_INSERT = 118;
static const int32_t KEY_HOME = 110;
static const int32_t KEY_PRIOR = 112;
static const int32_t KEY_DELETE = 119;
static const int32_t KEY_END = 115;
static const int32_t KEY_NEXT = 117;
static const int32_t KEY_RETURN = 36;
static const int32_t KEY_CAPS_LOCK = 66;
static const int32_t KEY_BACKSPACE = 22;
static const int32_t KEY_TAB = 23;
static const int32_t KEY_ESCAPE = 9;
static const int32_t KEY_SCROLL_LOCK = 78;
static const int32_t KEY_PAUSE = 127;

/////Signs//////////////////
static const int32_t KEY_MINUS = 20;
static const int32_t KEY_EQUAL = 21;
static const int32_t KEY_BRACKETLEFT = 34;
static const int32_t KEY_BRACKETRIGHT = 35;
static const int32_t KEY_SEMICOLON = 47;
static const int32_t KEY_APOSTROPHE = 48;
static const int32_t KEY_BACKSLASH = 51;
static const int32_t KEY_INTERNATIONAL = 94;  // /|
static const int32_t KEY_COMMA = 59;
static const int32_t KEY_PERIOD = 60;
static const int32_t KEY_SLASH = 61;
static const int32_t KEY_GRAVE = 49;

#endif //Q_OS_UNIX

#endif // VIRTUALKEYS_HPP
