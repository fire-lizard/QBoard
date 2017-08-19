#pragma once
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStandardPaths>
#include <QSysInfo>
#include <QDate>
#include "settingsdialog.h"
#include "WbEngine.h"
#include "UciEngine.h"
#include "UcciEngine.h"
#include "UsiEngine.h"
#include "QianhongEngine.h"
#include "enginemanager.h"

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

    void on_actionStop_game_triggered();

    void on_actionEngine_Manager_triggered();

private:
	void closeEvent(QCloseEvent *) override;

	Ui::MainWindow *ui;
	QString _currentStyle = "";
	Engine *_engine = nullptr;
	QString _engineExe = "";
	QString _engineName = "";
	EngineProtocol _engineProtocol = WinBoard;
};
