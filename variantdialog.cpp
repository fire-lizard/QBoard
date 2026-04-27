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

void VariantDialog::on_allGamesRadioButton_toggled(bool checked)
{
    if (checked)
    {
        ui->variantList->clear();
        std::for_each(variantMap().begin(), variantMap().end(), [&](QPair<GameVariant, QString> p) {ui->variantList->addItem(p.second);});
    }
}

void VariantDialog::on_chessGamesRadioButton_toggled(bool checked)
{
    if (checked)
    {
        ui->variantList->clear();
        std::for_each(variantMap().begin(), variantMap().end(), [&](QPair<GameVariant, QString> p) {
            if (std::find(std::begin(chessVariants), std::end(chessVariants), p.first) != std::end(chessVariants))
            {
                ui->variantList->addItem(p.second);
            }});
    }
}

void VariantDialog::on_shogiGamesRadioButton_toggled(bool checked)
{
    if (checked)
    {
        ui->variantList->clear();
        std::for_each(variantMap().begin(), variantMap().end(), [&](QPair<GameVariant, QString> p) {
            if (std::find(std::begin(shogiVariants), std::end(shogiVariants), p.first) != std::end(shogiVariants))
            {
                ui->variantList->addItem(p.second);
            }});
    }
}

void VariantDialog::on_otherGamesRadioButton_toggled(bool checked)
{
    if (checked)
    {
        ui->variantList->clear();
        std::for_each(variantMap().begin(), variantMap().end(), [&](QPair<GameVariant, QString> p) {
            if (std::find(std::begin(chessVariants), std::end(chessVariants), p.first) == std::end(chessVariants) &&
                std::find(std::begin(shogiVariants), std::end(shogiVariants), p.first) == std::end(shogiVariants))
            {
                ui->variantList->addItem(p.second);
            }});
    }
}
