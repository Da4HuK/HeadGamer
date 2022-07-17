#ifndef WINDOWCONFIGFORM_HPP
#define WINDOWCONFIGFORM_HPP

#include "action/WindowActionConfigList.hpp"
#include "WindowConfigItem.hpp"

#include <QDialog>
#include <vector>


namespace Ui {
class WindowConfigForm;
}

class WindowConfigForm : public QDialog
{
    Q_OBJECT

public:
    explicit WindowConfigForm(QWidget *parent = nullptr);
    virtual ~WindowConfigForm();

private slots:
    void onPushButtonAddWindowConfigPressed();
    void onPushButtonCopyWindowConfigPressed();
    void onPushButtonRenameWindowConfigPressed();
    void onPushButtonSaveWindowConfigPressed();
    void onPushButtonDeleteWindowConfigPressed();

    void onPushButtonAddWindowPressed();
    void onDeleteWindowConfigItem(WindowConfigItem* item);

    void onComboBoxWindowConfigListCurrentTextChanged(const QString& text);


private:
    void clearAllWindows();
    void readWindowConfigList(const QString& path);
    void readWindowConfigFile(const QString& fileName, const tWindowActionConfigListPtr& windowConfigList);
    void addWindowsActionConfigItem(tWindowActionConfigPtr& windowActionConfig);
    Ui::WindowConfigForm *ui;
    tWindowActionConfigListPtr mWindowActionConfigList;
    std::vector<tWindowConfigItemPtr> mWindowsItemsVector;
    int32_t mLastIndex;

    // QWidget interface
protected:
    void hideEvent(QHideEvent* event) override;
};

#endif // WINDOWCONFIGFORM_HPP
