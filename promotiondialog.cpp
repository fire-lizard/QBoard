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

void PromotionDialog::on_toolButton_5_clicked()
{
    _chosenPiece = Archbishop;
    accept();
}

void PromotionDialog::on_toolButton_6_clicked()
{
    _chosenPiece = Chancellor;
    accept();
}

PieceType PromotionDialog::GetChosenPiece() const
{
    return _chosenPiece;
}

void PromotionDialog::SetEnabled(PieceType pieceType, bool isEnabled)
{
    if (pieceType == Rook) ui->toolButton->setEnabled(isEnabled);
    if (pieceType == Knight) ui->toolButton_2->setEnabled(isEnabled);
    if (pieceType == Bishop) ui->toolButton_3->setEnabled(isEnabled);
    if (pieceType == Queen) ui->toolButton_4->setEnabled(isEnabled);
    if (pieceType == Archbishop) ui->toolButton_5->setEnabled(isEnabled);
    if (pieceType == Chancellor) ui->toolButton_6->setEnabled(isEnabled);
}
