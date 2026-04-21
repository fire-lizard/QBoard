#pragma once
#include <QDialog>
#include "Common.h"

namespace Ui {
class GothicPromotionDialog;
}

class GothicPromotionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GothicPromotionDialog(QWidget *parent = nullptr);
    ~GothicPromotionDialog() override;

    PieceType GetChosenPiece() const;
    void SetEnabled(PieceType pieceType, bool isEnabled);

private slots:
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_5_clicked();

    void on_toolButton_6_clicked();

private:
    Ui::GothicPromotionDialog *ui;

    PieceType _chosenPiece;
};
