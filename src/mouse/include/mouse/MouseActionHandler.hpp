#ifndef MOUSEACTIONHANDLER_H
#define MOUSEACTIONHANDLER_H

#include "Mouse4DirectionsHandler.hpp"
#include "settings/Presets.hpp"
#include "action/IAction.hpp"

#include <QObject>
#include <memory>


class MouseActionHandler : public QObject
{
    Q_OBJECT
public:
    explicit MouseActionHandler(tPresetPtr& presets,
                                const std::shared_ptr<Mouse4DirectionsHandler>& mouseDirectionHandler,
                                QObject *parent = nullptr);

signals:

private:
    void executeDirectionAction(tActionPtr action, bool isActive) const;

    const tPresetPtr mPresets;

private slots:
    void onMouseDirectionChanged(HeadGamer::eDirection direction, bool isActive);


};

#endif // MOUSEACTIONHANDLER_H
