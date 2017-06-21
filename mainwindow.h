#pragma once
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "settingsdialog.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	private slots:
	void on_actionSettings_triggered();

	void on_actionAbout_triggered();

	void on_actionExit_triggered();

    void on_actionNew_game_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

private:
	Ui::MainWindow *ui;
};
