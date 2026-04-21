#include "gothicpromotiondialog.h"
#include "ui_gothicpromotiondialog.h"

GothicPromotionDialog::GothicPromotionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GothicPromotionDialog)
{
    ui->setupUi(this);
}

GothicPromotionDialog::~GothicPromotionDialog()
{
    delete ui;
}

void GothicPromotionDialog::on_toolButton_clicked()
{
    _chosenPiece = Rook;
    accept();
}


void GothicPromotionDialog::on_toolButton_2_clicked()
{
    _chosenPiece = Knight;
    accept();
}


void GothicPromotionDialog::on_toolButton_3_clicked()
{
    _chosenPiece = Bishop;
    accept();
}


void GothicPromotionDialog::on_toolButton_4_clicked()
{
    _chosenPiece = Queen;
    accept();
}

void GothicPromotionDialog::on_toolButton_5_clicked()
{
    _chosenPiece = Archbishop;
    accept();
}

void GothicPromotionDialog::on_toolButton_6_clicked()
{
    _chosenPiece = Chancellor;
    accept();
}

PieceType GothicPromotionDialog::GetChosenPiece() const
{
    return _chosenPiece;
}

void GothicPromotionDialog::SetEnabled(PieceType pieceType, bool isEnabled)
{
    if (pieceType == Rook) ui->toolButton->setEnabled(isEnabled);
    if (pieceType == Knight) ui->toolButton_2->setEnabled(isEnabled);
    if (pieceType == Bishop) ui->toolButton_3->setEnabled(isEnabled);
    if (pieceType == Queen) ui->toolButton_4->setEnabled(isEnabled);
    if (pieceType == Archbishop) ui->toolButton_5->setEnabled(isEnabled);
    if (pieceType == Chancellor) ui->toolButton_6->setEnabled(isEnabled);
}
