#ifndef UTILS_HPP
#define UTILS_HPP

#include "action/IAction.hpp"

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
    template<typename T> static bool writeFile(const QString& path, const std::shared_ptr<const T>& objectToSave);
    template<typename T> static bool readFile(const QString& path, const std::shared_ptr<T>& result);
    static void doForAllJsonFiles(const QString& path, const jsonCallback& callback);
    static void fillCombobox(QComboBox* combobox);
    static void addParentItem(QStandardItemModel* model, const QString& text);
    static void addChildItem(QStandardItemModel* model, const QString& text, const QVariant& data);
    static tActionPtr getActionFromCombobox(const QComboBox* combobox);
    static tActionPtr readActionFromFile(const QString& path);
};


template<typename T>
bool Utils::writeFile(const QString& path, const std::shared_ptr<const T>& objectToSave)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't save file '%s'", path);
        return false;
    }

    QJsonObject json = objectToSave->toJson();
    return (file.write(QJsonDocument(json).toJson()) != -1);
}

template<typename T>
bool Utils::readFile(const QString& path, const std::shared_ptr<T>& result)
{
//    QFile file(path);
//    if (!file.open(QIODevice::ReadOnly))
//    {
//        qWarning("Couldn't read file '%s'", path);
//        return false;
//    }
//    QJsonDocument jsonDocument(QJsonDocument::fromJson(file.readAll()));
    QJsonDocument jsonDocument;
    if (readJsonFile(path, jsonDocument))
    {
        T::fromJson(jsonDocument.object(), result);
        return true;
    }

    return false;
}
#endif // UTILS_HPP
