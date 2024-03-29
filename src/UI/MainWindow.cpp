#include "UI/MainWindow.hpp"
#include "ui_MainWindow.h"
#include "hook/HookHandler.hpp"
#include "common/Utils.hpp"
#include "action/StopEvent.hpp"

#include <QFileDialog>
#include <QDirIterator>
#include <QPalette>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mHookHandler(nullptr)
    , mMouseDirectionHandler(nullptr)
    , mMouseActionHandler(nullptr)
    , mPresets(std::make_shared<Presets>())
    , mWindowActionWidgetList()
    , mWindowActionConfigList(nullptr)
    , mWindowConfigForm(nullptr)
    , mIsInitialized(false)
    , mIsProfileChanged(false)
    , mIsPresetChanged(false)
{
    ui->setupUi(this);

    qDebug() << "MainWindow()";
    init();
    connect(&StopEvent::getInstance(), &StopEvent::stopEmulation, this, &MainWindow::onStopEvent);
}

MainWindow::~MainWindow()
{
    qDebug() << "~MainWindow()";
    mWindowConfigForm.reset();
    mHookHandler->stop();
    delete ui;
    qDebug() << "~MainWindow() finished";
}

void MainWindow::onPushButtonCreateProfilePressed()
{
    QString fileName = Utils::createFile("Create profile file", Settings::PROFILE_DIR, tr("Profile files (*.json *.JSON)"));
    readProfilesList(Settings::PROFILE_DIR);
    Utils::setActiveComboboxElementByName(ui->comboBoxProfiles, Utils::getFileName(fileName));
}

void MainWindow::onPushButtonCopyProfilePressed()
{

}

void MainWindow::onPushButtonRenameProfilePressed()
{

}

void MainWindow::onPushButtonSaveProfilePressed()
{
    tSettingsPtr settings = std::make_shared<Settings>();
    fillSettings(settings);
    try
    {
        QString fileName =  Settings::PROFILE_DIR + "/" + Utils::getFileNameFromCombobox(ui->comboBoxProfiles);
        Utils::writeFile(fileName, settings);
    }
    catch (std::exception ex)
    {
        qDebug() << ex.what();
    }
}

void MainWindow::onPushButtonDeleteProfilePressed()
{

}

void MainWindow::onPushButtonCreatePresetPressed()
{
    QString fileName = Utils::createFile("Create presets file", Settings::PRESET_DIR, tr("Presets files (*.json *.JSON)"));
    readPresetsList(Settings::PRESET_DIR);
    Utils::setActiveComboboxElementByName(ui->comboBoxButtonsPreset, Utils::getFileName(fileName));
}

void MainWindow::onPushButtonCopyPresetPressed()
{

}

void MainWindow::onPushButtonRenamePresetPressed()
{

}

void MainWindow::onPushButtonSavePresetPressed()
{
    fillPresets(mPresets);
    try
    {
        QString fileName =  Settings::PRESET_DIR + "/" + Utils::getFileNameFromCombobox(ui->comboBoxButtonsPreset);
        Utils::writeFile(fileName, mPresets);
    }
    catch (std::exception ex)
    {
        qDebug() << ex.what();
    }
}

void MainWindow::onPushButtonDeletePresetPressed()
{

}

void MainWindow::onPushButtonStartPressed()
{
    this->hide();
    fillWindowActionWidgetList();
    showAllWindowActionWidgets();

    if(mMouseDirectionHandler == nullptr)
    {
        mMouseDirectionHandler = std::make_shared<Mouse4DirectionsHandler>(mHookHandler);
        fillPresets(mPresets);
        mMouseActionHandler = std::make_shared<MouseActionHandler>(mPresets, mMouseDirectionHandler);
    }
    mMouseDirectionHandler->start();
}

void MainWindow::onPushButtonClosePressed()
{
    if(mMouseDirectionHandler != nullptr)
    {
        mMouseDirectionHandler->stop();
    }
    mWindowActionWidgetList.clear();
    this->close();
}

