#pragma once
#include <QDialog>
#include <QStyleFactory>
#include <QComboBox>
#include <algorithm>
#include "mainwindow.h"

namespace Ui {
	class SettingsDialog;
}

class SettingsDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SettingsDialog(QWidget *parent = 0);
	~SettingsDialog();
	QComboBox* GetStyles() const;
	QComboBox* GetGameVariants() const;

	private slots:

private:
	Ui::SettingsDialog *ui;
};
