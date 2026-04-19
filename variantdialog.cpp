#include "variantdialog.h"
#include "ui_variantdialog.h"

VariantDialog::VariantDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VariantDialog)
{
    ui->setupUi(this);
    std::for_each(variantMap().begin(), variantMap().end(), [&](QPair<GameVariant, QString> p) {ui->variantList->addItem(p.second);});
}

VariantDialog::~VariantDialog()
{
    delete ui;
}

QString VariantDialog::GetVariant()
{
    return ui->variantList->currentItem()->text();
}

void VariantDialog::on_variantList_itemDoubleClicked(QListWidgetItem *item)
{
    accept();
}
