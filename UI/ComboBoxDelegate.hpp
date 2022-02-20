#ifndef COMBOBOXDELEGATE_HPP
#define COMBOBOXDELEGATE_HPP

#include <QItemDelegate>
#include <QPainter>

class ComboBoxDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit ComboBoxDelegate(QObject *parent = nullptr);
    virtual ~ComboBoxDelegate() = default;

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // COMBOBOXDELEGATE_HPP
