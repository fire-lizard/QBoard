#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    foreach (const QString &str, QStyleFactory::keys()) {
            ui->stylesComboBox->addItem(str);
        }
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_buttonBox_accepted()
{
    QApplication::setStyle(ui->stylesComboBox->itemText(ui->stylesComboBox->currentIndex()));
}
