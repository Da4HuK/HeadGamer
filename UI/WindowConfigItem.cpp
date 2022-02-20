#include "WindowConfigItem.hpp"
#include "ui_WindowConfigItem.h"
#include "UI/WindowActionWidget.hpp"

#include "action/MacroAction.hpp"
#include "action/KeyPressAction.hpp"
#include "Types.hpp"
#include "Utils.hpp"
#include "Settings.hpp"

#include <QColorDialog>
#include <QDebug>


WindowConfigItem::WindowConfigItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WindowConfigItem)
    , mColor()
{
    ui->setupUi(this);
    mWindowActionWidget = std::make_shared<WindowActionWidget>(getWindowActionConfig());
    Utils::fillCombobox(ui->comboBoxActionType);
}

WindowConfigItem::~WindowConfigItem()
{
    qDebug() << "~WindowConfigItem()";
    delete ui;
    mWindowActionWidget.reset();
}

tWindowActionConfigPtr WindowConfigItem::getWindowActionConfig()
{
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

void WindowConfigItem::onPushButtonDeletePressed()
{
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
    }
}

void WindowConfigItem::onPushButtonShowPressed()
{
    mWindowActionWidget->show();
}

void WindowConfigItem::onComboBoxActionTypeCurrentTextChanged(const QString& text)
{
    mWindowActionWidget->setAction(Utils::getActionFromCombobox(ui->comboBoxActionType));
}

void WindowConfigItem::onXChanged(int x)
{
    if(mWindowActionWidget != nullptr)
    {
        mWindowActionWidget->move(x, ui->spinBoxPositionY->value());
    }
}

void WindowConfigItem::onYChanged(int y)
{
    if(mWindowActionWidget != nullptr)
    {
        mWindowActionWidget->move(ui->spinBoxPositionX->value(), y);
    }
}

void WindowConfigItem::onWidthChanged(int width)
{
    if(mWindowActionWidget != nullptr)
    {
        mWindowActionWidget->resize(width, ui->spinBoxHeight->value());
    }
}

void WindowConfigItem::onHeightChanged(int height)
{
    if(mWindowActionWidget != nullptr)
    {
        mWindowActionWidget->resize(ui->spinBoxWidth->value(), height);
    }
}

void WindowConfigItem::setAction(tWindowActionConfigPtr& config)
{

}
