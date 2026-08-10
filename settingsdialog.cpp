#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);

	foreach(const QString &str, QStyleFactory::keys()) {
		ui->stylesComboBox->addItem(str);
	}

    ui->variantsLineEdit->setStyleSheet("QLineEdit { background: rgb(0, 223, 223); selection-background-color: rgb(223, 99, 0); }");
	ui->engine1DepthHorizontalSlider->setEnabled(ui->engine1DepthCheckBox->isChecked());
	ui->engine2DepthHorizontalSlider->setEnabled(ui->engine2DepthCheckBox->isChecked());
	ui->engine1TimeSpinBox->setEnabled(ui->engine1TimeCheckBox->isChecked());
	ui->engine2TimeSpinBox->setEnabled(ui->engine2TimeCheckBox->isChecked());
}

SettingsDialog::~SettingsDialog()
{
	delete ui;
}

QComboBox* SettingsDialog::GetStyles() const
{
	return ui->stylesComboBox;
}

QLineEdit* SettingsDialog::GetGameVariant() const
{
    return ui->variantsLineEdit;
}

QComboBox* SettingsDialog::GetGamePieces() const
{
	return ui->piecesComboBox;
}

QComboBox* SettingsDialog::GetEngineOutput() const
{
	return ui->engineOutputComboBox;
}

QCheckBox* SettingsDialog::GetHighlightMoves() const
{
	return ui->highlightMovesCheckBox;
}

QCheckBox* SettingsDialog::GetHighlightShoots() const
{
	return ui->highlightShootsCheckBox;
}

QCheckBox* SettingsDialog::GetHighlightAttackers() const
{
	return ui->highlightAttackersCheckBox;
}

QCheckBox* SettingsDialog::GetHighlightDefenders() const
{
	return ui->highlightDefendersCheckBox;
}

QCheckBox* SettingsDialog::GetHighlightLastMoves() const
{
	return ui->highlightLastMovesCheckBox;
}

QCheckBox* SettingsDialog::GetTimerState() const
{
    return ui->timerCheckBox;
}

QCheckBox* SettingsDialog::GetUseBlackEngineDepth() const
{
	return ui->engine1DepthCheckBox;
}

QSlider* SettingsDialog::GetBlackEngineDepth() const
{
	return ui->engine1DepthHorizontalSlider;
}

QCheckBox* SettingsDialog::GetUseWhiteEngineDepth() const
{
	return ui->engine2DepthCheckBox;
}

QSlider* SettingsDialog::GetWhiteEngineDepth() const
{
    return ui->engine2DepthHorizontalSlider;
}

QCheckBox* SettingsDialog::GetUseBlackEngineTime() const
{
	return ui->engine1TimeCheckBox;
}

QSpinBox* SettingsDialog::GetBlackEngineTime() const
{
	return ui->engine1TimeSpinBox;
}

QCheckBox* SettingsDialog::GetUseWhiteEngineTime() const
{
	return ui->engine2TimeCheckBox;
}

QSpinBox* SettingsDialog::GetWhiteEngineTime() const
{
	return ui->engine2TimeSpinBox;
}

void SettingsDialog::on_engine1DepthCheckBox_checkStateChanged(Qt::CheckState state) const
{
	ui->engine1DepthHorizontalSlider->setEnabled(ui->engine1DepthCheckBox->isChecked());
}

void SettingsDialog::on_engine2DepthCheckBox_checkStateChanged(Qt::CheckState state) const
{
	ui->engine2DepthHorizontalSlider->setEnabled(ui->engine2DepthCheckBox->isChecked());
}

void SettingsDialog::on_engine1TimeCheckBox_checkStateChanged(Qt::CheckState state) const
{
	ui->engine1TimeSpinBox->setEnabled(ui->engine1TimeCheckBox->isChecked());
}

void SettingsDialog::on_engine2TimeCheckBox_checkStateChanged(Qt::CheckState state) const
{
	ui->engine2TimeSpinBox->setEnabled(ui->engine2TimeCheckBox->isChecked());
}

void SettingsDialog::on_variantsLineEdit_textChanged(const QString& text)
{
	GameVariant gameVariant = EngineManager::StringToGameVariant(text);
	_pieceStyle = ui->piecesComboBox->currentText();
	ui->piecesComboBox->clear();
	switch (gameVariant)
	{
	case Chess:
	case AmazonChess:
	case AtomicChess:
	case CylinderChess:
	case CrazyHouse:
	case Shatranj:
	case Shatar:
	case Sittuyin:
	case Janggi:
	case Xiangqi:
	case ChuShogi:
	case Shogi:
	case MiniShogi:
	case JudkinShogi:
	case EuroShogi:
	case ShoShogi:
		ui->piecesComboBox->addItem("European");
		ui->piecesComboBox->addItem("Mnemonic");
		ui->piecesComboBox->addItem("Asian");
		ui->piecesComboBox->addItem("Asian 2");
		ui->piecesComboBox->addItem("Asian 3");
		ui->piecesComboBox->addItem("Asian 4");
		break;
	case MicroShogi:
	case KyotoShogi:
		ui->piecesComboBox->addItem("European");
		ui->piecesComboBox->addItem("Mnemonic");
		ui->piecesComboBox->addItem("Asian");
		ui->piecesComboBox->addItem("Asian 2");
		ui->piecesComboBox->addItem("Asian 3");
		ui->piecesComboBox->addItem("Asian 4");
		ui->piecesComboBox->addItem("Asian 5");
		break;
	case DaiShogi:
	case HeianShogi:
	case HeianDaiShogi:
		ui->piecesComboBox->addItem("European");
		ui->piecesComboBox->addItem("Asian");
		ui->piecesComboBox->addItem("Asian 2");
		ui->piecesComboBox->addItem("Asian 3");
		ui->piecesComboBox->addItem("Asian 4");
		break;
	case DaiDaiShogi:
	case MakaDaiDaiShogi:
	case TaiShogi:
		ui->piecesComboBox->addItem("Asian");
		ui->piecesComboBox->addItem("Asian 2");
		break;
	case Makruk:
	case YariShogi:
		ui->piecesComboBox->addItem("European");
		ui->piecesComboBox->addItem("Mnemonic");
		ui->piecesComboBox->addItem("Asian");
		break;
	case TenjikuShogi:
		ui->piecesComboBox->addItem("European");
		ui->piecesComboBox->addItem("Asian");
		ui->piecesComboBox->addItem("Asian 2");
		break;
	case ToriShogi:
	case KoShogi:
		ui->piecesComboBox->addItem("European");
		ui->piecesComboBox->addItem("Mnemonic");
		ui->piecesComboBox->addItem("Asian");
		ui->piecesComboBox->addItem("Asian 2");
		break;
	case CrazyWa:
		ui->piecesComboBox->addItem("European");
		ui->piecesComboBox->addItem("Asian");
		break;
	default:
		ui->piecesComboBox->addItem("European");
		break;
	}
	ui->piecesComboBox->setCurrentText(_pieceStyle);
}

void SettingsDialog::on_toolButton_clicked()
{
    VariantDialog* vd = new VariantDialog(this);
    vd->exec();
    if (vd->result() == Accepted && vd->GetVariant()->currentItem() != nullptr)
    {
        ui->variantsLineEdit->setText(vd->GetVariant()->currentItem()->text());
    }
}