void MainWindow::onPushButtonWindowsSettingPressed()
{
    if(mWindowConfigForm == nullptr)
    {
        mWindowConfigForm = std::make_shared<WindowConfigForm>(this);
    }
    mWindowConfigForm->show();
}

void MainWindow::onComboBoxButtonsProfilesCurrentTextChanged(const QString& text)
{
    if(text.isEmpty() == false)
    {
        tSettingsPtr settings = std::make_shared<Settings>();
        readProfileFile(text, settings);
        initProfileSettingsControls(settings);
    }
}

void MainWindow::onComboBoxButtonsPresetCurrentTextChanged(const QString& text)
{
    if(mIsInitialized && text.isEmpty() == false)
    {
        readPresetFile(text, mPresets);
        initPresetControls(mPresets);
        mIsPresetChanged = true;
        Utils::markSettingsComboboxChanged(ui->comboBoxProfiles);
    }
}

void MainWindow::onComboBoxWindowsSettingsTextChanged(const QString& text)
{
    if(mIsInitialized && text.isEmpty() == false)
    {
        // TODO read dialog window exit code to check if window config changed
        Utils::markSettingsComboboxChanged(ui->comboBoxProfiles);
    }
}

void MainWindow::onStopEvent()
{
    qDebug() << "onStopEvent received";
    mHookHandler->stop();
    if(mMouseDirectionHandler != nullptr)
    {
        mMouseDirectionHandler->stop();
    }

    hideAllWindowActionWidgets();

    this->show();
}

void MainWindow::init()
{
    fillComboboxes();
    createSettingsDirectories();
    readProfilesList(Settings::PROFILE_DIR);
    readPresetsList(Settings::PRESET_DIR);
    readWindowConfigsList(Settings::WINDOW_DIR);

    mHookHandler = std::make_shared<HookHandler>();
    mWindowActionConfigList = std::make_shared<WindowActionConfigList>();
    mIsInitialized = true;
}

void MainWindow::createSettingsDirectories()
{
    createDirectory(Settings::PROFILE_DIR);
    createDirectory(Settings::PRESET_DIR);
    createDirectory(Settings::SCRIPT_DIR);
    createDirectory(Settings::WINDOW_DIR);
}

void MainWindow::createDirectory(const QString& path)
{
    QDir dir("");
    if(dir.exists(path) == false)
    {
        dir.mkpath(path);
    }
}

void MainWindow::readProfilesList(const QString& path)
{
    Utils::fillComboboxWithJsonFileNames(ui->comboBoxProfiles, path);
}

void MainWindow::readProfileFile(const QString& fileName, const tSettingsPtr& settings)
{
    QString profileFilePath = Settings::PROFILE_DIR + "/" + fileName;
    Utils::readFile(profileFilePath, settings);
}

void MainWindow::readPresetsList(const QString& path)
{
    Utils::fillComboboxWithJsonFileNames(ui->comboBoxButtonsPreset, path);
}

void MainWindow::readPresetFile(const QString& fileName, const tPresetPtr& presets)
{
    QString presetFilePath = Settings::PRESET_DIR + "/" + fileName;
    Utils::readFile(presetFilePath, presets);
}

void MainWindow::readWindowConfigsList(const QString& path)
{
    ui->comboBoxWindowsSettings->addItem(*(HeadGamer::ACTION_NONE_STR));
    Utils::fillComboboxWithJsonFileNames(ui->comboBoxWindowsSettings, path);
}

