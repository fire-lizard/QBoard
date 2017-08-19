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

QTableWidget * EngineManager::GetEngineTable()
{
	return ui->engineTable;
}

void EngineManager::on_toolButton_clicked()
{
	AddEngineDialog *addEngineDialog = new AddEngineDialog(this);
	addEngineDialog->exec();
	if (addEngineDialog->result() == QDialog::Accepted)
	{
		QString engineName = addEngineDialog->GetEngineName()->text();
		QString engineProtocol = addEngineDialog->GetEngineProtocol()->currentText();
		QString enginePath = addEngineDialog->GetEnginePath()->text();
		if (engineName != "" && enginePath != "")
		{
			ui->engineTable->insertRow(ui->engineTable->rowCount());
			int currentRow = ui->engineTable->rowCount() - 1;
			ui->engineTable->setItem(currentRow, 0, new QTableWidgetItem(engineName));
			ui->engineTable->setItem(currentRow, 1, new QTableWidgetItem(engineProtocol));
			ui->engineTable->setItem(currentRow, 2, new QTableWidgetItem(enginePath));
		}
	}
}

void EngineManager::on_toolButton_2_clicked()
{
	int currentRow = ui->engineTable->currentRow();
	if (currentRow == -1) return;
	AddEngineDialog *addEngineDialog = new AddEngineDialog(this);
	addEngineDialog->exec();
	if (addEngineDialog->result() == QDialog::Accepted)
	{
		QString engineName = addEngineDialog->GetEngineName()->text();
		QString engineProtocol = addEngineDialog->GetEngineProtocol()->currentText();
		QString enginePath = addEngineDialog->GetEnginePath()->text();
		if (engineName != "" && enginePath != "")
		{
			ui->engineTable->setItem(currentRow, 0, new QTableWidgetItem(engineName));
			ui->engineTable->setItem(currentRow, 1, new QTableWidgetItem(engineProtocol));
			ui->engineTable->setItem(currentRow, 2, new QTableWidgetItem(enginePath));
		}
	}
}

void EngineManager::on_toolButton_3_clicked()
{
	QItemSelectionModel *select = ui->engineTable->selectionModel();

	if (select->hasSelection())
	{
		QModelIndexList selectedRows = select->selectedRows();
		QMessageBox mb("Remove warning", "Do you want to remove this entry?",
			QMessageBox::Question,
			QMessageBox::Ok | QMessageBox::Default,
			QMessageBox::Cancel | QMessageBox::Escape,
			QMessageBox::NoButton, this);
		int response = mb.exec();
		if (response == QMessageBox::Ok)
		{
			for (int index = 0; index < selectedRows.size(); index++)
			{
				ui->engineTable->removeRow(selectedRows[index].row());
			}
		}
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
