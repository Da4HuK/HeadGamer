QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = HeadGamer

INCLUDEPATH += \
    src/action/include \
    src/common/include \
    src/keyboard/include \
    src/mouse/include \
    src/settings/include \
    src/UI/include

SOURCES += \
    src/main.cpp \
    src/action/ActionBase.cpp \
    src/action/KeyPressAction.cpp \
    src/action/MacroAction.cpp \
    src/action/WindowActionConfig.cpp \
    src/common/Types.cpp \
    src/common/Utils.cpp \
    src/keyboard/KeyboardHandler.cpp \
    src/mouse/Mouse4DirectionsHandler.cpp \
    src/mouse/MouseActionHandler.cpp \
    src/mouse/MouseHookHandler.cpp \
    src/settings/Presets.cpp \
    src/settings/Settings.cpp \
    src/UI/MouseInfo.cpp \
    src/UI/ComboBoxDelegate.cpp \
    src/UI/DirectionButton.cpp \
    src/UI/DirectionWidget.cpp \
    src/UI/WindowActionWidget.cpp \
    src/UI/WindowConfigForm.cpp \
    src/UI/WindowConfigItem.cpp \
    src/UI/MainWindow.cpp

HEADERS += \
    src/action/include/action/IAction.hpp \
    src/action/include/action/ActionBase.hpp \
    src/action/include/action/KeyPressAction.hpp \
    src/action/include/action/MacroAction.hpp \
    src/action/include/action/WindowActionConfig.hpp \
    src/common/include/common/Types.hpp \
    src/common/include/common/Utils.hpp \
    src/keyboard/include/keyboard/VirtualKeys.hpp \
    src/keyboard/include/keyboard/KeyboardHandler.hpp \
    src/mouse/include/mouse/Mouse4DirectionsHandler.hpp \
    src/mouse/include/mouse/MouseActionHandler.hpp \
    src/mouse/include/mouse/MouseHookHandler.hpp \
    src/settings/include/settings/Presets.hpp \
    src/settings/include/settings/Settings.hpp \
    src/UI/include/UI/MouseInfo.hpp \
    src/UI/include/UI/MainWindow.hpp \
    src/UI/include/UI/ComboBoxDelegate.hpp \
    src/UI/include/UI/DirectionButton.hpp \
    src/UI/include/UI/DirectionWidget.hpp \
    src/UI/include/UI/WindowActionWidget.hpp \
    src/UI/include/UI/WindowConfigForm.hpp \
    src/UI/include/UI/WindowConfigItem.hpp

FORMS += \
    src/UI/MainWindow.ui \
    src/UI/MouseInfo.ui \
    src/UI/WindowConfigForm.ui \
    src/UI/WindowConfigItem.ui

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

unix {
    LIBS +=  -lX11 -lXtst
}

win32 {
    LIBS +=  -luser32
}

RESOURCES += \
    src/resources/resources.qrc
