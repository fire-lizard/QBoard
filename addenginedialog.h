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
    ~AddEngineDialog() override;
	QLineEdit* GetEngineName();
	QComboBox* GetEngineProtocol();
	QLineEdit* GetEnginePath();
	void SetEngineName(const QString &engineName);
	void SetEngineProtocol(int engineProtocol);
	void SetEnginePath(const QString& enginePath);

private slots:
    void on_toolButton_clicked();

private:
    Ui::AddEngineDialog *ui;
};