void MainWindow::initProfileSettingsControls(const tSettingsPtr& settings)
{
    ui->comboBoxButtonsPreset->setCurrentText(settings->getPresetName());
    ui->comboBoxDirectionsCount->setCurrentText(
                (settings->getDirectionsCount() == HeadGamer::eDirectionsCount::FOUR) ? "4" : "8");
    ui->spinBoxTriggerThreshold->setValue(settings->getTriggerThreshold());
    ui->spinBoxButtonPressTimeout->setValue(settings->getButtonPressTimeOut());

    switch(settings->getMode())
    {
    case HeadGamer::eMode::MODE_1:
        ui->radioButtonMode1->setChecked(true);
        break;
    case HeadGamer::eMode::MODE_2:
        ui->radioButtonMode2->setChecked(true);
        break;
    case HeadGamer::eMode::UNDEFINED:
    default:
        ui->radioButtonMode1->setChecked(false);
        ui->radioButtonMode2->setChecked(false);
        break;
    }

    switch(settings->getButtonPressType())
    {
        case HeadGamer::eButtonPressType::HOLD:
            ui->radioButtonPressType_Hold->setChecked(true);
            break;
        case HeadGamer::eButtonPressType::HOLD_FOR_TIME:
            ui->radioButtonPressType_HoldForTime->setChecked(true);
            break;
        case HeadGamer::eButtonPressType::UNDEFINED:
            ui->radioButtonPressType_Hold->setChecked(false);
            ui->radioButtonPressType_HoldForTime->setChecked(false);
        default:
            break;
    }
}

void MainWindow::initPresetControls(tConstPresetPtr& presets)
{
    auto initCombobox = [] (QComboBox* combobox, tConstActionPtr action)
    {
        if(action == nullptr)
        {
            combobox->setCurrentText(*(HeadGamer::ACTION_NONE_STR));
        }
        else
        {
            combobox->setCurrentText(action->getName());
        }
    };

    initCombobox(ui->comboBoxButtonUp, presets->getUpAction());
    initCombobox(ui->comboBoxButtonDown, presets->getDownAction());
    initCombobox(ui->comboBoxButtonLeft, presets->getLeftAction());
    initCombobox(ui->comboBoxButtonRight, presets->getRightAction());

    initCombobox(ui->comboBoxLeftMouse, presets->getLeftMouseAction());
    initCombobox(ui->comboBoxRightMouse, presets->getRightMouseAction());
    initCombobox(ui->comboBoxMidleMouse, presets->getMiddleMouseAction());
}

void MainWindow::fillSettings(tSettingsPtr& settings)
{
    settings->setMode(getMode());
    settings->setPresetName(getPresetName());
    //MODE_1
    settings->setDirectionsCount(getDirectionsCount());
    settings->setButtonPressType(getButtonPressType());
    settings->setTriggerThreshold(getTriggerThreshold());
    settings->setButtonPressTimeOut(getButtonPressTimeOut());
}

void MainWindow::fillPresets(tPresetPtr& presets)
{
    presets->setUpAction(getPreset(HeadGamer::eDirection::UP));
    presets->setDownAction(getPreset(HeadGamer::eDirection::DOWN));
    presets->setLeftAction(getPreset(HeadGamer::eDirection::LEFT));
    presets->setRightAction(getPreset(HeadGamer::eDirection::RIGHT));

    presets->setLeftMouseAction(getPreset(HeadGamer::eMouseButton::LEFT));
    presets->setRightMouseAction(getPreset(HeadGamer::eMouseButton::RIGHT));
    presets->setMiddleMouseAction(getPreset(HeadGamer::eMouseButton::MIDLE));
}

void MainWindow::fillWindowActionWidgetList()
{
    QString windowConfigName = ui->comboBoxWindowsSettings->currentText();
    if(windowConfigName == *(HeadGamer::ACTION_NONE_STR))
    {
        return;
    }

    QString path = Settings::WINDOW_DIR + "/" + windowConfigName;
    if(Utils::readFile(path, mWindowActionConfigList))
    {
        for(const auto& config : mWindowActionConfigList->getList())
        {
            mWindowActionWidgetList.push_back(std::make_shared<WindowActionWidget>(config));
        }
    }
}

void MainWindow::showAllWindowActionWidgets()
{
    for(auto& widget : mWindowActionWidgetList)
    {
        widget->show();
    }
}

