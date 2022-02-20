#ifndef WINDOWCONFIGITEM_HPP
#define WINDOWCONFIGITEM_HPP

#include "WindowActionConfig.hpp"

#include <QWidget>
#include <QColor>
#include <memory>

class QColorDialog;
class WindowActionWidget;
class WindowConfigItem;

using tWindowConfigItemPtr = std::shared_ptr<WindowConfigItem>;
using tContsWindowConfigItemPtr = const std::shared_ptr<const WindowConfigItem>;

namespace Ui {
class WindowConfigItem;
}

class WindowConfigItem : public QWidget
{
    Q_OBJECT

public:
    explicit WindowConfigItem(QWidget *parent = nullptr);
    virtual ~WindowConfigItem();

    tWindowActionConfigPtr getWindowActionConfig();

signals:
    void deleteItem(WindowConfigItem* item);

private slots:
    void onPushButtonDeletePressed();
    void onPushButtonSelectColorPressed();
    void onPushButtonShowPressed();
    void onComboBoxActionTypeCurrentTextChanged(const QString& text);

    void onXChanged(int x);
    void onYChanged(int y);
    void onWidthChanged(int width);
    void onHeightChanged(int height);

private:
    void setAction(tWindowActionConfigPtr& config);

    Ui::WindowConfigItem *ui;
    QColor mColor;
    std::shared_ptr<WindowActionWidget> mWindowActionWidget;
};

#endif // WINDOWCONFIGITEM_HPP
