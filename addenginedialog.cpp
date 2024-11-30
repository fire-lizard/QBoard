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

QLineEdit * AddEngineDialog::GetEngineName() const
{
	return ui->engineName;
}

QComboBox* AddEngineDialog::GetGameVariant() const
{
	return ui->gameVariant;
}

QComboBox * AddEngineDialog::GetEngineProtocol() const
{
	return ui->engineProtocol;
}

QLineEdit * AddEngineDialog::GetEnginePath() const
{
	return ui->enginePath;
}

QLineEdit* AddEngineDialog::GetEngineParameters() const
{
	return ui->engineParameters;
}

void AddEngineDialog::SetEngineName(const QString& engineName) const
{
	ui->engineName->setText(engineName);
}

void AddEngineDialog::SetGameVariant(int game) const
{
	ui->gameVariant->setCurrentIndex(game);
}

void AddEngineDialog::SetEngineProtocol(int engineProtocol) const
{
	ui->engineProtocol->setCurrentIndex(engineProtocol);
}

void AddEngineDialog::SetEnginePath(const QString& enginePath) const
{
	ui->enginePath->setText(enginePath);
}

void AddEngineDialog::SetEngineParameters(const QString& engineParameters) const
{
	ui->engineParameters->setText(engineParameters);
}

void AddEngineDialog::on_toolButton_clicked()
{
	const QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Programs (*.exe)");
	ui->enginePath->setText(fileName);
}
