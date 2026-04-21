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
    accept();
}


void JanusPromotionDialog::on_toolButton_2_clicked()
{
    _chosenPiece = Knight;
    accept();
}


void JanusPromotionDialog::on_toolButton_3_clicked()
{
    _chosenPiece = Bishop;
    accept();
}


void JanusPromotionDialog::on_toolButton_4_clicked()
{
    _chosenPiece = Queen;
    accept();
}

void JanusPromotionDialog::on_toolButton_5_clicked()
{
    _chosenPiece = Archbishop;
    accept();
}

PieceType JanusPromotionDialog::GetChosenPiece() const
{
    return _chosenPiece;
}
