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

QSlider* SettingsDialog::GetWhiteEngineDepth() const
{
    return ui->engine2DepthHorizontalSlider;
}

QSlider* SettingsDialog::GetBlackEngineDepth() const
{
    return ui->engine1DepthHorizontalSlider;
}

void SettingsDialog::on_toolButton_clicked()
{
    VariantDialog* vd = new VariantDialog(this);
    vd->exec();
    if (vd->result() == QDialog::Accepted)
    {
        ui->variantsLineEdit->setText(vd->GetVariant());
    }
}
