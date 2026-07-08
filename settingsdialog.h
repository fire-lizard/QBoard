#pragma once
#include <QDialog>
#include <QStyleFactory>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
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
	QCheckBox* GetUseWhiteEngineDepth() const;
	QSlider*   GetWhiteEngineDepth() const;
	QCheckBox* GetUseBlackEngineDepth() const;
	QSlider*   GetBlackEngineDepth() const;
	QCheckBox* GetUseWhiteEngineTime() const;
	QSpinBox*  GetWhiteEngineTime() const;
	QCheckBox* GetUseBlackEngineTime() const;
	QSpinBox*  GetBlackEngineTime() const;

private slots:

    void on_toolButton_clicked();
	void on_engine1DepthCheckBox_checkStateChanged(Qt::CheckState state) const;
	void on_engine2DepthCheckBox_checkStateChanged(Qt::CheckState state) const;
	void on_engine1TimeCheckBox_checkStateChanged(Qt::CheckState state) const;
	void on_engine2TimeCheckBox_checkStateChanged(Qt::CheckState state) const;

private:
	Ui::SettingsDialog *ui;
};
