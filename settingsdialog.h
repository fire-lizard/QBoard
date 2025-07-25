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
	~SettingsDialog() override;
	QComboBox* GetStyles() const;
	QComboBox* GetGameVariants() const;
	QComboBox* GetGamePieces() const;
	QComboBox* GetEngineOutput() const;
	QCheckBox* GetHighlightMoves() const;
	QCheckBox* GetHighlightShoots() const;
	QCheckBox* GetHighlightAttackers() const;
	QCheckBox* GetHighlightDefenders() const;
	QCheckBox* GetHighlightLastMoves() const;

	private slots:

private:
	Ui::SettingsDialog *ui;
};
