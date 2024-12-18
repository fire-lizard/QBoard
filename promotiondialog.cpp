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
    close();
}


void PromotionDialog::on_toolButton_2_clicked()
{
    _chosenPiece = WhiteHorse;
    close();
}


void PromotionDialog::on_toolButton_3_clicked()
{
    _chosenPiece = Bishop;
    close();
}


void PromotionDialog::on_toolButton_4_clicked()
{
    _chosenPiece = Queen;
    close();
}

PieceType PromotionDialog::GetChosenPiece() const
{
    return _chosenPiece;
}
