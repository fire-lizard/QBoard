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

QComboBox* SettingsDialog::GetWhitePlayer() const
{
	return ui->whitePlayerComboBox;
}

QComboBox* SettingsDialog::GetBlackPlayer() const
{
	return ui->blackPlayerComboBox;
}

void SettingsDialog::on_variantsComboBox_currentIndexChanged(int index)
{
	if (index == 1)
	{
		this->ui->whitePlayerLabel->setText("<html><head/><body><p><span style='color:#ffffff;background:#ff0000; '>Red player</span></p></body></html>");
	}
	else
	{
		this->ui->whitePlayerLabel->setText("<html><head/><body><p><span style='background:#ffffff; '>White player</span></p></body></html>");
	}
}
