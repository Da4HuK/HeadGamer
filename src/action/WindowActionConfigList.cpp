#include "action/WindowActionConfigList.hpp"
#include "common/Types.hpp"
#include <QJsonArray>

WindowActionConfigList::WindowActionConfigList()
    : mConfigList()
{
}

QJsonObject WindowActionConfigList::toJson() const
{
    QJsonObject json;
    QJsonArray jsonArray;
    for (auto& config : mConfigList)
    {
        jsonArray.push_back(config->toJson());
    }
    json[*(HeadGamer::WINDOW_ACTION_CONFIG_LIST_STR)] = jsonArray;

    return json;
}

void WindowActionConfigList::fromJson(const QJsonObject& json)
{
    if (HeadGamer::isJsonArrayPresent(*(HeadGamer::WINDOW_ACTION_CONFIG_LIST_STR), json))
    {
        mConfigList.clear();
        QJsonArray array = json[*(HeadGamer::WINDOW_ACTION_CONFIG_LIST_STR)].toArray();
        for (auto&& item : array)
        {
            tWindowActionConfigPtr config = std::make_shared<WindowActionConfig>();
            config->fromJson(item.toObject());
            mConfigList.push_back(config);
        }
    }
}
