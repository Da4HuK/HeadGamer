#ifndef WINDOWACTIONCONFIGLIST_H
#define WINDOWACTIONCONFIGLIST_H

#include "action/WindowActionConfig.hpp"
#include "common/IJson.hpp"

#include <vector>

class WindowActionConfigList;

using tWindowActionConfigListPtr = std::shared_ptr<WindowActionConfigList>;
using tConstWindowActionConfigListPtr = const std::shared_ptr<const WindowActionConfigList>;

class WindowActionConfigList : public IJson
{
public:
    WindowActionConfigList();
    virtual ~WindowActionConfigList() = default;

    std::vector<tWindowActionConfigPtr>& getList() { return mConfigList; }

    // IJson interface
    QJsonObject toJson() const override;
    void fromJson(const QJsonObject& json) override;

private:
    std::vector<tWindowActionConfigPtr> mConfigList;


};

#endif // WINDOWACTIONCONFIGLIST_H
