#include "comboboxitemdelegate.h"

ComboBoxItemDelegate::ComboBoxItemDelegate(QObject* parent) : QStyledItemDelegate(parent)
{
}

ComboBoxItemDelegate::~ComboBoxItemDelegate()
{
}

QWidget* ComboBoxItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.column() == 1)
	{
		QComboBox* cb = new QComboBox(parent);
		const int row = index.row();
		cb->addItem(QString("Chess").arg(row));
		cb->addItem(QString("Xiangqi").arg(row));
		cb->addItem(QString("Shogi").arg(row));
		cb->addItem(QString("Sho Shogi").arg(row));
		cb->addItem(QString("Chu Shogi").arg(row));
		cb->addItem(QString("Mini Shogi").arg(row));
		return cb;
	}
	if (index.column() == 2)
	{
		QComboBox* cb = new QComboBox(parent);
		const int row = index.row();
		cb->addItem(QString("XBoard").arg(row));
		cb->addItem(QString("UCI").arg(row));
		cb->addItem(QString("UCCI").arg(row));
		cb->addItem(QString("Qianhong").arg(row));
		cb->addItem(QString("USI").arg(row));
		return cb;
	}
	return QStyledItemDelegate::createEditor(parent, option, index);
}

void ComboBoxItemDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    if (QComboBox* cb = qobject_cast<QComboBox*>(editor)) {
       // get the index of the text in the combobox that matches the current value of the itenm
       const QString currentText = index.data(Qt::EditRole).toString();
       const int cbIndex = cb->findText(currentText);
       // if it is valid, adjust the combobox
       if (cbIndex >= 0)
           cb->setCurrentIndex(cbIndex);
    } else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void ComboBoxItemDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    if (const QComboBox* cb = qobject_cast<QComboBox*>(editor))
        // save the current text of the combo box as the current value of the item
        model->setData(index, cb->currentText(), Qt::EditRole);
    else
        QStyledItemDelegate::setModelData(editor, model, index);
}
