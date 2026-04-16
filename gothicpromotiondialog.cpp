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
    close();
}


void GothicPromotionDialog::on_toolButton_2_clicked()
{
    _chosenPiece = Knight;
    close();
}


void GothicPromotionDialog::on_toolButton_3_clicked()
{
    _chosenPiece = Bishop;
    close();
}


void GothicPromotionDialog::on_toolButton_4_clicked()
{
    _chosenPiece = Queen;
    close();
}

void GothicPromotionDialog::on_toolButton_5_clicked()
{
    _chosenPiece = Archbishop;
    close();
}

void GothicPromotionDialog::on_toolButton_6_clicked()
{
    _chosenPiece = Chancellor;
    close();
}

PieceType GothicPromotionDialog::GetChosenPiece() const
{
    return _chosenPiece;
}
