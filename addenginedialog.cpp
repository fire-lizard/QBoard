#include "addenginedialog.h"
#include "ui_addenginedialog.h"

AddEngineDialog::AddEngineDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AddEngineDialog)
{
    ui->setupUi(this);
}

AddEngineDialog::~AddEngineDialog()
{
    delete ui;
}

QLineEdit * AddEngineDialog::GetEngineName()
{
	return ui->engineName;
}

QComboBox * AddEngineDialog::GetEngineProtocol()
{
	return ui->engineProtocol;
}

QLineEdit * AddEngineDialog::GetEnginePath()
{
	return ui->enginePath;
}

void AddEngineDialog::SetEngineName(const QString& engineName)
{
	ui->engineName->setText(engineName);
}

void AddEngineDialog::SetEngineProtocol(int engineProtocol)
{
	ui->engineProtocol->setCurrentIndex(engineProtocol);
}

void AddEngineDialog::SetEnginePath(const QString& enginePath)
{
	ui->enginePath->setText(enginePath);
}

void AddEngineDialog::on_toolButton_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Programs (*.exe)");
	ui->enginePath->setText(fileName);
}
