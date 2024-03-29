#include "common/Utils.hpp"
#include "action/KeyPressAction.hpp"
#include "action/MacroAction.hpp"
#include "action/StopAction.hpp"
#include "common/Types.hpp"
#include "settings/Settings.hpp"
#include "UI/ComboBoxDelegate.hpp"

#include <QDirIterator>
#include <QFileDialog>

Utils::Utils()
{

}

void Utils::fillComboboxWithJsonFileNames(QComboBox* comboBox, const QString& path)
{
    comboBox->clear();
    jsonCallback callback = [&comboBox](QString fileName) {comboBox->addItem(fileName);};
    doForAllJsonFiles(path, callback);
}

bool Utils::readJsonFile(const QString& path, QJsonDocument& result)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        // TODO strange why it works in headsr file
        qWarning("Couldn't read file '%s'", path.toStdString().c_str());
        return false;
    }
    result = QJsonDocument::fromJson(file.readAll());
    return true;
}

tActionPtr Utils::jsonToAction(const QString& name, const QJsonObject& json)
{
    if (HeadGamer::isJsonObjectPresent(name, json))
    {
        QJsonObject actionJson = json[name].toObject();
        return jsonToAction(actionJson);
    }

    const QString pathTofile = HeadGamer::jsonToString(json, name);
    if (pathTofile.isEmpty() == false)
    {
        return readActionFromFile(pathTofile);
    }

    return nullptr;
}

tActionPtr Utils::jsonToAction(const QJsonObject& json)
{
    if(json.contains(*(HeadGamer::TYPE_STR)) == true)
    {
        if(json[*(HeadGamer::TYPE_STR)].isString() == true)
        {
            tActionPtr action = nullptr;

            if(json[*(HeadGamer::TYPE_STR)] == *(HeadGamer::KEY_PRESS_ACTION_STR))
            {
                action = std::make_shared<KeyPressAction>();
                action->fromJson(json);
            }
            else if(json[*(HeadGamer::TYPE_STR)] == *(HeadGamer::MACRO_ACTION_STR))
            {
                action = std::make_shared<MacroAction>();
                action->fromJson(json);
            }
            else if(json[*(HeadGamer::TYPE_STR)] == *(HeadGamer::STOP_ACTION_STR))
            {
                action = std::make_shared<StopAction>();
                action->fromJson(json);
            }
            //Same for other actions

            return action;
        }
    }

    return nullptr;
}

void Utils::doForAllJsonFiles(const QString& path, const jsonCallback& callback)
{
    QDirIterator it(path, {"*.json", "*.JSON"}, QDir::Files);
    while (it.hasNext())
    {
        //TODO add file validation
        static_cast<void>(it.next());
        callback(it.fileName());
    }
}

void Utils::fillCombobox(QComboBox* combobox)
{
    QStandardItemModel * model = new QStandardItemModel();

    for (const auto& virtualKey : HeadGamer::VIRTUAL_KEYS)
    {
        if(virtualKey.virtualKey == VC_A)
        {
            addParentItem(model, "Letters");
        }
        if(virtualKey.virtualKey == VC_0)
        {
            addParentItem(model, "Digits");
        }
        if(virtualKey.virtualKey == VC_NUM_LOCK)
        {
            addParentItem(model, "Numpad");
        }
        if(virtualKey.virtualKey == VC_F1)
        {
            addParentItem(model, "F buttons");
        }
        if(virtualKey.virtualKey == VC_UP)
        {
            addParentItem(model, "Arrows");
        }
        if(virtualKey.virtualKey == MOUSE_BUTTON1)
        {
            addParentItem(model, "Mouse buttons");
        }
        if(virtualKey.virtualKey == VC_SPACE)
        {
            addParentItem(model, "Special");
        }
        if(virtualKey.virtualKey == VC_MINUS)
        {
            addParentItem(model, "Signes");
        }
        addChildItem(model, virtualKey.buttonStr, virtualKey.virtualKey);
    }

    addParentItem(model, "Actions");
    addChildItem(model, "Stop", HeadGamer::STOP_ACTION);

    addParentItem(model, "Scripts");
    jsonCallback callback = [&model](QString fileName) { addChildItem(model, fileName, HeadGamer::SCRIPT_ACTION); };
    doForAllJsonFiles(Settings::SCRIPT_DIR, callback);

    combobox->setModel(model);
    combobox->setItemDelegate(new ComboBoxDelegate);
}

