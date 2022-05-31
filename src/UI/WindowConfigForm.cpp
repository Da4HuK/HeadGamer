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
}

WindowConfigForm::~WindowConfigForm()
{
    clearAllWindows();
    delete ui;
}

void WindowConfigForm::onPushButtonAddWindowConfigPressed()
{

}

void WindowConfigForm::onPushButtonCopyWindowConfigPressed()
{

}

void WindowConfigForm::onPushButtonRenameWindowConfigPressed()
{

}

void WindowConfigForm::onPushButtonSaveWindowConfigPressed()
{
    // TODO implement
    QString fileName = Utils::getSaveFileName("Save windows file", Settings::WINDOW_DIR, tr("Windows files (*.json *.JSON)"));
    tContsWindowActionConfigPtr cfg = mWindowsItemsVector[0]->getWindowActionConfig();
    Utils::writeFile(fileName, cfg);
}

void WindowConfigForm::onPushButtonDeleteWindowConfigPressed()
{

}

void WindowConfigForm::onPushButtonAddWindowPressed()
{
    tWindowConfigItemPtr windowConfigItem = std::make_shared<WindowConfigItem>(this);
    mWindowsItemsVector.push_back(windowConfigItem);
    connect(windowConfigItem.get(), &WindowConfigItem::deleteItem, this, &WindowConfigForm::onDeleteWindowConfigItem);
    ui->verticalLayoutWindowsItems->insertWidget(mLastIndex, windowConfigItem.get());
    ++mLastIndex;
}

void WindowConfigForm::onDeleteWindowConfigItem(WindowConfigItem* item)
{
    ui->verticalLayoutWindowsItems->removeWidget(item);
    mWindowsItemsVector.erase(std::remove_if(mWindowsItemsVector.begin(),
                              mWindowsItemsVector.end(),
                              [item](tWindowConfigItemPtr element){ return element.get() == item; }));
    --mLastIndex;
}

void WindowConfigForm::clearAllWindows()
{
    mLastIndex = 0;
    mWindowsItemsVector.clear();
}

void WindowConfigForm::hideEvent(QHideEvent* /*event*/)
{
    clearAllWindows();
}
