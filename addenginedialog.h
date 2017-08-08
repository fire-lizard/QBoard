#pragma once
#include <QDialog>
#include <QFileDialog>
#include <QLineEdit>
#include <QComboBox>

namespace Ui {
class AddEngineDialog;
}

class AddEngineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddEngineDialog(QWidget *parent = nullptr);
    ~AddEngineDialog();
	QLineEdit* GetEngineName();
	QComboBox* GetEngineProtocol();
	QLineEdit* GetEnginePath();

private slots:
    void on_toolButton_clicked();

private:
    Ui::AddEngineDialog *ui;
};