void Utils::addParentItem(QStandardItemModel* model, const QString& text)
{
    QStandardItem* item = new QStandardItem( text );
    item->setFlags( item->flags() & ~( Qt::ItemIsEnabled | Qt::ItemIsSelectable ) );
    item->setData( "parent", Qt::AccessibleDescriptionRole );
    QFont font = item->font();
    font.setBold( true );
//    font.setItalic( true );
    item->setFont( font );
    model->appendRow( item );
}

void Utils::addChildItem(QStandardItemModel* model, const QString& text, const QVariant& data)
{
    QStandardItem* item = new QStandardItem( text );
    item->setData( data, Qt::UserRole );
    item->setData( "child", Qt::AccessibleDescriptionRole );
    model->appendRow( item );
}

tActionPtr Utils::getActionFromCombobox(const QComboBox* combobox)
{
    QString text = combobox->currentText();
    if(text == *(HeadGamer::ACTION_NONE_STR))
    {
        return nullptr;
    }

    auto data = combobox->currentData().value<int32_t>();
    // It is script => read action from json file
    if (data == HeadGamer::SCRIPT_ACTION)
    {
        const QString path = Settings::SCRIPT_DIR + "/" + text;
        return readActionFromFile(path);
    }

    if(data == HeadGamer::STOP_ACTION)
    {
        return std::make_shared<StopAction>();
    }

    return std::make_shared<KeyPressAction>(text, data);
}

tActionPtr Utils::readActionFromFile(const QString& path)
{
    QJsonDocument jsonDocument;
    if (readJsonFile(path, jsonDocument))
    {
        QJsonObject json = jsonDocument.object();
        json[*(HeadGamer::PATH_TO_ACTION_STR)] = path;
        return jsonToAction(json);
    }

    return nullptr;
}

QString Utils::createFile(const QString& caption, const QString& dir, const QString& filter)
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, caption, dir, filter);
    if(fileName.endsWith(".json", Qt::CaseInsensitive) == false)
    {
        fileName.append(".json");
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't save file '%s'", fileName.toStdString().c_str());
    }

    return fileName;
}

void Utils::setActiveComboboxElementByName(QComboBox* combobox, const QString& name)
{
    const int32_t index = combobox->findText(name);
    const int32_t INVALID_INDEX = -1;
    if(index == INVALID_INDEX)
    {
        qWarning("Couldn't find element with name '%s'", name.toStdString().c_str());
        return;
    }

    combobox->setCurrentIndex(index);
}

QString Utils::getFileName(const QString& path)
{
    const QFileInfo info(path);
    return info.fileName();
}

QString Utils::getFileNameFromCombobox(const QComboBox* combobox)
{
    //Delete " *" (used to show that config modified)
    return combobox->currentText().remove(" *");
}

void Utils::markSettingsComboboxChanged(QComboBox* combobox)
{
    combobox->setItemText(combobox->currentIndex(), combobox->currentText() + " *");
}

bool Utils::writeFile(const QString& path, const std::shared_ptr<const IJson>& objectToSave)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't save file '%s'", path.toStdString().c_str());
        return false;
    }

    QJsonObject json = objectToSave->toJson();
    return (file.write(QJsonDocument(json).toJson()) != -1);
}

bool Utils::readFile(const QString& path, const std::shared_ptr<IJson>& objectToRead)
{
    QJsonDocument jsonDocument;
    if (readJsonFile(path, jsonDocument))
    {
        objectToRead->fromJson(jsonDocument.object());
        return true;
    }

    return false;
}
