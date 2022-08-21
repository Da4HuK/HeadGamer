#include "UI/WindowConfigForm.hpp"
#include "ui_WindowConfigForm.h"
#include "common/Utils.hpp"
#include "settings/Settings.hpp"

#include <QFileDialog>
#include <QHideEvent>

WindowConfigForm::WindowConfigForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WindowConfigForm)
    , mWindowsItemsVector()
    , mLastIndex(0)
{
    ui->setupUi(this);
    init();
}

WindowConfigForm::~WindowConfigForm()
{
    clearAllWindows();
    delete ui;
}

void WindowConfigForm::onPushButtonAddWindowConfigPressed()
{
    QString fileName = Utils::createFile("Create windows file", Settings::WINDOW_DIR, tr("Windows files (*.json *.JSON)"));
    readWindowConfigList(Settings::WINDOW_DIR);
    Utils::setActiveComboboxElementByName(ui->comboBoxWindowConfigList, Utils::getFileName(fileName));
}

void WindowConfigForm::onPushButtonCopyWindowConfigPressed()
{

}

void WindowConfigForm::onPushButtonRenameWindowConfigPressed()
{

}

void WindowConfigForm::onPushButtonSaveWindowConfigPressed()
{
    QString fileName =  Settings::WINDOW_DIR + "/" + Utils::getFileNameFromCombobox(ui->comboBoxWindowConfigList);
    Utils::writeFile(fileName, mWindowActionConfigList);
}

void WindowConfigForm::onPushButtonDeleteWindowConfigPressed()
{

}

void WindowConfigForm::onPushButtonAddWindowPressed()
{
    tWindowActionConfigPtr windowActionConfig = std::make_shared<WindowActionConfig>();
    mWindowActionConfigList->getList().push_back(windowActionConfig);
    addWindowsActionConfigItem(windowActionConfig);
}

void WindowConfigForm::onDeleteWindowConfigItem(WindowConfigItem* item)
{
    auto& configList = mWindowActionConfigList->getList();
    configList.erase(std::remove_if(configList.begin(),
                                    configList.end(),
                                    [item](auto& config) { return config == item->getWindowActionConfig(); } ));

    mWindowsItemsVector.erase(std::remove_if(mWindowsItemsVector.begin(),
                                             mWindowsItemsVector.end(),
                                             [&item](auto& element){ return element.get() == item; }));
    --mLastIndex;
    ui->verticalLayoutWindowsItems->removeWidget(item);
}

void WindowConfigForm::onComboBoxWindowConfigListCurrentTextChanged(const QString& text)
{
    clearAllWindows();
    QString windowsActionListConfigPath = Settings::WINDOW_DIR + "/" + text;
    readWindowConfigFile(windowsActionListConfigPath, mWindowActionConfigList);
}

void WindowConfigForm::clearAllWindows()
{
    mLastIndex = 0;
    mWindowsItemsVector.clear();
    mWindowActionConfigList->getList().clear();
}

void WindowConfigForm::readWindowConfigList(const QString& path)
{
    Utils::fillComboboxWithJsonFileNames(ui->comboBoxWindowConfigList, path);
}

void WindowConfigForm::readWindowConfigFile(const QString& fileName, const tWindowActionConfigListPtr& windowConfigList)
{
    if(Utils::readFile(fileName, windowConfigList))
    {
        for(auto& config : windowConfigList->getList())
        {
            addWindowsActionConfigItem(config);
        }
    }
    else
    {
        qDebug() << "Error to read " << fileName;
    }
}

void WindowConfigForm::addWindowsActionConfigItem(tWindowActionConfigPtr& windowActionConfig)
{
    tWindowConfigItemPtr windowConfigItem = std::make_shared<WindowConfigItem>(windowActionConfig, this);
    mWindowsItemsVector.push_back(windowConfigItem);
    connect(windowConfigItem.get(), &WindowConfigItem::deleteItem, this, &WindowConfigForm::onDeleteWindowConfigItem);
    ui->verticalLayoutWindowsItems->insertWidget(mLastIndex, windowConfigItem.get());
    ++mLastIndex;
}

void WindowConfigForm::init()
{
    mWindowActionConfigList = std::make_shared<WindowActionConfigList>();
    readWindowConfigList(Settings::WINDOW_DIR);
}

void WindowConfigForm::showEvent(QShowEvent* /*event*/)
{
    init();
}


void WindowConfigForm::hideEvent(QHideEvent* /*event*/)
{
    clearAllWindows();
}
