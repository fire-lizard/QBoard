#pragma once
#include <algorithm>
#include <QDialog>
#include <QFileDialog>
#include <QLineEdit>
#include <QComboBox>
#include "Common.h"
#include "enginemanager.h"
#include "variantdialog.h"

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
    QLineEdit* GetGameVariant() const;
	QComboBox* GetEngineProtocol() const;
	QLineEdit* GetEnginePath() const;
    QLineEdit* GetEngineOptions() const;
    void SetEngineName(const QString &engineName) const;
    void SetGameVariant(const QString& gameVariant) const;
    void SetEngineProtocol(const QString& engineProtocol) const;
	void SetEnginePath(const QString& enginePath) const;
    void SetEngineOptions(const QString& engineOptions) const;

private slots:
    void on_toolButton_clicked();

    void on_gameVariant_currentIndexChanged(int index);

    void on_toolButton_2_clicked();

private:
    Ui::AddEngineDialog *ui;
};
