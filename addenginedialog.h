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
	QLineEdit* GetEngineName() const;
	QComboBox* GetGameVariant() const;
	QComboBox* GetEngineProtocol() const;
	QLineEdit* GetEnginePath() const;
	QLineEdit* GetEngineParameters() const;
	void SetEngineName(const QString &engineName) const;
	void SetGameVariant(int gameVariant) const;
	void SetEngineProtocol(int engineProtocol) const;
	void SetEnginePath(const QString& enginePath) const;
	void SetEngineParameters(const QString& engineParameters) const;

private slots:
    void on_toolButton_clicked();

private:
    Ui::AddEngineDialog *ui;
};
