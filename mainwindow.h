#pragma once
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStandardPaths>
#include "settingsdialog.h"
#include "WbEngine.h"
#include "UciEngine.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
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
	QString _currentStyle = "";
	Engine *_engine = nullptr;
	QString _engineFolder = "";
	QString _engineExe = "";
};
