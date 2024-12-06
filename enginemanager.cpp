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

QTableWidget * EngineManager::GetEngineTable() const
{
	return ui->engineTable;
}

void EngineManager::on_toolButton_clicked()
{
	AddEngineDialog *addEngineDialog = new AddEngineDialog(this);
	addEngineDialog->exec();
	if (addEngineDialog->result() == QDialog::Accepted)
	{
		const QString engineName = addEngineDialog->GetEngineName()->text();
		const QString gameName = addEngineDialog->GetGameVariant()->currentText();
		const QString engineProtocol = addEngineDialog->GetEngineProtocol()->currentText();
		const QString enginePath = addEngineDialog->GetEnginePath()->text();
		const QString engineParameters = addEngineDialog->GetEngineParameters()->text();
		if (engineName != "" && enginePath != "")
		{
			ui->engineTable->insertRow(ui->engineTable->rowCount());
			const int currentRow = ui->engineTable->rowCount() - 1;
			ui->engineTable->setItem(currentRow, 0, new QTableWidgetItem(engineName));
			ui->engineTable->setItem(currentRow, 1, new QTableWidgetItem(gameName));
			ui->engineTable->setItem(currentRow, 2, new QTableWidgetItem(engineProtocol));
			ui->engineTable->setItem(currentRow, 3, new QTableWidgetItem(enginePath));
            ui->engineTable->setItem(currentRow, 4, new QTableWidgetItem(
                gameName == "Xiangqi" && engineProtocol == "Qianhong" && engineParameters == "" ? "-plugin" : engineParameters));
		}
	}
}

EngineProtocol EngineManager::StringToEngineProtocol(const QString& str)
{
	if (str == "UCI")
		return UCI;
	if (str == "UCCI")
		return UCCI;
	if (str == "Qianhong")
		return Qianhong;
	if (str == "USI")
		return USI;
	return WinBoard;
}

GameVariant EngineManager::StringToGameVariant(const QString& str)
{
	if (str == "Xiangqi")
		return Xiangqi;
	if (str == "Shogi")
		return Shogi;
	if (str == "Sho Shogi")
		return ShoShogi;
	if (str == "Chu Shogi")
		return ChuShogi;
	if (str == "Mini Shogi")
		return MiniShogi;
	return Chess;
}

void EngineManager::on_toolButton_2_clicked()
{
	const int currentRow = ui->engineTable->currentRow();
	if (currentRow == -1) return;
	AddEngineDialog *addEngineDialog = new AddEngineDialog(this);
	addEngineDialog->SetEngineName(ui->engineTable->item(currentRow, 0)->text());
	addEngineDialog->SetGameVariant(StringToGameVariant(ui->engineTable->item(currentRow, 1)->text()));
	addEngineDialog->SetEngineProtocol(StringToEngineProtocol(ui->engineTable->item(currentRow, 2)->text()));
	addEngineDialog->SetEnginePath(ui->engineTable->item(currentRow, 3)->text());
	addEngineDialog->SetEngineParameters(ui->engineTable->item(currentRow, 4)->text());
	addEngineDialog->exec();
	if (addEngineDialog->result() == QDialog::Accepted)
	{
		const QString engineName = addEngineDialog->GetEngineName()->text();
		const QString gameName = addEngineDialog->GetGameVariant()->currentText();
		const QString engineProtocol = addEngineDialog->GetEngineProtocol()->currentText();
		const QString enginePath = addEngineDialog->GetEnginePath()->text();
		const QString engineParameters = addEngineDialog->GetEngineParameters()->text();
		if (engineName != "" && enginePath != "")
		{
			ui->engineTable->setItem(currentRow, 0, new QTableWidgetItem(engineName));
			ui->engineTable->setItem(currentRow, 1, new QTableWidgetItem(gameName));
			ui->engineTable->setItem(currentRow, 2, new QTableWidgetItem(engineProtocol));
			ui->engineTable->setItem(currentRow, 3, new QTableWidgetItem(enginePath));
			ui->engineTable->setItem(currentRow, 4, new QTableWidgetItem(engineParameters));
		}
	}
}

void EngineManager::on_toolButton_3_clicked()
{
	const QItemSelectionModel *select = ui->engineTable->selectionModel();

	if (select->hasSelection())
	{
		QModelIndexList selectedRows = select->selectedRows();
		QMessageBox mb(QMessageBox::Question, "Remove warning", "Do you want to remove this entry?",
			QMessageBox::Ok | QMessageBox::Cancel, this);
		const int response = mb.exec();
		if (response == QMessageBox::Ok)
		{
			const qsizetype cnt = selectedRows.size();
			for (qsizetype index = cnt - 1; index >= 0; index--)
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
