#pragma once
#include <QDialog>
#include <QStyleFactory>
#include <QComboBox>
#include <QCheckBox>
#include "variantdialog.h"

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
    QLineEdit* GetGameVariant() const;
	QComboBox* GetGamePieces() const;
	QComboBox* GetEngineOutput() const;
	QCheckBox* GetHighlightMoves() const;
	QCheckBox* GetHighlightShoots() const;
	QCheckBox* GetHighlightAttackers() const;
	QCheckBox* GetHighlightDefenders() const;
	QCheckBox* GetHighlightLastMoves() const;
    QCheckBox* GetTimerState() const;
    QSlider*   GetEngineDepth() const;

	private slots:

    void on_toolButton_clicked();

private:
	Ui::SettingsDialog *ui;
};
