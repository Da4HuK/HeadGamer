#ifndef UTILS_HPP
#define UTILS_HPP

#include "action/IAction.hpp"
#include "common/IJson.hpp"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QComboBox>
#include <QStandardItemModel>
#include <functional>

using jsonCallback = std::function<void(const QString& /*jsonFileName*/)>;

class Utils
{
public:
    Utils();

    static void fillComboboxWithJsonFileNames(QComboBox* comboBox, const QString& path);
    static bool readJsonFile(const QString& path, QJsonDocument& result);
    static tActionPtr jsonToAction(const QString& name, const QJsonObject& json);
    static tActionPtr jsonToAction(const QJsonObject& json);
    static bool writeFile(const QString& path, const std::shared_ptr<const IJson>& objectToSave);
    static bool readFile(const QString& path, const std::shared_ptr<IJson>& objectToRead);
    static void doForAllJsonFiles(const QString& path, const jsonCallback& callback);
    static void fillCombobox(QComboBox* combobox);
    static void addParentItem(QStandardItemModel* model, const QString& text);
    static void addChildItem(QStandardItemModel* model, const QString& text, const QVariant& data);
    static tActionPtr getActionFromCombobox(const QComboBox* combobox);
    static tActionPtr readActionFromFile(const QString& path);
    // returns created file name
    static QString createFile(const QString& caption, const QString& dir, const QString& filter);
    static void setActiveComboboxElementByName(QComboBox* combobox, const QString& name);
    static QString getFileName(const QString& path);
    static QString getFileNameFromCombobox(const QComboBox* combobox);
    static void markSettingsComboboxChanged(QComboBox* combobox);
};




#endif // UTILS_HPP
