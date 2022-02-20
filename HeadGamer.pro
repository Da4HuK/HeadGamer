QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = HeadGamer

SOURCES += \
    action/ActionBase.cpp \
    action/KeyPressAction.cpp \
    action/MacroAction.cpp \
    KeyboardHandler.cpp \
    Mouse4DirectionsHandler.cpp \
    MouseActionHandler.cpp \
    MouseHookHandler.cpp \
    MouseInfo.cpp \
    Presets.cpp \
    Settings.cpp \
    Types.cpp \
    UI/ComboBoxDelegate.cpp \
    UI/DirectionButton.cpp \
    UI/DirectionWidget.cpp \
    UI/WindowActionWidget.cpp \
    UI/WindowConfigForm.cpp \
    UI/WindowConfigItem.cpp \
    Utils.cpp \
    WindowActionConfig.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    action/IAction.hpp \
    action/ActionBase.hpp \
    action/KeyPressAction.hpp \
    action/MacroAction.hpp \
    KeyboardHandler.hpp \
    MainWindow.hpp \
    Mouse4DirectionsHandler.hpp \
    MouseActionHandler.hpp \
    MouseHookHandler.hpp \
    MouseInfo.hpp \
    Presets.hpp \
    Settings.hpp \
    Types.hpp \
    UI/ComboBoxDelegate.hpp \
    UI/DirectionButton.hpp \
    UI/DirectionWidget.hpp \
    UI/WindowActionWidget.hpp \
    UI/WindowConfigForm.hpp \
    UI/WindowConfigItem.hpp \
    Utils.hpp \
    VirtualKeys.hpp \
    WindowActionConfig.hpp

FORMS += \
    UI/MainWindow.ui \
    UI/MouseInfo.ui \
    UI/WindowConfigForm.ui \
    UI/WindowConfigItem.ui

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

win32: LIBS +=  -luser32

RESOURCES += \
    resources/resources.qrc
