#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);

	foreach(const QString &str, QStyleFactory::keys()) {
		ui->stylesComboBox->addItem(str);
	}
}

SettingsDialog::~SettingsDialog()
{
	delete ui;
}

QComboBox* SettingsDialog::GetStyles() const
{
	return ui->stylesComboBox;
}

QComboBox* SettingsDialog::GetGameVariants() const
{
	return ui->variantsComboBox;
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
