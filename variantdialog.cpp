#include "variantdialog.h"
#include "ui_variantdialog.h"

VariantDialog::VariantDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VariantDialog)
{
    ui->setupUi(this);
}

VariantDialog::~VariantDialog()
{
    delete ui;
}

QString VariantDialog::GetVariant()
{
    return ui->variantList->currentItem()->text();
}
