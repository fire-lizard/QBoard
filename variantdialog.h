#pragma once
#include <QDialog>

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

private:
    Ui::VariantDialog *ui;
};