void MainWindow::hideAllWindowActionWidgets()
{
    for(auto& widget : mWindowActionWidgetList)
    {
        widget->hide();
    }
}

HeadGamer::eMode MainWindow::getMode()
{
    HeadGamer::eMode resultMode = HeadGamer::eMode::UNDEFINED;

    if(ui->radioButtonMode1->isChecked())
    {
        resultMode = HeadGamer::eMode::MODE_1;
    }

    if(ui->radioButtonMode2->isChecked())
    {
        resultMode = HeadGamer::eMode::MODE_2;
    }

    return resultMode;
}

QString MainWindow::getPresetName()
{
    return ui->comboBoxButtonsPreset->currentText();
}

HeadGamer::eDirectionsCount MainWindow::getDirectionsCount()
{
    HeadGamer::eDirectionsCount resultDirectionsCount = HeadGamer::eDirectionsCount::FOUR;
    if(ui->comboBoxDirectionsCount->currentText() == "8")
    {
        resultDirectionsCount = HeadGamer::eDirectionsCount::EIGHT;
    }

    return resultDirectionsCount;
}

HeadGamer::eButtonPressType MainWindow::getButtonPressType()
{
    HeadGamer::eButtonPressType resultButtonPressType = HeadGamer::eButtonPressType::UNDEFINED;

    if(ui->radioButtonPressType_Hold->isChecked())
    {
        resultButtonPressType = HeadGamer::eButtonPressType::HOLD;
    }

    if(ui->radioButtonPressType_HoldForTime->isChecked())
    {
        resultButtonPressType = HeadGamer::eButtonPressType::HOLD_FOR_TIME;
    }

    return resultButtonPressType;
}

int32_t MainWindow::getTriggerThreshold()
{
    return ui->spinBoxTriggerThreshold->value();
}

int32_t MainWindow::getButtonPressTimeOut()
{
    return ui->spinBoxButtonPressTimeout->value();
}

tActionPtr MainWindow::getPreset(HeadGamer::eDirection direction)
{
    tActionPtr resultAction = nullptr;

    switch (direction)
    {
    case HeadGamer::eDirection::UP:
        resultAction = getPreset(ui->comboBoxButtonUp);
        break;
    case HeadGamer::eDirection::DOWN:
        resultAction = getPreset(ui->comboBoxButtonDown);
        break;
    case HeadGamer::eDirection::LEFT:
        resultAction = getPreset(ui->comboBoxButtonLeft);
        break;
    case HeadGamer::eDirection::RIGHT:
        resultAction = getPreset(ui->comboBoxButtonRight);
        break;
    default:
        break;
    }

    return resultAction;
}

tActionPtr MainWindow::getPreset(HeadGamer::eMouseButton mouseButton)
{
    tActionPtr resultAction = nullptr;

    switch (mouseButton)
    {
    case HeadGamer::eMouseButton::LEFT:
        resultAction = getPreset(ui->comboBoxLeftMouse);
        break;
    case HeadGamer::eMouseButton::RIGHT:
        resultAction = getPreset(ui->comboBoxRightMouse);
        break;
    case HeadGamer::eMouseButton::MIDLE:
        resultAction = getPreset(ui->comboBoxMidleMouse);
        break;
    default:
        break;
    }

    return resultAction;
}

tActionPtr MainWindow::getPreset(const QComboBox* combobox)
{
    return Utils::getActionFromCombobox(combobox);
}

void MainWindow::fillComboboxes()
{
    Utils::fillCombobox(ui->comboBoxButtonUp);
    Utils::fillCombobox(ui->comboBoxButtonDown);
    Utils::fillCombobox(ui->comboBoxButtonLeft);
    Utils::fillCombobox(ui->comboBoxButtonRight);
    Utils::fillCombobox(ui->comboBoxLeftMouse);
    Utils::fillCombobox(ui->comboBoxRightMouse);
    Utils::fillCombobox(ui->comboBoxMidleMouse);
}
