#pragma once
#include <QDialog>
#include <QStyleFactory>
#include <QComboBox>
#include "mainwindow.h"

namespace Ui {
	class SettingsDialog;
}

class SettingsDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SettingsDialog(QWidget *parent = nullptr);
	~SettingsDialog();
	QComboBox* GetStyles() const;
	QComboBox* GetGameVariants() const;
	QString EngineFolder = "";
	QString EngineExe = "";
	QString SelectedEngineProtocol = "";

	private slots:

    void on_variantsComboBox_currentIndexChanged(int index);

private:
	Ui::SettingsDialog *ui;
};
