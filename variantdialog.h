#pragma once
#include <algorithm>
#include <QDialog>
#include <QListWidgetItem>
#include "enginemanager.h"

namespace Ui {
class VariantDialog;
}

class VariantDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VariantDialog(QWidget *parent = nullptr);
    ~VariantDialog();
    QString GetVariant();

private slots:
    void on_variantList_itemDoubleClicked(QListWidgetItem *item);

    void on_allGamesRadioButton_toggled(bool checked);

    void on_chessGamesRadioButton_toggled(bool checked);

    void on_shogiGamesRadioButton_toggled(bool checked);

    void on_otherGamesRadioButton_toggled(bool checked);

private:
    Ui::VariantDialog *ui;
};
