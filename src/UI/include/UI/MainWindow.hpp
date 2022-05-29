#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QStandardItemModel>

#include "settings/Settings.hpp"
#include "settings/Presets.hpp"
//#include "Settings.hpp"
//#include "Presets.hpp"
#include "MouseInfo.hpp"
#include "mouse/Mouse4DirectionsHandler.hpp"
#include "mouse/MouseActionHandler.hpp"
#include "WindowActionWidget.hpp"
#include "WindowConfigForm.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QComboBox;
class HookHandler;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

private slots:
    void onPushButtonAddProfilePressed();
    void onPushButtonCopyProfilePressed();
    void onPushButtonRenameProfilePressed();
    void onPushButtonSaveProfilePressed();
    void onPushButtonDeleteProfilePressed();

    void onPushButtonAddPresetPressed();
    void onPushButtonCopyPresetPressed();
    void onPushButtonRenamePresetPressed();
    void onPushButtonSavePresetPressed();
    void onPushButtonDeletePresetPressed();

    void onPushButtonStartPressed();
    void onPushButtonClosePressed();
    void onPushButtonWindowsSettingPressed();

    void onComboBoxButtonsProfilesCurrentTextChanged(const QString& text);
    void onComboBoxButtonsPresetCurrentTextChanged(const QString& text);
    void onComboBoxWindowsSettingsTextChanged(const QString& text);

private:
    void init();
    void createSettingsDirectories();
    void createDirectory(const QString& path);
    void readProfilesList(const QString& path);
    void readProfileFile(const QString& fileName, const tSettingsPtr& settings);
    void readPresetsList(const QString& path);
    void readPresetFile(const QString& fileName, const tPresetPtr& presets);
    void initProfileSettingsControls(const tSettingsPtr& settings);
    void initPresetControls(tContsPresetPtr& presets);
    void fillSettings(tSettingsPtr& settings);
    void fillPresets(tPresetPtr& presets);
    HeadGamer::eMode getMode();
    QString getPresetName();
    HeadGamer::eDirectionsCount getDirectionsCount();
    HeadGamer::eButtonPressType getButtonPressType();
    int32_t getTriggerThreshold();
    int32_t getButtonPressTimeOut();
    tActionPtr getPreset(HeadGamer::eDirection direction);
    tActionPtr getPreset(HeadGamer::eMouseButton mouseButton);
    tActionPtr getPreset(const QComboBox* combobox);

    //For grouped compobox
    //Use it for fill every combobox
    void fillComboboxes();

    Ui::MainWindow *ui;
    std::shared_ptr<HookHandler> mHookHandler;
    std::shared_ptr<Mouse4DirectionsHandler> mMouseDirectionHandler;
    std::shared_ptr<MouseActionHandler> mMouseActionHandler;
    tPresetPtr mPresets;

    std::shared_ptr<WindowActionWidget> mWindowAction;
    std::shared_ptr<WindowConfigForm> mWindowConfigForm;


};
#endif // MAINWINDOW_HPP
