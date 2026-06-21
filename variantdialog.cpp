#include "variantdialog.h"
#include "ui_variantdialog.h"

VariantDialog::VariantDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VariantDialog)
{
    ui->setupUi(this);
    std::ranges::for_each(variantMap(), [&](const QPair<GameVariant, QString>& p) {ui->variantList->addItem(p.second);});
}

VariantDialog::~VariantDialog()
{
    delete ui;
}

QString VariantDialog::GetVariant() const
{
    return ui->variantList->currentItem()->text();
}

void VariantDialog::on_variantList_itemDoubleClicked(QListWidgetItem *item)
{
    accept();
}

void VariantDialog::on_allGamesRadioButton_toggled(bool checked) const
{
    if (checked)
    {
        ui->variantList->clear();
        std::ranges::for_each(variantMap(), [&](const QPair<GameVariant, QString>& p) {ui->variantList->addItem(p.second);});
    }
}

void VariantDialog::on_chessGamesRadioButton_toggled(bool checked) const
{
    if (checked)
    {
        ui->variantList->clear();
        std::ranges::for_each(variantMap(), [&](const QPair<GameVariant, QString>& p) {
            if (std::ranges::find(chessVariants, p.first) != std::end(chessVariants))
            {
                ui->variantList->addItem(p.second);
            }});
    }
}

void VariantDialog::on_shogiGamesRadioButton_toggled(bool checked) const
{
    if (checked)
    {
        ui->variantList->clear();
        std::ranges::for_each(variantMap(), [&](const QPair<GameVariant, QString>& p) {
            if (std::ranges::find(shogiVariants, p.first) != std::end(shogiVariants))
            {
                ui->variantList->addItem(p.second);
            }});
    }
}

void VariantDialog::on_otherGamesRadioButton_toggled(bool checked) const
{
    if (checked)
    {
        ui->variantList->clear();
        std::ranges::for_each(variantMap(), [&](const QPair<GameVariant, QString>& p) {
            if (std::ranges::find(chessVariants, p.first) == std::end(chessVariants) &&
                std::ranges::find(shogiVariants, p.first) == std::end(shogiVariants))
            {
                ui->variantList->addItem(p.second);
            }});
    }
}
