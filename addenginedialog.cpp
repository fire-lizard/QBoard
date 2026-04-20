#include "addenginedialog.h"
#include "ui_addenginedialog.h"

AddEngineDialog::AddEngineDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AddEngineDialog)
{
    ui->setupUi(this);
    on_gameVariant_currentIndexChanged(0);
    ui->gameVariant->setText("Chess");
    ui->gameVariant->setStyleSheet("QLineEdit { background: rgb(0, 223, 223); selection-background-color: rgb(223, 99, 0); }");
}

AddEngineDialog::~AddEngineDialog()
{
    delete ui;
}

QLineEdit * AddEngineDialog::GetEngineName() const
{
	return ui->engineName;
}

QLineEdit * AddEngineDialog::GetGameVariant() const
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

QLineEdit * AddEngineDialog::GetEngineOptions() const
{
    return ui->engineOptions;
}

void AddEngineDialog::SetEngineName(const QString& engineName) const
{
	ui->engineName->setText(engineName);
}

void AddEngineDialog::SetGameVariant(const QString& gameVariant) const
{
    ui->gameVariant->setText(gameVariant);
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

void AddEngineDialog::on_gameVariant_currentIndexChanged(int index)
{
    ui->engineProtocol->clear();
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
    case MiniShogi:
    case JudkinShogi:
        ui->engineProtocol->addItem("USI");
        break;
    default:
        break;
    }
    ui->engineProtocol->addItem("XBoard");
}


void AddEngineDialog::on_toolButton_2_clicked()
{
    VariantDialog* vd = new VariantDialog(this);
    vd->exec();
    if (vd->result() == QDialog::Accepted)
    {
        ui->gameVariant->setText(vd->GetVariant());
    }
}
