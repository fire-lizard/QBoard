#pragma once
#include <QDialog>
#include <QFileDialog>
#include <QLineEdit>
#include <QComboBox>
#include "Common.h"

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
	void SetEngineName(const QString &engineName) const;
    void SetGameVariant(const QString& gameVariant) const;
    void SetEngineProtocol(const QString& engineProtocol) const;
	void SetEnginePath(const QString& enginePath) const;

private slots:
    void on_toolButton_clicked();

    void on_gameVariant_currentIndexChanged(int index);

private:
    Ui::AddEngineDialog *ui;
};
