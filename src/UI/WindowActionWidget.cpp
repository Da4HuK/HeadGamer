#include "UI/WindowActionWidget.hpp"
#include "action/IAction.hpp"


#include <QDebug>

WindowActionWidget::WindowActionWidget(const tWindowActionConfigPtr& config, QWidget *parent)
    : QWidget(parent)
    , mAction(nullptr)
{
    qDebug() << "WindowActionWidget()";
    setWidgetProperties(config);
}

WindowActionWidget::~WindowActionWidget()
{
    qDebug() << "~WindowActionWidget()";
}

void WindowActionWidget::setColor(QColor color)
{
    QPalette pal = palette();
    pal.setColor(QPalette::Window, color);
    setWindowOpacity(color.alphaF());
    setPalette(pal);
}

void WindowActionWidget::setAction(const tActionPtr& action)
{
    mAction = action;
}

void WindowActionWidget::enterEvent(QEvent* /*event*/)
{
    if (mAction != nullptr)
    {
        QString s = mAction->getName();
        qDebug() << "WindowActionWidget::enterEvent: run action " << s;
        mAction->action();
    }
    else
    {
        qDebug() << "WindowActionWidget::enterEvent: action is empty!!!";
    }
}


void WindowActionWidget::setWidgetProperties(const tWindowActionConfigPtr& config)
{
    mAction.reset();
    mAction = config->getAction();
    setObjectName(config->getName());
    resize(config->getWidth(), config->getHeight());
    move(config->getX(), config->getY());
    Qt::WindowFlags flags = (Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setWindowFlags(flags);
//    setWindowOpacity(0.7);
//    setAttribute(Qt::WA_NoSystemBackground);
//    setAttribute(Qt::WA_TranslucentBackground);
    //Work only for Windows
//    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_TransparentForMouseEvents);

    setColor(config->getColor());
}
