#include "addenginedialog.h"
#include "ui_addenginedialog.h"

AddEngineDialog::AddEngineDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AddEngineDialog)
{
    ui->setupUi(this);
    on_gameVariant_currentIndexChanged(0);
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

void AddEngineDialog::SetGameVariant(QString gameVariant) const
{
    ui->gameVariant->setCurrentText(gameVariant);
}

void AddEngineDialog::SetEngineProtocol(QString engineProtocol) const
{
    ui->engineProtocol->setCurrentText(engineProtocol);
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
#ifdef Q_OS_WIN
    const QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Programs (*.exe)");
#else
    const QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Programs (*)");
#endif
	ui->enginePath->setText(fileName);
}

void AddEngineDialog::on_gameVariant_currentIndexChanged(int index)
{
    ui->engineProtocol->clear();
    ui->engineProtocol->addItem("XBoard");
    GameVariant v = static_cast<GameVariant>(index);
    switch (v)
    {
    case Chess:
        ui->engineProtocol->addItem("UCI");
        break;
    case Xiangqi:
        ui->engineProtocol->addItem("UCCI");
        ui->engineProtocol->addItem("Qianhong");
        break;
    case Shogi:
        ui->engineProtocol->addItem("USI");
        break;
    default:
        break;
    }
}

