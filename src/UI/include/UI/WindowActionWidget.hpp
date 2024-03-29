#ifndef WINDOWACTIONWIDGET_HPP
#define WINDOWACTIONWIDGET_HPP

#include "action/WindowActionConfig.hpp"
#include "action/IAction.hpp"

#include <QWidget>

class IAction;
class WindowActionWidget;

using tWindowActionWidgetPtr = std::shared_ptr<WindowActionWidget>;
using tConstWindowActionWidgetPtr = const std::shared_ptr<const WindowActionWidget>;

class WindowActionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WindowActionWidget(const tWindowActionConfigPtr& config, QWidget *parent = nullptr);
    virtual ~WindowActionWidget();

    void setColor(QColor color);
    void setAction(const tActionPtr& action);

signals:

    // QWidget interface
protected:
    virtual void enterEvent(QEnterEvent* event) override;

private:
    void setWidgetProperties(const tWindowActionConfigPtr& config);

    tActionPtr mAction;
};

#endif // WINDOWACTIONWIDGET_HPP
