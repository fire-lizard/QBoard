#include "addenginedialog.h"
#include "ui_addenginedialog.h"

AddEngineDialog::AddEngineDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AddEngineDialog)
{
    ui->setupUi(this);
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
    const QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Programs (*.exe *.bat *.cmd *.ps1)");
#else
    const QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Programs (*)");
#endif
	ui->enginePath->setText(fileName);
}

void AddEngineDialog::on_toolButton_2_clicked()
{
	VariantDialog* vd = new VariantDialog(this);
    vd->GetVariant()->setSelectionMode(QAbstractItemView::MultiSelection);
    QStringList variants = ui->gameVariant->text().split(',');
    for (int index = 0; index < vd->GetVariant()->count(); index++)
    {
        auto item = vd->GetVariant()->item(index);
        if (variants.contains(item->text()))
        {
            item->setSelected(true);
        }
    }
    vd->exec();
    if (vd->result() == Accepted)
    {
        variants.clear();
        for (auto& selectedItem : vd->GetVariant()->selectedItems())
        {
            variants.push_back(selectedItem->text());
        }
    	ui->gameVariant->setText(variants.join(','));
    }
}

void AddEngineDialog::on_toolButton_3_clicked() const
{
    QStringList variantList = GetVariantList();
    ui->gameVariant->setText(variantList.join(','));
}

void AddEngineDialog::on_engineProtocol_currentIndexChanged(int index) const
{
    ui->toolButton_2->setEnabled(ui->engineProtocol->currentText() == "XBoard");
	ui->toolButton_3->setEnabled(ui->engineProtocol->currentText() == "XBoard");
    ui->engineOptions->setEnabled(ui->engineProtocol->currentText() != "Qianhong");
    if (ui->engineProtocol->currentText() == "UCI")
    {
        ui->gameVariant->setText("Chess");
    }
    else if (ui->engineProtocol->currentText() == "UCCI" || ui->engineProtocol->currentText() == "Qianhong")
    {
        ui->gameVariant->setText("Xiangqi");
    }
    else if (ui->engineProtocol->currentText() == "USI")
    {
        ui->gameVariant->setText("Shogi");
    }
}

QStringList AddEngineDialog::GetVariantList() const
{
    QProcess process;
    process.setWorkingDirectory(QFileInfo(ui->enginePath->text()).absolutePath());
    process.setProgram(ui->enginePath->text());
    process.start();
    if (!process.waitForStarted(1000))
    {
        return {};
    }
    process.write("xboard\n");
    process.waitForBytesWritten();
    process.write("protover 2\n");
    process.waitForBytesWritten();
    QString allOutput;
    while (true)
    {
        if (!process.waitForReadyRead(1000))
            break;
        allOutput += QString::fromUtf8(process.readAll());
        if (allOutput.contains("feature done=1"))
            break;
    }
    QRegularExpression rx(R"(variants="([^"]*))");
	QRegularExpressionMatch match = rx.match(allOutput);
    if (match.hasMatch())
    {
    	QString variants = match.captured(1);
        QStringList variantList = variants.split(',');
        QStringList result;
        for (QString& variantName: variantList)
        {
            std::optional<GameVariant> gameVariant = EngineManager::ShortStringToGameVariant(variantName);
        	if (gameVariant != std::nullopt)
	        {
                QString str = EngineManager::GameVariantToString(gameVariant.value());
                if (!result.contains(str))
                {
                    result.push_back(str);
                }
	        }
        }
        return result;
    }
    process.write("quit\n");
    return {};
}
