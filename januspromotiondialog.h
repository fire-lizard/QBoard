#pragma once
#include <QDialog>
#include "Common.h"

namespace Ui {
class JanusPromotionDialog;
}

class JanusPromotionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit JanusPromotionDialog(QWidget *parent = nullptr);
    ~JanusPromotionDialog() override;

    PieceType GetChosenPiece() const;

private slots:
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_5_clicked();

private:
    Ui::JanusPromotionDialog *ui;

    PieceType _chosenPiece;
};
