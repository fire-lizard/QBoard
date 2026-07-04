#include "addenginedialog.h"
#include "ui_addenginedialog.h"

AddEngineDialog::AddEngineDialog(QWidget* parent) : QDialog(parent), ui(new Ui::AddEngineDialog)
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

QComboBox * AddEngineDialog::GetEngineProtocol() const
{
	return ui->engineProtocol;
}

QLineEdit * AddEngineDialog::GetEnginePath() const
{
	return ui->enginePath;
}

QLineEdit * AddEngineDialog::GetEngineOptions() const
{
    return ui->engineOptions;
}

void AddEngineDialog::SetEngineName(const QString& engineName) const
{
	ui->engineName->setText(engineName);
}

void AddEngineDialog::SetEngineProtocol(const QString& engineProtocol) const
{
    ui->engineProtocol->setCurrentText(engineProtocol);
}

void AddEngineDialog::SetEnginePath(const QString& enginePath) const
{
	ui->enginePath->setText(enginePath);
}

void AddEngineDialog::SetEngineOptions(const QString& engineOptions) const
{
    ui->engineOptions->setText(engineOptions);
}

void AddEngineDialog::on_toolButton_clicked()
{
#ifdef Q_OS_WIN
    const QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Programs (*.exe)");
#else
    const QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Programs (*)");
#endif
	ui->enginePath->setText(fileName);
}
