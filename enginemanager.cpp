#include "enginemanager.h"
#include "ui_enginemanager.h"

EngineManager::EngineManager(QWidget *parent) : QDialog(parent), ui(new Ui::EngineManager)
{
	ui->setupUi(this);
	ComboBoxItemDelegate* cbid = new ComboBoxItemDelegate(ui->engineTable);
	ui->engineTable->setItemDelegate(cbid);
	ui->engineTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

EngineManager::~EngineManager()
{
    delete ui;
}

void EngineManager::on_toolButton_clicked()
{
	AddEngineDialog *addEngineDialog = new AddEngineDialog(this);
	addEngineDialog->exec();
	if (addEngineDialog->result() == QDialog::Accepted)
	{
	}
}

void EngineManager::on_toolButton_2_clicked()
{
	AddEngineDialog *addEngineDialog = new AddEngineDialog(this);
	addEngineDialog->exec();
	if (addEngineDialog->result() == QDialog::Accepted)
	{
	}
}

void EngineManager::on_toolButton_3_clicked()
{
	QItemSelectionModel *select = ui->engineTable->selectionModel();

	select->hasSelection(); //check if has selection
	select->selectedRows(); // return selected row(s)
	select->selectedColumns(); // return selected column(s)
	if (ui->engineTable->selectedItems().size() > 0)
	{
		QMessageBox mb("Remove warning", "Do you want to remove this entry?",
			QMessageBox::Question,
			QMessageBox::Ok | QMessageBox::Default,
			QMessageBox::Cancel | QMessageBox::Escape,
			QMessageBox::NoButton, this);
		int response = mb.exec();
		if (response == QMessageBox::Ok)
			return;
	}
}

void EngineManager::on_buttonBox_accepted()
{
	accept();
}

void EngineManager::on_buttonBox_rejected()
{
	reject();
}
