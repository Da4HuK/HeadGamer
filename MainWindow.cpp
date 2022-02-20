#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "MouseHookHandler.hpp"
#include "action/KeyPressAction.hpp"
#include "MouseHookHandler.hpp"
#include "Utils.hpp"

#include "UI/ComboBoxDelegate.hpp"
//#include "UI/DirectionWidget.hpp"

#include <QFileDialog>
#include <QDirIterator>
#include <QPalette>
//#include <QComboBox>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mMouseHookHandler(nullptr)
    , mMouseDirectionHandler(nullptr)
    , mMouseActionHandler(nullptr)
    , mPresets(std::make_shared<Presets>())
    , mWindowAction(nullptr)
    , mWindowConfigForm(nullptr)
{
    ui->setupUi(this);

    qDebug() << "MainWindow()";
    init();
}

MainWindow::~MainWindow()
{
    qDebug() << "~MainWindow()";
    mWindowConfigForm.reset();
    mMouseHookHandler->stop();
    delete ui;
    qDebug() << "~MainWindow() finished";
}

void MainWindow::onPushButtonAddProfilePressed()
{

}

void MainWindow::onPushButtonCopyProfilePressed()
{

}

void MainWindow::onPushButtonRenameProfilePressed()
{

}

void MainWindow::onPushButtonSaveProfilePressed()
{
    tSettingsPtr settings;
    fillSettings(settings);
    try
    {
        QString fileName = QFileDialog::getSaveFileName(this, "Save profile file", Settings::PROFILE_DIR, tr("Profile files (*.json *.JSON)"));
        Utils::writeFile<Settings>(fileName, settings);
    }
    catch (std::exception ex)
    {
        qDebug() << ex.what();
    }
}

void MainWindow::onPushButtonDeleteProfilePressed()
{

}

void MainWindow::onPushButtonAddPresetPressed()
{

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
        QString fileName = QFileDialog::getSaveFileName(this, "Save presets file", Settings::PRESET_DIR, tr("Presets files (*.json *.JSON)"));
        Utils::writeFile<Presets>(fileName, mPresets);
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
    if(mMouseDirectionHandler == nullptr)
    {
        mMouseDirectionHandler = std::make_shared<Mouse4DirectionsHandler>(mMouseHookHandler);
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
    this->close();
}

void MainWindow::onPushButtonWindowsSettingPressed()
{
    if(mWindowConfigForm == nullptr)
    {
        mWindowConfigForm = std::make_shared<WindowConfigForm>(this);
    }
    mWindowConfigForm->show();

//    mWindowAction = std::make_shared<WindowActionWidget>(nullptr);
//    mWindowAction->show();
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
    if(text.isEmpty() == false)
    {
        readPresetFile(text, mPresets);
        initPresetControls(mPresets);
    }
}

void MainWindow::onComboBoxWindowsSettingsTextChanged(const QString& text)
{
    if(text.isEmpty() == false)
    {
//        readPresetFile(text, mPresets);
//        initPresetControls(mPresets);
    }
}

void MainWindow::init()
{
    fillComboboxes();
    createSettingsDirectories();
    readProfilesList(Settings::PROFILE_DIR);
    readPresetsList(Settings::PRESET_DIR);

    mMouseHookHandler = std::make_shared<MouseHookHandler>();
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

void MainWindow::initProfileSettingsControls(const tSettingsPtr& settings)
{
    ui->comboBoxButtonsPreset->setCurrentText(settings->getPresetName());
    ui->comboBoxDirectionsCount->setCurrentText(
                (settings->getDirectionsCount() == HeadGamer::eDirectionsCount::FOUR) ? "4" : "8");
    ui->spinBoxTriggerThreshold->setValue(settings->getTriggerThreshold());

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
}

void MainWindow::initPresetControls(tContsPresetPtr& presets)
{
    auto initCombobox = [] (QComboBox* combobox, tContsActionPtr action)
    {
        if(action == nullptr)
        {
            combobox->setCurrentText("None");
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
