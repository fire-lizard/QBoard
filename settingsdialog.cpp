#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);

	foreach(const QString &str, QStyleFactory::keys()) {
		ui->stylesComboBox->addItem(str);
	}

    ui->variantsLineEdit->setStyleSheet("QLineEdit { background: rgb(0, 223, 223); selection-background-color: rgb(223, 99, 0); }");
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

void SettingsDialog::on_toolButton_clicked()
{
    VariantDialog* vd = new VariantDialog(this);
    vd->exec();
    if (vd->result() == Accepted)
    {
        ui->variantsLineEdit->setText(vd->GetVariant()->currentItem()->text());
    }
}
