#ifndef WINDOWCONFIGFORM_HPP
#define WINDOWCONFIGFORM_HPP

#include "action/WindowActionConfig.hpp"
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

private:
    void clearAllWindows();
    Ui::WindowConfigForm *ui;
    std::vector<tWindowConfigItemPtr> mWindowsItemsVector;
    int32_t mLastIndex;

    // QWidget interface
protected:
    void hideEvent(QHideEvent* event) override;
};

#endif // WINDOWCONFIGFORM_HPP
