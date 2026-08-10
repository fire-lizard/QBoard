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
    ~VariantDialog() override;
    QListWidget* GetVariant() const;
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void on_variantList_itemDoubleClicked(QListWidgetItem *item);

private:
    void ApplyFilter() const;

    Ui::VariantDialog *ui;
};
