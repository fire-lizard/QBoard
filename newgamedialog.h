#pragma once
#include <QDialog>
#include <QComboBox>
#include <QLabel>

namespace Ui {
    class NewGameDialog;
}

class NewGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewGameDialog(QWidget* parent = nullptr);
    ~NewGameDialog() override;

    QComboBox* GetWhitePlayer() const;
    QComboBox* GetBlackPlayer() const;
    QLabel* GetWhitePlayerLabel() const;

private slots:

private:
    Ui::NewGameDialog* ui;
};
