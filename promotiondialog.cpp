#include "promotiondialog.h"
#include "ui_promotiondialog.h"

PromotionDialog::PromotionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PromotionDialog)
{
    ui->setupUi(this);
}

PromotionDialog::~PromotionDialog()
{
    delete ui;
}

void PromotionDialog::on_toolButton_clicked()
{
    _chosenPiece = Rook;
    accept();
}


void PromotionDialog::on_toolButton_2_clicked()
{
    _chosenPiece = Knight;
    accept();
}


void PromotionDialog::on_toolButton_3_clicked()
{
    _chosenPiece = Bishop;
    accept();
}


void PromotionDialog::on_toolButton_4_clicked()
{
    _chosenPiece = Queen;
    accept();
}

PieceType PromotionDialog::GetChosenPiece() const
{
    return _chosenPiece;
}
