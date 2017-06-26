#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SettingsDialog)
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

void SettingsDialog::on_tableWidget_clicked(const QModelIndex &index)
{
	int r = index.row();
	EngineFolder = ui->tableWidget->verticalHeaderItem(r)->data(0).toString();
	EngineExe = ui->tableWidget->item(r, 0)->data(0).toString();
	SelectedEngineType = ui->tableWidget->item(r, 1)->data(0).toString();
}
