#include "januspromotiondialog.h"
#include "ui_januspromotiondialog.h"

JanusPromotionDialog::JanusPromotionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::JanusPromotionDialog)
{
    ui->setupUi(this);
}

JanusPromotionDialog::~JanusPromotionDialog()
{
    delete ui;
}

void JanusPromotionDialog::on_toolButton_clicked()
{
    _chosenPiece = Rook;
    close();
}


void JanusPromotionDialog::on_toolButton_2_clicked()
{
    _chosenPiece = Knight;
    close();
}


void JanusPromotionDialog::on_toolButton_3_clicked()
{
    _chosenPiece = Bishop;
    close();
}


void JanusPromotionDialog::on_toolButton_4_clicked()
{
    _chosenPiece = Queen;
    close();
}

void JanusPromotionDialog::on_toolButton_5_clicked()
{
    _chosenPiece = Archbishop;
    close();
}

PieceType JanusPromotionDialog::GetChosenPiece() const
{
    return _chosenPiece;
}
