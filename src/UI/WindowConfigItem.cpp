#include "UI/WindowConfigItem.hpp"
#include "ui_WindowConfigItem.h"
#include "UI/WindowActionWidget.hpp"

#include "action/MacroAction.hpp"
#include "action/KeyPressAction.hpp"
#include "common/Types.hpp"
#include "common/Utils.hpp"
#include "settings/Settings.hpp"

#include <QColorDialog>
#include <QDebug>


WindowConfigItem::WindowConfigItem(tWindowActionConfigPtr& config, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WindowConfigItem)
    , mColor()
    , isShowed(false)
{
    ui->setupUi(this);
    Utils::fillCombobox(ui->comboBoxActionType);

    if (config == nullptr)
    {
        mWindowActionConfig = getWindowActionConfig();
    }
    else
    {
        setWindowActionConfig(config);
    }

    mWindowActionWidget = std::make_shared<WindowActionWidget>(mWindowActionConfig);
}

WindowConfigItem::~WindowConfigItem()
{
    qDebug() << "~WindowConfigItem()";
    delete ui;
    mWindowActionWidget.reset();
    mWindowActionConfig.reset();
}

tWindowActionConfigPtr WindowConfigItem::getWindowActionConfig()
{
    if (mWindowActionConfig != nullptr)
    {
        return mWindowActionConfig;
    }

    tWindowActionConfigPtr config = std::make_shared<WindowActionConfig>();
    config->setName(ui->lineEditWindowName->text());
    config->setAction(Utils::getActionFromCombobox(ui->comboBoxActionType));
    config->setColor(mColor);
    config->setWidth(ui->spinBoxWidth->value());
    config->setHeight(ui->spinBoxHeight->value());
    config->setX(ui->spinBoxPositionX->value());
    config->setY(ui->spinBoxPositionY->value());
    return config;
}

void WindowConfigItem::setWindowActionConfig(tWindowActionConfigPtr& config)
{
    mWindowActionConfig = config;
    ui->lineEditWindowName->setText(mWindowActionConfig->getName());
    mColor = config->getColor();
    ui->lineEditColor->setText(mColor.name(QColor::HexArgb));
    ui->spinBoxWidth->setValue(config->getWidth());
    ui->spinBoxHeight->setValue(config->getHeight());
    ui->spinBoxPositionX->setValue(config->getX());
    ui->spinBoxPositionY->setValue(config->getY());

    if(mWindowActionConfig->getAction() == nullptr)
    {
        Utils::setActiveComboboxElementByName(ui->comboBoxActionType, *(HeadGamer::ACTION_NONE_STR));
    }
    else
    {
        Utils::setActiveComboboxElementByName(ui->comboBoxActionType, mWindowActionConfig->getAction()->getName());
    }
}

void WindowConfigItem::onPushButtonDeletePressed()
{
//    mWindowActionConfig.reset();
    emit deleteItem(this);
}

void WindowConfigItem::onPushButtonSelectColorPressed()
{
    QColorDialog colorDialog(mColor);
    colorDialog.setOption(QColorDialog::ShowAlphaChannel);
    if(colorDialog.exec() == QDialog::Accepted)
    {
        mColor = colorDialog.selectedColor();
        ui->lineEditColor->setText(mColor.name(QColor::HexArgb));
        if(mWindowActionWidget != nullptr)
        {
            mWindowActionWidget->setColor(mColor);
        }

        if(mWindowActionConfig != nullptr)
        {
            mWindowActionConfig->setColor(mColor);
        }
    }
}

void WindowConfigItem::onPushButtonShowHidePressed()
{
    if(isShowed)
    {
        ui->pushButtonShowHide->setText("Показать");
        mWindowActionWidget->hide();
        isShowed = false;
    }
    else
    {
        ui->pushButtonShowHide->setText("Скрыть");
        mWindowActionWidget->show();
        isShowed = true;
    }
}

void WindowConfigItem::onComboBoxActionTypeCurrentTextChanged(const QString& /*text*/)
{
    tActionPtr action = Utils::getActionFromCombobox(ui->comboBoxActionType);
    if(mWindowActionWidget != nullptr)
    {
        mWindowActionWidget->setAction(action);
    }

    if(mWindowActionConfig != nullptr)
    {
        mWindowActionConfig->setAction(action);
    }
}

void WindowConfigItem::onLineEditWindowNameTextChanged(const QString& text)
{
    if(mWindowActionConfig != nullptr)
    {
        mWindowActionConfig->setName(text);
    }
}

void WindowConfigItem::onXChanged(int x)
{
    if(mWindowActionWidget != nullptr)
    {
        mWindowActionWidget->move(x, ui->spinBoxPositionY->value());
    }

    if(mWindowActionConfig != nullptr)
    {
        mWindowActionConfig->setX(x);
    }
}

void WindowConfigItem::onYChanged(int y)
{
    if(mWindowActionWidget != nullptr)
    {
        mWindowActionWidget->move(ui->spinBoxPositionX->value(), y);
    }

    if(mWindowActionConfig != nullptr)
    {
        mWindowActionConfig->setY(y);
    }
}

void WindowConfigItem::onWidthChanged(int width)
{
    if(mWindowActionWidget != nullptr)
    {
        mWindowActionWidget->resize(width, ui->spinBoxHeight->value());
    }

    if(mWindowActionConfig != nullptr)
    {
        mWindowActionConfig->setWidth(width);
    }
}

void WindowConfigItem::onHeightChanged(int height)
{
    if(mWindowActionWidget != nullptr)
    {
        mWindowActionWidget->resize(ui->spinBoxWidth->value(), height);
    }

    if(mWindowActionConfig != nullptr)
    {
        mWindowActionConfig->setHeight(height);
    }
}

void WindowConfigItem::setAction(tWindowActionConfigPtr& config)
{

}
